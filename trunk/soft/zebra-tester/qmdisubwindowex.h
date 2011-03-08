#ifndef QMDISUBWINDOWEX_H
#define QMDISUBWINDOWEX_H

#include <QMdiSubWindow>

class QAction;
class QEvent;

class QMdiSubWindowEx : public QMdiSubWindow
{
	Q_OBJECT

public:
	QMdiSubWindowEx(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~QMdiSubWindowEx();

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

#endif // QMDISUBWINDOWEX_H
