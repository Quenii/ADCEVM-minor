#include "qelephantmainwindow.h"
#include "AboutDialog.h"
#include "qmdisubwindowex.h"
#include "qsardevicewindow.h"
#include "qsmsdevicewindow.h"

#include <QApplication>


int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	app.setApplicationName("Elephant");
	app.setOrganizationName("GKHY");
	app.setOrganizationDomain("www.gkhy.com.cn");	

	QElephantMainWindow elephant;
	elephant.showMaximized();

	return app.exec();
}

QElephantMainWindow::QElephantMainWindow(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	addMdiWindow(new QSarDeviceWindow(this), ui.pushButtonSarEmulator);
	addMdiWindow(new QSmsDeviceWindow(this), ui.pushButtonStorageEmulator);
}

QElephantMainWindow::~QElephantMainWindow()
{

}

void QElephantMainWindow::addMdiWindow(QWidget* widget, QPushButton* btn)
{
	QMdiSubWindowEx* subWindow = new QMdiSubWindowEx(this, Qt::MSWindowsFixedSizeDialogHint); 
	subWindow->setWidget(widget);
	ui.mdiArea->addSubWindow(subWindow);
	ui.menuWindow->addAction(subWindow->toggleViewAction());

	if (btn)
	{
		bool ok = connect(btn, SIGNAL(clicked()),
			subWindow->toggleViewAction(), SLOT(toggle()));
		Q_ASSERT(ok);
	}
}

void QElephantMainWindow::on_actionAbout_triggered(bool checked)
{
	AboutDialog aboutDlg;
	aboutDlg.exec();
}


