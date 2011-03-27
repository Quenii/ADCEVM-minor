#include "qstatictestplot.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_canvas.h"
#include "qwt_scale_widget.h"
#include "qstatictester.h"

#include <QPen>
#include <cmath>

QStaticTestPlot::QStaticTestPlot(QWidget *parent)
	: QwtPlot(parent)
{
	ui.setupUi(this);

	setTitle(QString::fromLocal8Bit("¾²Ì¬²âÊÔÇúÏß"));

	setCanvasBackground(Qt::black);
	
	QwtPlotGrid* grid = new QwtPlotGrid();
	grid->setPen(QPen(Qt::darkGreen, 0, Qt::SolidLine));
	grid->enableX(true);
	grid->enableXMin(true);
	grid->enableY(true);
	grid->enableYMin(true);
	grid->attach(this);

	QwtPlotCurve& sine = * new QwtPlotCurve("Sine");
	sine.setPen(QPen(Qt::red, 0, Qt::SolidLine));
	static std::vector<double> xs;
	static std::vector<double> ys;
	for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 100.0))
	{
		xs.push_back(x);
		ys.push_back(std::sin(x));
	}
	sine.setRawSamples(&xs[0],&ys[0],xs.size());
	sine.attach(this);

	QStaticTester* staticTester = &(QStaticTester::instance());
	bool ok = connect(staticTester, SIGNAL(newData()), this, SLOT(setData()));
	Q_ASSERT(ok);

	bool ok = connect(staticTester, SIGNAL(started()), this, SLOT(reset()));
	Q_ASSERT(ok);

}

QStaticTestPlot::~QStaticTestPlot()
{

}

void QStaticTestPlot::reset()
{

}

void QStaticTestPlot::setData()
{

}