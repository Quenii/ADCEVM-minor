#pragma once

#include <QValidator>

class QString;

class QIPValidator :public QValidator
{
	Q_OBJECT

public:
	QIPValidator(QObject * parent);
	~QIPValidator(void);

public:
	QValidator::State validate(QString & input, int& pos)const;

private:
	QValidator::State FieldValidate(const QString& field) const;
};
