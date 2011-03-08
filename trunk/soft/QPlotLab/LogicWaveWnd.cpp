#include "stdafx.h"
#include "gkhy/qplotlib/LogicWaveWnd.hpp"
#include "gkhy/qplotlib/plotlab/CSLScope.h"

using namespace gkhy::QPlotLab;

LogicWaveWnd::LogicWaveWnd(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/) : QScope(parent, f) 
{
	USES_CONVERSION;

	CTSLScope& scope = rawScope();
	
	scope.Title.Visible = false;

	while(scope.Channels.Count > 0)	
	{
		scope.Channels.Delete(0);
	}

	m_arrayList.resize(16);

	scope.Channels.Add(m_arrayList.size());
	for (size_t i = 0; i < scope.Channels.Count; ++i)
	{
		scope.Channels[i].Color = RGB(0, 0 , 255);
		QString title = QString("Bit %1").arg(i);
		scope.Channels[i].Name = A2T(title.toLocal8Bit().constData());
	}
//	scope.CanRedoZoom

	//std::vector<unsigned short> data(10);	
	//for (int i = 0; i < data.size(); ++i)
	//{
	//	data[i] = unsigned short(i);
	//}

	//update(data);
}

LogicWaveWnd::~LogicWaveWnd()
{

}

void LogicWaveWnd::update(const std::vector<unsigned short> & xdata)
{
	CTSLScope& scope = rawScope();

	const int points2Display = 1024;

	for (int i = 0; i < 16; ++i)
	{
		m_x.resize(0);//xdata.size());
		m_y.resize(0);//xdata.size());

		for (int j = 0; j < xdata.size() && j < points2Display; ++j)
		{
			int mask = 1 << i;
			float val = ((xdata[j] & mask) ? .5f : 0) + i;
			m_x.push_back(j);
			m_y.push_back(val); 		
			m_x.push_back(j+1);
			m_y.push_back(val); 		

		}


		if (m_x.size() && m_y.size())
		{
			scope.Channels[i].Data.SetXYData(&m_x[0], &m_y[0], m_x.size());
		}
		//CTColor color = scope.Channels[0].Color;
	}
}