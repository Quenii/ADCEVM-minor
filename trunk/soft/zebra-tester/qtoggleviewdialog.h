#ifndef QTOGGLEVIEWWIDGET_H
#define QTOGGLEVIEWWIDGET_H

#include <QDialog>

class QAction;

class QToggleViewDialog : public QDialog
{
	Q_OBJECT

public:
	QToggleViewDialog(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~QToggleViewDialog();

public:
	QAction* toggleViewAction () const { return m_toggleViewAction; }

protected:
	void changeEvent(QEvent *event);
	bool event(QEvent *event);

private slots:
	void slotToggleView(bool b);

private:
	QAction* m_toggleViewAction;
	
};

#endif // QTOGGLEVIEWWIDGET_H
