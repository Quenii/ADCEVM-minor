#include "QGkhyMdiArea.h"

#include <QRegion>
#include <QRect>
#include <QPaintEvent>
#include <QBrush>
#include <QSharedPointer>
#include <QPixmap>
#include <QPainter>

QGkhyMdiArea::QGkhyMdiArea(QWidget *parent)
	: QMdiArea(parent)
{
	m_bkPic = QSharedPointer<QPixmap>(0);
}

QGkhyMdiArea::~QGkhyMdiArea()
{

}

void QGkhyMdiArea::paintEvent(QPaintEvent * paintEvent)
{
	QBrush bk = background();
	if (0 == m_bkPic || m_bkPic->size() != size())
	{
		m_bkPic.clear();
		m_bkPic = QSharedPointer<QPixmap>(new QPixmap(size()));
		
		QPainter painter(m_bkPic.data());

		QImage img(":/Resources/gkhy_gray_banner.png");		
		
		QFont font("Verdana", 10);
		
		painter.setFont(font);		
		// We will do something just as a doctor does in his O.R. when he
		// gets a pot from a pig's face and then paints it onto a man's whole
		// face.
		painter.fillRect(m_bkPic->rect(), QColor(img.pixel(0, 0)));
		painter.drawText(m_bkPic->rect(), Qt::AlignCenter,
			"Beijing Transuniverse Space Technology Co., Ltd");
		
		QRect imgSrcRect = img.rect();
		QPoint offset = m_bkPic->rect().center() - imgSrcRect.center();
		QRect imgDestRect = imgSrcRect.translated(offset);
		painter.drawImage(imgDestRect, img);

	}
	
	bk.setTexture(*m_bkPic);
	setBackground(bk);
	
	QMdiArea::paintEvent(paintEvent);
}

