#ifndef QDACTYPEDIALOG_H
#define QDACTYPEDIALOG_H

#include "ui_qdactypedialog.h"

#include <QDialog>
#include <QDataStream>

struct DacTypeSettings
{
	QString type;
	float va;
	float vd;
	int bitCount;
	float refVolt;
	float phase;	

	operator QVariant() const {	return QVariant::fromValue(*this); }
};
Q_DECLARE_METATYPE(DacTypeSettings);


inline QDataStream& operator<<(QDataStream& out, const DacTypeSettings& val)
{
	out << val.type;
	out << val.va;
	out << val.vd;
	out << val.bitCount;
	out << val.refVolt;
	out << val.phase;	

	return out;
}

inline QDataStream& operator>>(QDataStream& in, DacTypeSettings& val)
{
	in >> val.type;
	in >> val.va;
	in >> val.vd;
	in >> val.bitCount;
	in >> val.refVolt;
	in >> val.phase;	

	return in;
}

class QDacTypeDialog : public QDialog
{
	Q_OBJECT

public:
	QDacTypeDialog(QWidget *parent = 0);
	~QDacTypeDialog();

public:
	DacTypeSettings settings() { return m_settings; }

private:
	void setSettings(const DacTypeSettings& val);

private:
	Ui::QDacTypeDialogClass ui;

	DacTypeSettings m_settings;
};

#endif // QDACTYPEDIALOG_H
