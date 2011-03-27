#ifndef QSTATICTESTPLOT_H
#define QSTATICTESTPLOT_H

#include <Qwt_Plot.h>
#include "ui_qstatictestplot.h"

class QStaticTestPlot : public QwtPlot
{
	 Q_OBJECT

public:
	QStaticTestPlot(QWidget *parent = 0);
	~QStaticTestPlot();

public slots:
	void setData();

private:
	Ui::QStaticTestPlotClass ui;
};

#endif // QSTATICTESTPLOT_H
