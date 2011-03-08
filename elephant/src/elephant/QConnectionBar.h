#pragma once

#include "ui_QConnectionBar.h"
#include <QWidget>

#include "gkhy/pagoda/QRebufferedTcpSocket.h"

using namespace gkhy::pagoda;

class QConnectionBar : public QWidget
{
	Q_OBJECT

public:
	QConnectionBar(QWidget *parent = 0);
	~QConnectionBar();

public:
	void loadSettings(QString path);
	void saveSettings(QString path);
	void setSocket(QRebufferedTcpSocket* socket);
	void enableConnection(bool enable);
	bool isConnectionEnabled() { return m_enableConnection; }

protected:
	void timerEvent(QTimerEvent *event);

private slots:
	void slot_tcpSocket_connected();
	void slot_tcpSocket_disconnected();
	void slot_tcpSocket_error();
	void slot_tcpSocket_stateChanged(QAbstractSocket::SocketState socketState);
	void on_enableConnectionPushButton_clicked();

private:
	Ui::ConnectionBarClass ui;
	QRebufferedTcpSocket* m_tcpSocket;
	bool m_enableConnection;
	QString m_settingsPath;
};

