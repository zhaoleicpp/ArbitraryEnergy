
// ArbitraryEnergyView.cpp : implementation of the CArbitraryEnergyView class
//

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Type.h"
#include "Misc.h"
#include "Sphere.h"
#include "Kettle.h"
#include "Electret.h"
#include "resource.h"
#include "DialogTool.h"
#include "Simulate.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ArbitraryEnergy.h"
#endif

#include "ArbitraryEnergyDoc.h"
#include "ArbitraryEnergyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CArbitraryEnergyView

IMPLEMENT_DYNCREATE(CArbitraryEnergyView, CView)

BEGIN_MESSAGE_MAP(CArbitraryEnergyView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CArbitraryEnergyView construction/destruction

CArbitraryEnergyView::CArbitraryEnergyView()
{
	// TODO: add construction code here
	C3DWindow::SetSize(g_kettle.GetOuterRadius()*5);
	C3DWindow::UpdateLook();
	m_round_face_min=m_round_face_max=0;
	m_round_face_string[0]=_T('\0');
}

CArbitraryEnergyView::~CArbitraryEnergyView()
{
}

BOOL CArbitraryEnergyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CArbitraryEnergyView drawing

void CArbitraryEnergyView::OnDraw(CDC* pDC)
{
	CArbitraryEnergyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	DoPaint(*pDC);
}


// CArbitraryEnergyView printing

BOOL CArbitraryEnergyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CArbitraryEnergyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CArbitraryEnergyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CArbitraryEnergyView diagnostics

#ifdef _DEBUG
void CArbitraryEnergyView::AssertValid() const
{
	CView::AssertValid();
}

void CArbitraryEnergyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CArbitraryEnergyDoc* CArbitraryEnergyView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArbitraryEnergyDoc)));
	return (CArbitraryEnergyDoc*)m_pDocument;
}
#endif //_DEBUG


// CArbitraryEnergyView message handlers


void CArbitraryEnergyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nFlags&MK_LBUTTON)
	{
		C3DWindow::OnMouseDrag(point.x,point.y);
		DoPaint();
	}
	__super::OnMouseMove(nFlags, point);
}


void CArbitraryEnergyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	C3DWindow::OnLeftButtonDown(point.x,point.y);
	DoPaint();
	__super::OnLButtonDown(nFlags, point);
}


BOOL CArbitraryEnergyView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	C3DWindow::OnMouseWheel(zDelta);
	DoPaint();
	return __super::OnMouseWheel(nFlags, zDelta, pt);
}
void CArbitraryEnergyView::OnSize(UINT nType, int cx, int cy)
{
	C3DWindow::SetSize(cx,cy);
}

