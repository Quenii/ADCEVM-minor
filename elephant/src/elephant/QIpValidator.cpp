#include "QIPValidator.h"

#include <QString>

QIPValidator::QIPValidator(QObject * parent):
QValidator(parent)
{
}

QIPValidator::~QIPValidator(void)
{

}

QValidator::State QIPValidator::FieldValidate(const QString& field) const
{
	if (field.trimmed().isEmpty())
	{
		return QValidator::Intermediate;
	}

	bool ok = false;
	unsigned int int0 = field.toUInt(&ok);
	if (ok && int0 >= 0 && int0 <= 255)
	{
		return QValidator::Acceptable;
	}

	return QValidator::Invalid;
}

QValidator::State QIPValidator::validate(QString& input, int& pos) const
{
 	bool ok;
 	//将地址分成四段
	QString str0 = input.section('.',0,0).trimmed();
	QString str1 = input.section('.',1,1).trimmed();
	QString str2 = input.section('.',2,2).trimmed();
	QString str3 = input.section('.',3,3).trimmed();

	QValidator::State states[] = { 
		FieldValidate(str0),
		FieldValidate(str1),
		FieldValidate(str2),
		FieldValidate(str3)
	};

	for (int i = 0; i < sizeof(states) / sizeof(states[0]); ++i)
	{
		if (states[i] != QValidator::Acceptable)
			return states[i];
	}

	return QValidator::Acceptable;
	

 //	//不允许第一段数字和最后一段数字的第一个字符为0
 //	if(str0.isEmpty() || QChar('0') == str0[0])
 //	{
	//	input = QString("%1:%2:%3:%4").arg("").arg(str1).arg(str2).arg(str3);
	//	return QValidator::Invalid;
 //	}
 //	if(str3.isEmpty() || QChar('0') == str3[0])
	//{
	//	input = QString("%1:%2:%3:%4").arg(str0).arg(str1).arg(str2).arg("");
	//	return QValidator::Invalid;
 //	}

	//// 当第二段和第三段的第一个字符等于0时，不允许再输入第二个字符
	//if(str1.isEmpty() || QChar('0') == str1[0])
	//{
	//	if(str1.length() > 1)
	//	{
	//		input.replace(str0.length()+2,1,QString(""));
	//		return QValidator::Invalid;
	//	}
	//}
 //	if(str2.isEmpty() || QChar('0') == str2[0])
 //	{
	//	if(str2.length() > 1)
	//	{
	//		input.replace(str0.length()+str1.length()+2,1,QString(""));
	//		return QValidator::Invalid;
	//	}
 //	}
 //
	//// 只允许输入A/B/C 段的IP地址
 //	int addr0 = str0.toInt(&ok,10);	
 //	if ( (addr0<0)||(addr0>223) )
 //	{
 //		input.replace(0,str0.length(),QString(""));
	//	return QValidator::Invalid;
 //	}
 //	
 //	int addr1 = str1.toInt(&ok,10);
 //	if( (addr1<0)||(addr1>255) )
 //	{
 //		input.replace(str0.length()+1,str1.length(),QString(""));
	//	return QValidator::Invalid;
 //	}
 //	
 //	int addr2 = str2.toInt(&ok,10);
 //	if( (addr2<0)||(addr2>255) )
 //	{
 //		input.replace(str0.length()+str1.length()+2,str2.length(),QString(""));
	//	return QValidator::Invalid;
 //	}
 //	
 //	int addr3 = str3.toInt(&ok,10);
 //	if( (addr3<0)||(addr3>254) )
 //	{
 //		input.replace(str0.length()+str1.length()+str2.length()+3,str3.length(),QString(""));
	//	return QValidator::Invalid;
 //	}

	//return QValidator::Acceptable;
}
