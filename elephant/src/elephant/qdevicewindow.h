#ifndef QDeviceWindow_H
#define QDeviceWindow_H

#include "ui_QDeviceWindow.h"

#include <QWidget>
#include <QHBoxLayout>

class QDeviceWindow : public QWidget
{
	Q_OBJECT

public:
	QDeviceWindow(QWidget *parent = 0);
	~QDeviceWindow();

public:
	void setCentralWindow(QWidget* widget);

protected:
	void loadSettings(QString path);
	void saveSettings(QString path);

protected:
	Ui::DeviceWindowClass ui;
private:
	QHBoxLayout* m_layout;
	QWidget* m_widget;
};

#endif // QDeviceWindow_H
