#ifndef QINSTTESTPLOT_H
#define QINSTTESTPLOT_H

#include <QwtPlot.h>
#include "ui_qinsttestplot.h"

class QInstTestPlot : public QwtPlot
{
	Q_OBJECT

public:
	QInstTestPlot(QWidget *parent = 0);
	~QInstTestPlot();

private:
	Ui::QInstTestPlotClass ui;
};

#endif // QINSTTESTPLOT_H
