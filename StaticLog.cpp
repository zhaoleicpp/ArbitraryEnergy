// StaticLog.cpp : 实现文件
//

#include "stdafx.h"
#include "ArbitraryEnergy.h"
#include "StaticLog.h"
#include "Type.h"
#include "Simulate.h"



// CStaticLog

IMPLEMENT_DYNAMIC(CStaticLog, CStatic)

CStaticLog::CStaticLog()
{

}

CStaticLog::~CStaticLog()
{
}


BEGIN_MESSAGE_MAP(CStaticLog, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CStaticLog 消息处理程序




void CStaticLog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	Paint(dc);
}
void CStaticLog::Paint(CDC &dc)
{
	CRect rect;
	GetClientRect(&rect);
	int width,height;
	width=rect.Width();
	height=rect.Height();
	height-=20;
	if(width<=1)
		return ;
	if(height<=1)
		return ;
	if(g_simulate.m_log_count<=1)
		return ;

	CDC * dc_pointer;
	if(&dc)
		dc_pointer=&dc;
	else
		dc_pointer=new CClientDC(this);

	dc_pointer->Rectangle(0,0,width,height+2);
	static const COLORREF density_color=RGB(255,0,0);
	static const COLORREF temperature_color=RGB(0,128,0);
	static const COLORREF lawson_color=RGB(0,0,128);
	dc_pointer->SetTextColor(density_color);
	dc_pointer->TextOut(0,height+2,_T("density"));
	dc_pointer->SetTextColor(temperature_color);
	dc_pointer->TextOut(80,height+2,_T("temperature"));
	dc_pointer->SetTextColor(lawson_color);
	dc_pointer->TextOut(160,height+2,_T("lawson"));
	double min_density,max_density;
	double min_temperature,max_temperature;
	double min_lawson,max_lawson;
	min_density=min_temperature=min_lawson=1e200;
	max_density=max_temperature=max_lawson=-1e200;
	for(int loop=0;loop<2;loop++)
	{
		for(int x=0;x<width;x++)
		{
			int index;
			index=(g_simulate.m_log_count-1)*x/(width-1);
			auto &log=g_simulate.m_log[index];
			double density;
			double temperature;
			double lawson;
			density=log.density;
			temperature=log.temperature;
			lawson=log.lawson;
			if(loop==0)
			{
				if(density<min_density)
					min_density=density;
				if(density>max_density)
					max_density=density;
				if(temperature<min_temperature)
					min_temperature=temperature;
				if(temperature>max_temperature)
					max_temperature=temperature;
				if(lawson<min_lawson)
					min_lawson=lawson;
				if(lawson>max_lawson)
					max_lawson=lawson;
			}
			else
			{
				if(min_density!=max_density)
				{
					int y;
					y=(int)((height-1)*(density-min_density)/(max_density-min_density)+0.5);
					y=height-1-y;
					dc_pointer->SetPixel(x,y,density_color);
				}
				if(min_temperature!=max_temperature)
				{
					int y;
					y=(int)((height-1)*(temperature-min_temperature)/(max_temperature-min_temperature)+0.5);
					y=height-1-y;
					dc_pointer->SetPixel(x,y,temperature_color);
				}
				if(min_lawson!=max_lawson)
				{
					int y;
					y=(int)((height-1)*(lawson-min_lawson)/(max_lawson-min_lawson)+0.5);
					y=height-1-y;
					dc_pointer->SetPixel(x,y,lawson_color);
				}
			}
		}
	}

	if(!&dc)
	{
		delete (CClientDC*)dc_pointer;
		dc_pointer=NULL;
	}
}