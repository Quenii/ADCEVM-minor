#ifndef QDYNAMICTESTPLOT_H
#define QDYNAMICTESTPLOT_H

#include <Qwt_Plot.h>
#include "ui_qdynamictestplot.h"

class QDynamicTestPlot : public QwtPlot
{
	// Q_OBJECT

public:
	QDynamicTestPlot(QWidget *parent = 0);
	~QDynamicTestPlot();

private:
	Ui::QDynamicTestPlotClass ui;
};

#endif // QDYNAMICTESTPLOT_H