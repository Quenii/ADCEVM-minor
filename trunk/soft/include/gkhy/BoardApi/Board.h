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

struct BoardInfo 
{
	int usbAddr;
	QString devName;
	QString infName;
};

class Board : public QObject
{
	Q_OBJECT

private:
	static Board* _inst;

public:
	static Board* instance() 
	{
		if (!_inst)
		{
			_inst = new Board(0);
		}

		return _inst;
	}

public:	
	virtual ~Board();

private:
	Board(QObject* parent = 0);
	Q_DISABLE_COPY(Board);

public:
	bool readReg(unsigned short addr,unsigned short& val);
	bool writeReg(unsigned short addr,unsigned short val);

	bool readReg24b(unsigned short addr,unsigned short& val);
	bool writeReg24b(unsigned short addr,unsigned short val);

protected:	
	// len - number of unsigned-short's
	bool read(unsigned short addr, unsigned short* buf, unsigned int len);
	// len - number of unsigned-short's
	//bool write(unsigned int addr, const unsigned short* buf, int len);


private:
	bool writeIOCmd(unsigned short addr, bool dirRead, unsigned short data);
	unsigned short CalcReg(float v);

signals:
	void devListChanged(const QList<BoardInfo>& lst);

public slots:
		bool open(int usbAddr);
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

