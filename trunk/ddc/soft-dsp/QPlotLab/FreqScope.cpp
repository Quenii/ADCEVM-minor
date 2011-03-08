#include "stdafx.h"
#include "gkhy/qplotlib/FreqScope.hpp"
#include "CSLScope.h"

using namespace std;
using namespace gkhy::QPlotLab;

QFreqScope::QFreqScope(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/) :
QScope(parent, f)
{
	rawScope().Legend.Channels.Visible = false;	
	rawScope().Title.Visible = false;	
	rawScope().XAxis.AxisLabel.Visible = false;
	rawScope().YAxis.AxisLabel.Visible = false;

	//Yellow
	rawScope().Channels[0].Color = RGB(255, 255, 0);

}

QFreqScope::~QFreqScope()
{

}

void QFreqScope::setData(const vector<float>& data)
{
	if(data.size() > 0)
		rawScope().Channels[0].Data.SetYData(&data[0], (int)data.size()); 	
	
}

void QFreqScope::clear()
{
	if (rawScope().Channels.Count <= 0)
	{
		return;
	}
	for (int i = 0; i< rawScope().Channels.Count; ++i)
	{
		rawScope().Channels[i].Data.Clear();
	}
}
