#include <windows.h>
#include <qmath.h>
#include <vector>
#include <Dbt.h>
#include <QDebug>
#include <QString>
#include <QEvent>
#include <QList>
#include <QTimer>
#include <QSettings>
#include <QThread>

#include "CyAPI.h"
#include "..\include\gkhy\BoardApi\Board.h"

#pragma comment(lib, "CyAPI.lib")

using namespace std;



class QThreadL : public QThread
{
public:
	static void msleep (unsigned long msecs)
	{
		QThread::msleep(msecs);
	}
};

static void msleep (unsigned long msecs)
{
	QThreadL::msleep(msecs);
}


class DummyWidget : public QWidget
{
	Q_OBJECT

public:
	DummyWidget(QWidget* parent = 0, Qt::WindowFlags f = 0 );

protected:
	bool winEvent(MSG * message, long * result);

signals:
	void devChanged();

private:
	bool bPnP_Arrival;
	bool bPnP_DevNodeChange;
	bool bPnP_Removal;
};

#include "Board.moc"

DummyWidget::DummyWidget(QWidget* parent /*= 0*/, Qt::WindowFlags f /*= 0*/ ) : QWidget(parent, f) 
{
	bPnP_Arrival = false;
	bPnP_DevNodeChange = false;
	bPnP_Removal = false;
	QTimer::singleShot(0, this, SIGNAL(devChanged()));	
}

bool DummyWidget::winEvent(MSG * message, long * result)
{	
	if (message->message == WM_DEVICECHANGE) {
		// Tracks DBT_DEVICEARRIVAL followed by DBT_DEVNODES_CHANGED
		if (message->wParam == DBT_DEVICEARRIVAL) {
			bPnP_Arrival = true;
			bPnP_DevNodeChange = false;
		}
		// Tracks DBT_DEVNODES_CHANGED followed by DBT_DEVICEREMOVECOMPLETE
		if (message->wParam == DBT_DEVNODES_CHANGED) {
			bPnP_DevNodeChange = true;
			bPnP_Removal = false;
		}
		if (message->wParam == DBT_DEVICEREMOVECOMPLETE) {
			bPnP_Removal = true;
			PDEV_BROADCAST_HDR bcastHdr = (PDEV_BROADCAST_HDR) message->lParam;
			if (bcastHdr->dbch_devicetype == DBT_DEVTYP_HANDLE) {
				PDEV_BROADCAST_HANDLE pDev = (PDEV_BROADCAST_HANDLE) message->lParam;
				/*if (pDev->dbch_handle == USBDevice->DeviceHandle())
				USBDevice->Close();*/
			}
		}
		// If DBT_DEVNODES_CHANGED followed by DBT_DEVICEREMOVECOMPLETE
		if (bPnP_Removal && bPnP_DevNodeChange) {
			//Sleep(10);
			//DisplayDevices();
			bPnP_Removal = false;
			bPnP_DevNodeChange = false;
			//msleep(10);
			emit devChanged();
		}
		// If DBT_DEVICEARRIVAL followed by DBT_DEVNODES_CHANGED
		if (bPnP_DevNodeChange && bPnP_Arrival) {
			//DisplayDevices();
			bPnP_Arrival = false;
			bPnP_DevNodeChange = false;
			emit devChanged();
		}
	}
	return false;
}

Board* Board::_inst = 0;
Board::Board(QObject* parent /* = 0 */) 
: QObject(parent)
, pi(3.141592653589793f)
{
	widget = new DummyWidget();
	bool okay = connect(widget, SIGNAL(devChanged()), this, SLOT(devChanged()));
	Q_ASSERT(okay);
	usbDev = new CCyUSBDevice((HANDLE)(widget->winId()));
}

Board::~Board()
{
	if (usbDev)
	{
		delete usbDev;
		usbDev = 0;
	}

	if (widget)
	{
		delete widget;
		widget = 0;
	}
}

void Board::devChanged()
{
	QList<BoardInfo> devList;
	if (!(usbDev->DeviceCount()))
	{
		devList.clear();
	}
	for (int i = 0; i < usbDev->DeviceCount(); ++i)
	{
		if (usbDev->Open(i))
		{
			BoardInfo info;
			info.usbAddr = i;
			info.devName = QString(usbDev->DeviceName);
			info.infName = QString(usbDev->FriendlyName);
			devList.push_back(info);
		}
	}

	emit devListChanged(devList);
}

bool Board::open(int usbAddr)
{
	return usbDev->Open((UCHAR)usbAddr);
}

bool Board::read(unsigned short addr, unsigned short *buf, unsigned int len)
{	
	if (! usbDev->BulkOutEndPt)
		return false;

	long b2Read = (len * sizeof(unsigned short) + 511) / 512 * 512;
	long w2Read = b2Read / 2;
	if (bulkIOBuff.size() < w2Read) bulkIOBuff.resize(w2Read);

	if (!writeIOCmd(addr, true, w2Read))
	{
		return false;
	}

	long bRead = b2Read;
	if (!usbDev->BulkInEndPt->XferData((unsigned char*)&bulkIOBuff[0], bRead))
		return false;

	if (b2Read != bRead)
	{
		return false;
	}

	memcpy(buf, &bulkIOBuff[0], len * sizeof(unsigned short));

	return true;
}

bool Board::writeIOCmd(unsigned short addr, bool dirRead, unsigned short data)
{	
	if (! usbDev->BulkOutEndPt)
		return false;

	if (bulkIOBuff.size() < 4) bulkIOBuff.resize(4);

	bulkIOBuff[0] = 0xbc95;
	bulkIOBuff[1] = addr;
	bulkIOBuff[2] = dirRead ?  0xFF00 : 0x00FF;
	bulkIOBuff[3] = data;
	long llen = 4 * sizeof(unsigned short);
	if (!usbDev->BulkOutEndPt->XferData((UCHAR*)&bulkIOBuff[0], llen))
		return false;

	return true;
}

bool Board::readReg(unsigned short addr, unsigned short &val)
{
	return read(addr, &val, 1);
}

bool Board::writeReg(unsigned short addr, unsigned short val)
{
	if (!writeIOCmd(addr, false, val))
	{
		return false;
	}

	return true;
}

bool Board::readReg24b(unsigned short addr,unsigned short& val)
{
	unsigned short w1 = (addr & 0xFF) << 8;
	unsigned short w2 = (addr & 0xFF00) >> 8 | 0x80;
	unsigned short r;
	if (!writeReg(0x1002, w1))
		return false;

	msleep(100);

	if (!writeReg(0x1003, w2))
		return false;

	msleep(300);

	unsigned short temp[1024];

	memset(temp, 0, sizeof(temp));
	if ( !read(0x1002, temp, 1024)  )
	{
		return false;
	}
	val = temp[0];

	//if ( !read(0x1002, &buff[0], 1024)  )
	//{
	//	return false;
	//}

	//	val = buff[0];

	return 	true;
}