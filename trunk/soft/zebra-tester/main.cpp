#include "mainwindow.h"
#include "qdactypedialog.h"

#include <QApplication>
#include <QMetaType>

#define REGISTER_METATYPE_HELPER( type ) \
	qRegisterMetaType<type>(); \
	qRegisterMetaType<type>(#type); \
	qRegisterMetaTypeStreamOperators<type>(#type)


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QApplication::setOrganizationName("quenii");
	QApplication::setOrganizationDomain("quenii.com");
	QApplication::setApplicationName("dac-analyzer");

	REGISTER_METATYPE_HELPER(DacTypeSettings);

	MainWindow w;
	w.showMaximized();
	return a.exec();
}
