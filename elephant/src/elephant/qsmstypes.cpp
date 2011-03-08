#include "qsmstypes.h"

/*static const char* t1Key = "t1";
static const char* t2Key = "t2";
static const char* t3Key = "t3";
static const char* t4Key = "t4";
static const char* clkKey = "clk";
*/

void SmsConfig::fromSettings(const QSettings& s) 
{

	/*s.value(t1Key, 0).toInt();
	s.value(t2Key, 0).toInt();
	s.value(t3Key, 0).toInt();
	s.value(t4Key, 0).toInt();
	s.value(clkKey, 0).toInt();
	*/
}

void SmsConfig::toSettings(QSettings& s) const
{
	/*s.setValue(t1Key, QString::number(t1));
	s.setValue(t2Key, QString::number(t2));
	s.setValue(t3Key, QString::number(t3));
	s.setValue(t4Key, QString::number(t4));
	s.setValue(clkKey, QString::number(clk));
	*/
}
