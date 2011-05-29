#include "stdafx.h"
#include "gkhy/qplotlib/WaveWnd.hpp"
#include "gkhy/qplotlib/plotlab/CSLScope.h"

using namespace gkhy::QPlotLab;

WaveWnd::WaveWnd(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/) : QScope(parent, f) 
{
	//rawScope().Title.Text = _T("Time-domain Wave");
	rawScope().Title.Visible = false;
	rawScope().XAxis.AxisLabel.Text = _T("Time (ns)");
	
	rawScope().YAxis.AxisLabel.Text = _T("Amplitude (V)");

	//rawScope().XAxis.OnCustomLabel.Set(this, &WaveWnd::CustomXAxesLabel);



}

WaveWnd::~WaveWnd()
{

}

void WaveWnd::update(const std::vector<float> & xdata, const std::vector<float> & ydata)
{
	CTSLScope& scope = rawScope();
	if (scope.Channels.Count < 1)
		scope.Channels.Add(1);

	if (xdata.size() > 0 && ydata.size() > 0)
		scope.Channels[0].Data.SetXYData(&xdata[0], &ydata[0], (int)xdata.size());


}
