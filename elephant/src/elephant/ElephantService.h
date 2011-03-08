#include <QCoreApplication>
#include <QtServiceBase>

class ElephantService : public QtService<QCoreApplication>
{
public:
	ElephantService(int argc, char **argv);
	~ElephantService();

protected:
	void start();
	void stop();
};