#include "qstatictestplot.h"
#include "qwt_plot_grid.h"

#include <QPen>

QStaticTestPlot::QStaticTestPlot(QWidget *parent)
	: QwtPlot(parent)
{
	ui.setupUi(this);

	setCanvasBackground(Qt::black);

	QwtPlotGrid* grid = new QwtPlotGrid();
	grid->setPen(QPen(Qt::darkGreen, 0, Qt::SolidLine));
	grid->enableX(true);
	grid->enableXMin(true);
	grid->enableY(true);
	grid->enableYMin(true);
	grid->attach(this);
}

QStaticTestPlot::~QStaticTestPlot()
{

}
