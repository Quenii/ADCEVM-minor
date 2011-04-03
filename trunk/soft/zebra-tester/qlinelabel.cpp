#include "qlinelabel.h"

#include <qlineedit>

QLineLabel::QLineLabel(QWidget *parent)
	: QLabel(parent)
{
	ui.setupUi(this);

	QLineEdit w;
	m_sizeHint = w.sizeHint();
	m_minimumSizeHint = w.minimumSizeHint();

	// m_minimumSizeHint = m_sizeHint = QSize(0, 0);
}

QLineLabel::~QLineLabel()
{

}

QSize QLineLabel::sizeHint() const
{
	return m_sizeHint;
}

QSize QLineLabel::minimumSizeHint() const
{
	return m_minimumSizeHint;
}
