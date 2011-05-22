#ifndef QSTATICTESTPLOT_H
#define QSTATICTESTPLOT_H

#include "ui_qstatictestplot.h"

#include <Qwt_Plot.h>
#include <QSharedPointer>

class QwtPlotCurve;
class QStaticTester;

class QStaticTestPlot : public QwtPlot
{
	 Q_OBJECT

public:
	QStaticTestPlot(QWidget *parent = 0);
	~QStaticTestPlot();

public slots:
	void reset();
	void setData();

private:
	Ui::QStaticTestPlotClass ui;

	QwtPlotCurve* ideaCurve;
	QwtPlotCurve* realCurve;
};

#endif // QSTATICTESTPLOT_H
