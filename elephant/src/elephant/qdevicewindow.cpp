#include "QDeviceWindow.h"

QDeviceWindow::QDeviceWindow(QWidget *parent)
	: QWidget(parent)
	, m_layout(0)
	, m_widget(0)
{
	ui.setupUi(this);	
}

QDeviceWindow::~QDeviceWindow()
{
	saveSettings(windowTitle());
}

void QDeviceWindow::loadSettings(QString path)
{
	ui.connectionBar->loadSettings(path + "/" + ui.connectionBar->windowTitle());
}

void QDeviceWindow::saveSettings(QString path)
{
	ui.connectionBar->saveSettings(path + "/" + ui.connectionBar->windowTitle());
}


void QDeviceWindow::setCentralWindow(QWidget *widget)
{
	if (m_widget)
	{
		delete m_widget;
		m_widget = 0;
	}

	if (m_layout)
	{
		delete m_layout;
		m_layout = 0;
	}

	m_widget = widget;

	//m_widget->setParent(this);

	QHBoxLayout* m_layout = new QHBoxLayout();
	m_layout->addWidget(m_widget);
	ui.devParamWindow->setLayout(m_layout);		
}

