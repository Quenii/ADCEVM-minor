#ifndef QGKHYMDIAREA_H
#define QGKHYMDIAREA_H

#include <QMdiArea>
#include <QSharedPointer>

class QGkhyMdiArea : public QMdiArea
{
	Q_OBJECT

public:
	QGkhyMdiArea(QWidget *parent);
	~QGkhyMdiArea();

protected:
	void paintEvent(QPaintEvent * event);
private:
	QSharedPointer<QPixmap> m_bkPic;
	//QBrush* m_bkBrush;	
};

#endif // QGKHYMDIAREA_H
