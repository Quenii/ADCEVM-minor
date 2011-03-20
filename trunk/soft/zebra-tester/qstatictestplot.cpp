#include "qstatictestplot.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"

#include <QPen>
#include <cmath>

QStaticTestPlot::QStaticTestPlot(QWidget *parent)
	: QwtPlot(parent)
{
	ui.setupUi(this);

	setCanvasBackground(Qt::black);
	setIntervalLength(10.0);
	/*setIntervalLength(10.0);

	QwtPlotGrid* grid = new QwtPlotGrid();
	grid->setPen(QPen(Qt::darkGreen, 0, Qt::SolidLine));


	grid->enableX(true);
	grid->enableXMin(true);
	grid->enableY(true);
	grid->enableYMin(true);
	grid->attach(this);
*/
	/*QwtPlotCurve sine("Sine");
	std::vector<float> xs;
	std::vector<float> ys;
	for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 10.0))
	{
		xs.push_back(x);
		ys.push_back(std::sin(x));
	}
	sine.setData(&xs[0],&ys[0],xs.size());
	sine.attach(&plot);

	plot.show();
	return a.exec();

	*/
}

QStaticTestPlot::~QStaticTestPlot()
{

}

