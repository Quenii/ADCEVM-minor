#include "stdafx.h"
#include "gkhy/qplotlib/ConstScope.hpp"
#include "gkhy/qplotlib/plotlab/CSLScope.h"
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QResizeEvent>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QStyle>

using namespace std;
using namespace gkhy::QPlotLab;

class SquareWidgetContainer : public QScrollArea
{
public:
	SquareWidgetContainer(QWidget* parent = 0) : QScrollArea(parent)
	{		
		setAlignment(Qt::AlignCenter);	
		//setBackgroundRole(QPalette::Dark);
	}

private:
	void resizeEvent(QResizeEvent *event)
	{
		QSize viewportSize = viewport()->size();
		int size = qMin(viewportSize.width(), viewportSize.height());
		QSize square(size, size);
		widget()->resize(square);

		QScrollArea::resizeEvent(event);
	}
};

QConstScope::QConstScope(QWidget* parent /* = 0 */, Qt::WindowFlags f /* = 0 */):
QWidget(parent, f)
{	
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(0);
	layout->setSpacing(0);
	setLayout(layout);

	m_scopeContainer = new SquareWidgetContainer;
	layout->addWidget(m_scopeContainer);
	
	m_scope = new Scope;
	m_scopeContainer->setWidget(m_scope);
	

	float mag = .5f;

	m_fXMax = mag;	
	m_fXMin = -mag;
	m_fYMax = mag;
	m_fYMin = -mag;	

	m_scope->rawScope().Legend.Channels.Visible = false;	
	m_scope->rawScope().Title.Visible = false;	
	m_scope->rawScope().XAxis.AxisLabel.Visible = false;
	m_scope->rawScope().YAxis.AxisLabel.Visible = false;	

	m_scope->rawScope().XAxis.Max.AutoScale = false;
	m_scope->rawScope().XAxis.Min.AutoScale = false;
	m_scope->rawScope().YAxis.Max.AutoScale = false;	
	m_scope->rawScope().YAxis.Min.AutoScale = false;
	

	m_scope->rawScope().YAxis.Max.Value = m_fYMax;
	m_scope->rawScope().YAxis.Min.Value = m_fYMin;

	m_scope->rawScope().XAxis.Max.Value = m_fXMax;
	m_scope->rawScope().XAxis.Min.Value = m_fXMin;

	m_scope->rawScope().XAxis.Visible = true;
	m_scope->rawScope().YAxis.Visible = true;

	//m_scope->rawScope().ToolBar.Visible = false;
	m_scope->rawScope().Zooming.MouseZoom = false;

	m_scope->rawScope().Zooming.Mode = zmBoth;

	m_scope->rawScope().Channels[ 0 ].ChannelMode = cmPoint;

	//Set points size
	m_scope->rawScope().Channels[ 0 ].Points.Visible = true;
	m_scope->rawScope().Channels[ 0 ].Points.Size = 1;

	//Yellow
	m_scope->rawScope().Channels[0].Color = RGB(255, 255, 0);	
}

QConstScope::~QConstScope()
{
}


void QConstScope::setData(float data[], int size)
{
	if (m_di.size() != size / 2) m_di.resize(size / 2);
	if (m_dq.size() != size / 2) m_dq.resize(size / 2);

	for (int k = 0; k < size / 2; ++k)
	{

		m_di[k] = data[2*k];
		m_dq[k] = data[2*k+1];	
	}		
	
	showIQ();
}

void QConstScope::setData(vector< complex< float > >& data)
{	
	if(data.size() <= 0) return;

	if (m_di.size() != data.size())
	{
		m_di.resize(data.size());
	}

	if (m_dq.size() != data.size())
	{
		m_dq.resize(data.size());
	}

	for (size_t k = 0; k < data.size(); k ++)
	{

		m_di[k] = data[k].real();
		m_dq[k] = data[k].imag();	
	}	

	showIQ();
}

void QConstScope::showIQ()
{
	m_scope->rawScope().Channels[0].Data.AddXYData(&m_di[0], &m_dq[0], (unsigned int)(m_di.size()), false);
	
	m_scope->rawScope().Channels[0].Data.AddXYPoint(m_fXMax, m_fYMax); // NE
	m_scope->rawScope().Channels[0].Data.AddXYPoint(m_fXMax, m_fYMin); // SE
	m_scope->rawScope().Channels[0].Data.AddXYPoint(m_fXMin, m_fYMax); // NW
	m_scope->rawScope().Channels[0].Data.AddXYPoint(m_fXMin, m_fYMin); // SW
}

void QConstScope::clear()
{
	if (m_scope->rawScope().Channels.Count <= 0)
	{
		return;
	}
	for (int i = 0; i< m_scope->rawScope().Channels.Count; ++i)
	{
		m_scope->rawScope().Channels[i].Data.Clear();
	}
	return;
}