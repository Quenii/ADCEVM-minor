#ifndef QDACTYPEWIDGET_H
#define QDACTYPEWIDGET_H

#include <QWidget>
#include "ui_qdactypewidget.h"
#include "qdactypedialog.h"

class QDacTypeWidget : public QWidget
{
	Q_OBJECT

public:
	QDacTypeWidget(QWidget *parent = 0);
	~QDacTypeWidget();

public:
	void setDacTypeSettings(const DacTypeSettings& val);
	// DacTypeSettings dacTypeSettings() const { return m_dacTypeSettings; }

private:
	Ui::QDacTypeWidgetClass ui;
	// DacTypeSettings m_dacTypeSettings;
};

#endif // QDACTYPEWIDGET_H
