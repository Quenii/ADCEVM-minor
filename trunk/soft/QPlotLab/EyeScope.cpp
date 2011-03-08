#include "stdafx.h"
#include "gkhy/qplotlib/EyeScope.hpp"
#include "plotlab/CSLScope.h"
#include <QVBoxLayout>

using namespace std;
using namespace gkhy::QPlotLab;

QEyeScope::QEyeScope(QWidget* parent /* = 0 */, Qt::WindowFlags f /* = 0 */) :
QWidget(parent, f)
{
	QVBoxLayout* layout = new QVBoxLayout;
	layout->setSpacing(1);
	layout->setMargin(0);
	m_scopeI = new Scope(this, f);
	m_scopeQ = new Scope(this, f);
	layout->addWidget(m_scopeI);
	layout->addWidget(m_scopeQ);
	setLayout(layout);


	m_iSamplesPerSymbol = 6;
	m_iSymbolsPerTrace = 3;

	m_fYMax = 1.0f;
	m_fYMin = -1.0f;

	m_scopeI->rawScope().Legend.Channels.Visible = false;
	m_scopeQ->rawScope().Legend.Channels.Visible = false;
	m_scopeI->rawScope().Title.Visible = false;
	m_scopeQ->rawScope().Title.Visible = false;
	m_scopeI->rawScope().XAxis.AxisLabel.Visible = false;
	m_scopeQ->rawScope().XAxis.AxisLabel.Visible = false;
	m_scopeI->rawScope().YAxis.AxisLabel.Visible = false;
	m_scopeQ->rawScope().YAxis.AxisLabel.Visible = false;

	m_scopeI->rawScope().YAxis.Max.Value = m_fYMax;
	m_scopeI->rawScope().YAxis.Min.Value = m_fYMin;

	m_scopeI->rawScope().XAxis.Max.AutoScale = false;
	m_scopeI->rawScope().XAxis.Min.AutoScale = false;

	m_scopeQ->rawScope().XAxis.Max.AutoScale = false;
	m_scopeQ->rawScope().XAxis.Min.AutoScale = false;
}

QEyeScope::~QEyeScope()
{

}


void QEyeScope::setData(vector< complex< float > >& data)
{
	CTSLScope& scopeI = m_scopeI->rawScope();
	CTSLScope& scopeQ = m_scopeQ->rawScope();

	const size_t tracesAllowed = 20;
	const size_t samplesPerTrace =  m_iSamplesPerSymbol * m_iSymbolsPerTrace;

	size_t channelcnt = ((int)data.size()) / samplesPerTrace;
	if (channelcnt <= 0) return; 	 
	if (channelcnt > tracesAllowed) 
		channelcnt = tracesAllowed;


	if (((size_t)scopeI.Channels.Count) > channelcnt)
	{
		for (size_t i = scopeI.Channels.Count - 1; i >= channelcnt; --i)
		{
			scopeI.Channels.Delete((int)i);
			scopeQ.Channels.Delete((int)i);
		}
	}
	else if (((size_t)scopeI.Channels.Count) < channelcnt)
	{		
		for (size_t i = scopeI.Channels.Count; i < channelcnt; ++i)
		{
			scopeI.Channels.Add(1);
			scopeQ.Channels.Add(1);			
		}
	}	

	for (size_t i = 0; i < (size_t)scopeI.Channels.Count; ++i )
	{
		//Set  the color as Yellow
		if (scopeI.Channels[(int)i].Color != RGB(255, 255, 0))
			scopeI.Channels[(int)i].Color = RGB(255, 255, 0);

		if (scopeQ.Channels[(int)i].Color != RGB(255, 255, 0))
			scopeQ.Channels[(int)i].Color = RGB(255, 255, 0);
	}

	vector< float > x(samplesPerTrace + 1);
	vector< float > di(samplesPerTrace + 1);
	vector< float > dq(samplesPerTrace + 1);
	for (size_t j = 0; j < x.size(); ++j)
	{
		x[j] = (float)j;
	}

	scopeI.XAxis.Max.Value = samplesPerTrace;
	scopeI.XAxis.Min.Value = 0;

	scopeQ.XAxis.Max.Value = samplesPerTrace;
	scopeQ.XAxis.Min.Value = 0;

	for (size_t k = 0; k < channelcnt; ++k)
	{
		size_t tmp = k * samplesPerTrace;
		if (channelcnt - 1 == k)
		{  //The last channel needs "samplesPertrace - 1" points
			for ( size_t m = 0; m < samplesPerTrace; ++m)
			{			
				di[m] = data[tmp].real();
				dq[m] = data[tmp].imag();
				tmp = tmp + 1;
			}	
			scopeI.Channels[(int)k].Data.SetXYData(&x[0], &di[0], (unsigned int)(x.size() - 1));
			scopeQ.Channels[(int)k].Data.SetXYData(&x[0], &dq[0], (unsigned int)(x.size() - 1));
		} 
		else
		{
			for ( size_t m = 0; m <= samplesPerTrace; ++m)
			{			
				di[m] = data[tmp].real();
				dq[m] = data[tmp].imag();
				tmp = tmp + 1;
			}	
			scopeI.Channels[(int)k].Data.SetXYData(&x[0], &di[0], (unsigned int)(x.size()));
			scopeQ.Channels[(int)k].Data.SetXYData(&x[0], &dq[0], (unsigned int)(x.size()));
		}
	}

	return; 
}

void QEyeScope::clear()
{
	CTSLScope& scopeI = m_scopeI->rawScope();
	CTSLScope& scopeQ = m_scopeQ->rawScope();

	if (scopeI.Channels.Count <=0 || scopeQ.Channels.Count <= 0)
	{
		return;
	}
	for (int i = 0; i< scopeI.Channels.Count; ++i)
	{
		scopeI.Channels[i].Data.Clear();
	}
	for (int j = 0; j< scopeQ.Channels.Count; ++j)
	{
		scopeQ.Channels[j].Data.Clear();
	}
	return;
}




