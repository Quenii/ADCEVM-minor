#include "mainwindow.h"
#include <QMessageBox>
#include <QtSingleApplication>



#ifdef MATLAB    //defined in AdcBoardTypes.hpp
#include "libalgo.h"

#pragma comment(lib, "libalgo.lib")
#pragma comment(lib, "mclmcrrt.lib")
#endif // MATLAB

int main(int argc, char *argv[])
{
	QtSingleApplication app(argc, argv);

	QApplication::setOrganizationName("quenii-roc");
	QApplication::setOrganizationDomain("quenii-roc.com");
	QApplication::setApplicationName("zebra-scope");

#ifdef MATLAB
	if (!(mclInitializeApplication(NULL, 0) && libalgoInitialize()))
	{
		QMessageBox::critical(NULL, "", "Failed to initialize Matlab.");

	}
#endif // MATLAB

	MainWindow w;

	bool ok = app.connect(&app, SIGNAL(messageReceived (const QString &)), &app, SLOT(activateWindow()));
	Q_ASSERT(ok);

	app.setActivationWindow(&w);
	if (app.isRunning())
		return !app.sendMessage(" ");

	w.showMaximized();

	int ret = app.exec();

#ifdef MATLAB
	libalgoTerminate();
	mclTerminateApplication();
#endif // MATLAB

	return ret;
}
