#pragma once

#include "boardapi_global.h"

#pragma once

#include <QObject>
#include <QString>
#include <QList>
#include <QWidget>
#include <vector>
#include <QSettings>

class CCyUSBDevice;
class DummyWidget;
class QObject;
class QEvent;

struct BOARDAPI_EXPORT BoardInfo 
{
	int usbAddr;
	QString devName;
	QString infName;
};

class BOARDAPI_EXPORT Board : public QObject
{
	Q_OBJECT

public:
	Board(QObject* parent = 0);
	virtual ~Board();

private:	
	Q_DISABLE_COPY(Board);

public:
	bool open(int usbAddr = 0);
	void close();
	bool isOpen();

	bool readReg(unsigned short addr,unsigned short& val);
	bool writeReg(unsigned short addr,unsigned short val);

	bool readReg24b(unsigned short addr,unsigned short& val);
	bool writeReg24b(unsigned short addr,unsigned short val);
	int setVoltage(int adcChannel, int dacChannel, float v);

signals:
	void devListChanged(const QList<BoardInfo>& lst);

protected:	
	// len - number of unsigned-short's
	bool read(unsigned short addr, unsigned short* buf, unsigned int len);
	// len - number of unsigned-short's
	bool write(unsigned short addr, const unsigned short* buf, unsigned int len);

private:
	bool writeIOCmd(unsigned short addr, bool dirRead, unsigned short data);

private slots:
    void devChanged();

private:
	CCyUSBDevice* usbDev;
	DummyWidget* widget;
	std::vector<unsigned short> bulkIOBuff;
	std::vector<unsigned short> buff;

	const static int buffer_cnt = 32 * 1024;
	const float pi;
};

