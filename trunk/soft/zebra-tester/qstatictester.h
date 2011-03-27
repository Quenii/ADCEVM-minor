#ifndef QSTATICTESTER_H
#define QSTATICTESTER_H

#include <QObject>

class QStaticTester : public QObject
{
	Q_OBJECT

public:
	QStaticTester(QObject *parent);
	~QStaticTester();

private:
	
};

#endif // QSTATICTESTER_H
