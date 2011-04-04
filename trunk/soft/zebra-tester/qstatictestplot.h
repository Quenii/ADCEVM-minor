#ifndef QSTATICTESTPLOT_H
#define QSTATICTESTPLOT_H

#include "ui_qstatictestplot.h"

#include <Qwt_Plot.h>
#include <QSharedPointer>

class QwtPlotCurve;
class QTester;

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

	QSharedPointer<QTester> tester;

};

#endif // QSTATICTESTPLOT_H
