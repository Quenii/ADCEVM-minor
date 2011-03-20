#include "qstatictestplot.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_canvas.h"
#include "qwt_scale_widget.h"

#include <QPen>
#include <cmath>

QStaticTestPlot::QStaticTestPlot(QWidget *parent)
	: QwtPlot(parent)
{
	ui.setupUi(this);

	setTitle(QString::fromLocal8Bit("��̬��������"));

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
	std::vector<double> xs;
	std::vector<double> ys;
	for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 100.0))
	{
		xs.push_back(x);
		ys.push_back(std::sin(x));
	}
	sine.setData(&xs[0],&ys[0],xs.size());
	sine.attach(this);


}

QStaticTestPlot::~QStaticTestPlot()
{

}