BOOL CArbitraryEnergyView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;//CScrollView::OnEraseBkgnd(pDC);
}
void CArbitraryEnergyView::DoPaint(CDC &dc)
{
	C3DWindow::Render();
	CDC *dc_pointer;
	if(&dc)
		dc_pointer=&dc;
	else
		dc_pointer=(CDC*)new CClientDC(this);
	BITMAPINFO info;
	info.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth=C3DWindow::GetWidth();
	info.bmiHeader.biHeight=C3DWindow::GetHeight();
	info.bmiHeader.biPlanes=1;
	info.bmiHeader.biBitCount=24;
	info.bmiHeader.biCompression=0;
	info.bmiHeader.biSizeImage=C3DWindow::GetWidth()*C3DWindow::GetHeight()*3;
	info.bmiHeader.biXPelsPerMeter=40000;
	info.bmiHeader.biYPelsPerMeter=30000;
	info.bmiHeader.biClrUsed=100;
	info.bmiHeader.biClrImportant=100;
	::SetDIBitsToDevice(dc_pointer->m_hDC,0,0,C3DWindow::GetWidth(),C3DWindow::GetHeight(),0,0,0,C3DWindow::GetHeight(),C3DWindow::GetImageData(),&info,DIB_RGB_COLORS);
	if(!&dc)
		delete (CClientDC*)dc_pointer;
}
void CArbitraryEnergyView::PaintSphere(double radius,unsigned char red,unsigned char green,unsigned char blue,bool half)
{
	static const int loop_count=100;
	for(int longitude_loop=0;longitude_loop<loop_count;longitude_loop++)
	{
		double start_longitude,end_longitude;
		start_longitude=M_PI*2*longitude_loop/loop_count-M_PI;
		end_longitude=M_PI*2*(longitude_loop+1)/loop_count-M_PI;
		for(int latitude_loop=0;latitude_loop<loop_count;latitude_loop++)
		{
			if(half)
				if(latitude_loop>=loop_count/2)
					continue;
			double start_latitude,end_latitude;
			start_latitude=M_PI*latitude_loop/loop_count-M_PI/2;
			end_latitude=M_PI*(latitude_loop+1)/loop_count-M_PI/2;
			double x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3;
#define XYZ(x,y,z,latitude,longitude) \
			x=radius*cos(latitude)*cos(longitude);\
			y=radius*sin(latitude)*cos(longitude);\
			z=radius*sin(longitude)
			XYZ(x0,y0,z0,start_longitude,start_latitude);
			XYZ(x1,y1,z1,start_longitude,end_latitude);
			XYZ(x2,y2,z2,end_longitude,end_latitude);
			XYZ(x3,y3,z3,end_longitude,start_latitude);
#undef XYZ
			C3DWindow::Add(x0,y0,z0,red,green,blue,x1,y1,z1,red,green,blue,x2,y2,z2,red,green,blue);
			C3DWindow::Add(x2,y2,z2,red,green,blue,x3,y3,z3,red,green,blue,x0,y0,z0,red,green,blue);
		}
	}
}
void CArbitraryEnergyView::PaintCircle(double radius1,unsigned char red1,unsigned char green1,unsigned char blue1,double radius2,unsigned char red2,unsigned char green2,unsigned char blue2)
{
	static const int loop_count=100;
	for(int loop=0;loop<loop_count;loop++)
	{
		double start,end;
		start=M_PI*2*loop/loop_count;
		end=M_PI*2*(loop+1)/loop_count;
		double x0,y0,x1,y1,x2,y2,x3,y3;
		x0=radius1*cos(start);
		y0=radius1*sin(start);
		x1=radius2*cos(start);
		y1=radius2*sin(start);
		x2=radius2*cos(end);
		y2=radius2*sin(end);
		x3=radius1*cos(end);
		y3=radius1*sin(end);
		C3DWindow::Add(x0,y0,0,red1,green1,blue1,x1,y1,0,red2,green2,blue2,x2,y2,0,red2,green2,blue2);
		C3DWindow::Add(x2,y2,0,red2,green2,blue2,x3,y3,0,red1,green1,blue1,x0,y0,0,red1,green1,blue1);
	}
}
void CArbitraryEnergyView::PaintRoundFace(double radius,void * thiz,double (CGetXValue::*Go)(int index,void * user_data),int count,void * user_data)
{
	double min,max;
	min=1e200;
	max=-1e200;
	for(int index=0;index<count;index++)
	{
		double value;
		value=(*(CGetXValue*)thiz.*Go)(index,user_data);
		if(value<min)
			min=value;
		if(value>max)
			max=value;
	}
	for(int index=0;index<count;index++)
	{
		double current_radius;
		current_radius=radius*index/(count-1);
		double value;
		value=(*(CGetXValue*)thiz.*Go)(index,user_data);
		value=(-min+value)/(-min+max);
		unsigned char red,green,blue;
		ColorFromValue(red,green,blue,value);
		int loop_count;
		loop_count=400*index/count;
		for(int loop=0;loop<loop_count;loop++)
		{
			double start,end;
			start=M_PI*2*loop/loop_count;
			end=M_PI*2*(loop+1)/loop_count;
			double x0,y0,x1,y1;
			x0=current_radius*cos(start);
			y0=current_radius*sin(start);
			x1=current_radius*cos(end);
			y1=current_radius*sin(end);
			C3DWindow::Add(x0,y0,0,red,green,blue,x1,y1,0,red,green,blue);
		}
	}
	m_round_face_min=min;
	m_round_face_max=max;
}
void CArbitraryEnergyView::Paint()
{
	{
		double light[3];
		C3DWindow::GetLookDirection(light);
		C3DWindow::TurnOnLight(light);
	}
	//The ground
	{
		double radius;
		radius=g_kettle.GetOuterRadius()+g_electret.m_thickness;
		double z;
		z=-radius;
		radius*=1.3;
		static const int loop_count=8;
		for(int loop=0;loop<loop_count;loop++)
		{
			double position;
			position=-radius+radius*2*loop/(loop_count-1);
			C3DWindow::Add(position,-radius,z, 100,200,255,    position,radius,z,  100,200,255);
			C3DWindow::Add(-radius,position,z, 100,200,255,    radius,position,z,  100,200,255);
		}
	}
	if(!g_dialog_tool.m_check_display_half_of_the_reactor.GetCheck())
	{
		PaintSphere(g_kettle.GetOuterRadius()+g_electret.m_thickness,120,120,255,false);
	}
	else
	{
		if(g_dialog_tool.m_check_display_coordinate_axes.GetCheck())
		{
			C3DWindow::Add(0,0,0, 255,100,100,    g_kettle.GetInnerRadius()*0.65,0,0,  255,100,100);
			C3DWindow::Add(0,0,0, 0,  255,  0,    0,g_kettle.GetInnerRadius()*0.65,0,  0,  255,0  );
			C3DWindow::Add(0,0,0, 150,150,255,    0,0,g_kettle.GetInnerRadius()*0.65,  150,150,255);
		}
		PaintSphere(g_kettle.GetOuterRadius(),255,100,100,true);
		PaintSphere(g_kettle.GetOuterRadius()+g_electret.m_thickness,120,120,255,true);
		PaintCircle(g_kettle.GetOuterRadius(),255,100,100,g_kettle.GetOuterRadius()+g_electret.m_thickness,120,120,255);
		PaintSphere(g_kettle.GetInnerRadius(),200,200,200,true);
		PaintCircle(g_kettle.GetOuterRadius(),200,200,200,g_kettle.GetInnerRadius(),200,200,200);
		if(g_dialog_tool.m_radio_display_electric_field_whole.GetCheck())
		{
			union
			{
				double (CGetXValue::*Out)(int index,void * user_data);
				double (CSimulate::*In)(int index,CSimulate::EGetElectricField source);
			}funtion;
			funtion.In=&CSimulate::GetElectricField;
			PaintRoundFace(g_kettle.GetInnerRadius()*0.9,&g_simulate,funtion.Out,(int)(g_simulate.m_block_count*0.9),(void *)(CSimulate::NUCLEAR_IN_KETTLE|CSimulate::ELECTRON_ON_KETTLE_INWALL|CSimulate::NUCLEAR_ESCAPED_ON_KETTLE_INWALL));
			_tcsncpy(m_round_face_string,_T("N/C"),sizeof(m_round_face_string)/sizeof(m_round_face_string[0])-1);
		}
	}
}


void CArbitraryEnergyView::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
	g_dialog_tool.ShowWindow(SW_SHOW);
}





int CArbitraryEnergyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	g_simulate.Start();
	g_dialog_tool.Create(IDD_DIALOG_TOOL);
	g_dialog_tool.ShowWindow(SW_SHOW);
	SetTimer(4335223,100,NULL);
	return 0;
}


void CArbitraryEnergyView::OnDestroy()
{
	__super::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	g_simulate.Stop();
}


void CArbitraryEnergyView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_dialog_tool.m_edit_display_max=m_round_face_max;
	g_dialog_tool.m_edit_display_min=m_round_face_min;
	g_dialog_tool.m_edit_display_middle=(m_round_face_max+m_round_face_min)/2;
	g_dialog_tool.m_edit_display_unit.SetWindowText(m_round_face_string);
	if(!g_simulate.m_updating_statistic)
	{
		DoPaint();
		g_dialog_tool.Update();
	}
	__super::OnTimer(nIDEvent);
}
