#include "stdafx.h"
#include "gkhy/qplotlib/StaticTestPlot.hpp"
#include "CSLScope.h"

using namespace std;
using namespace gkhy::QPlotLab;

QStaticTestPlot::QStaticTestPlot(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/) :
QScope(parent, f)
{
	USES_CONVERSION;

	CTSLScope& scope = rawScope();

	scope.Legend.Channels.Visible = true;	
	scope.Title.Visible = false;	
	scope.XAxis.AxisLabel.Visible = false;
	scope.YAxis.AxisLabel.Visible = false;

	while(scope.Channels.Count > 0)	
	{
		scope.Channels.Delete(0);
	}

	scope.Channels.Add(2);

 	scope.Channels[0].Name = A2T("ideal"); 
	scope.Channels[1].Name = A2T("measured"); 

}

QStaticTestPlot::~QStaticTestPlot()
{

}

void QStaticTestPlot::addData(float ideal, float measured)
{
	m_ideal.push_back(ideal);
	m_measured.push_back(measured);

	if(m_ideal.size() > 0)
		rawScope().Channels[0].Data.SetYData(&m_ideal[0], (int)m_ideal.size()); 	

	if(m_measured.size() > 0)
		rawScope().Channels[0].Data.SetYData(&m_measured[0], (int)m_measured.size()); 	

}

void QStaticTestPlot::clear()
{
	m_ideal.swap(std::vector<float>());
	m_measured.swap(std::vector<float>());

	if (rawScope().Channels.Count <= 0)
	{
		return;
	}
	for (int i = 0; i< rawScope().Channels.Count; ++i)
	{
		rawScope().Channels[i].Data.Clear();
	}
}
