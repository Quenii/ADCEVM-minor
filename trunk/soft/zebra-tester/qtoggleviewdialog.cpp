#include "qtoggleviewdialog.h"

#include <QAction>
#include <Qevent>

QToggleViewDialog::QToggleViewDialog(QWidget *parent/* = 0*/, Qt::WindowFlags flags /*= 0*/)
: QDialog(parent, flags)
{
	m_toggleViewAction = new QAction(this);
	m_toggleViewAction->setCheckable(true);
	m_toggleViewAction->setChecked(false);
	m_toggleViewAction->setText(windowTitle());
	bool okay = false;

	/*okay = QObject::connect(m_toggleViewAction, SIGNAL(triggered(bool)),
	SLOT(slotToggleView(bool))); Q_ASSERT(okay);
	*/

	okay = QObject::connect(m_toggleViewAction, SIGNAL(toggled(bool)),
		SLOT(slotToggleView(bool))); Q_ASSERT(okay);
}

QToggleViewDialog::~QToggleViewDialog()
{

}

void QToggleViewDialog::slotToggleView(bool b)
{
	if (b != isVisible()) {
		if (b)
			show();
		else
			close();
	}
}

void QToggleViewDialog::changeEvent(QEvent *event)
{
	switch (event->type())
	{
	case QEvent::WindowTitleChange:
		m_toggleViewAction->setText(windowTitle());
		break;

	default:
		break;
	}

	QWidget::changeEvent(event);
}

bool QToggleViewDialog::event(QEvent *event)
{
	switch (event->type()) 
	{
	case QEvent::Hide:
		m_toggleViewAction->setChecked(false);
		break;

	case QEvent::Show:
		m_toggleViewAction->setChecked(true);	

		break;
	default:
		break;
	}

	return QWidget::event(event);
}