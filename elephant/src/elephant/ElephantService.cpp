#include "qsarserver.h"
#include "qsmsserver.h"

#include <QCoreApplication>
#include <qtserviceBase>
#include <QSettings>
#include <QProcess>
#include <QTimer>
#include <QStringList>
#include <QSettings>

class Service : public QtService<QCoreApplication>
{
public:
	Service(int argc, char **argv)
		: QtService<QCoreApplication>(argc, argv, "Elephant Service")
	{
		setServiceDescription("No description yet.");
		
		qApp->setApplicationName(serviceName());
		qApp->setOrganizationName("GKHY");
		qApp->setOrganizationDomain("www.gkhy.com.cn");


		setServiceFlags(QtService::Default);
		setStartupType(QtServiceController::AutoStartup);
	}

protected:
	void start()
	{
		QCoreApplication *app = application();
		
		QServer* tcpServer = createServer();
		if (tcpServer)
		{
			tcpServer->listen();

			if (!tcpServer->isListening()) {
				logMessage(QString("Failed to bind to port %1").arg(tcpServer->serverPort()), QtServiceBase::Error);
				app->quit();
			}
		}
	}	

	QServer* createServer()
	{
		QStringList args = QCoreApplication::arguments();

		QServer* ret = 0;
		
		while(args.size() > 0)
		{
			if (args.at(0) == "-m" || args.at(0) == "-mode")
			{
				if (args.size() >= 2)
				{
					QString mode = args.at(1).toLower();
					if (mode == "sar")
					{
						ret = new QSarServer(qApp);
					}
					else if (mode == "sms")
					{
						ret = new QSmsServer(qApp);
					}
					else
					{

					}
				}

				break;
			}
			else
			{
				args.pop_front();
			}			
		}

		if (ret == 0)
		{
			std::auto_ptr<QServer> ptr(new QSarServer(qApp));
			if (ptr->isEmulator()) // not real SAR
			{
       			ptr.reset();  // delete QSarServer before create QSmsServer
				ptr.reset(new QSmsServer); 
			}		

			if (ptr->isEmulator())
			{
				ptr.reset(0);
			}
			
			if(ptr.get() != 0)
				ret = ptr.release();
		}

		return ret;
	}
};

int main(int argc, char **argv)
{
	Service service(argc, argv);

	return service.exec(); 
}
