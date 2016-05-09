// ButtonAutoCall3DPaint.cpp : 实现文件
//

#include "stdafx.h"
#include "ArbitraryEnergy.h"
#include "ButtonAutoCall3DPaint.h"
#include "MainFrm.h"
#include "ArbitraryEnergyDoc.h"
#include "ArbitraryEnergyView.h"


// CButtonAutoCall3DPaint

IMPLEMENT_DYNAMIC(CButtonAutoCall3DPaint, CButton)

CButtonAutoCall3DPaint::CButtonAutoCall3DPaint()
{

}

CButtonAutoCall3DPaint::~CButtonAutoCall3DPaint()
{
}


BEGIN_MESSAGE_MAP(CButtonAutoCall3DPaint, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &CButtonAutoCall3DPaint::OnBnClicked)
END_MESSAGE_MAP()



// CButtonAutoCall3DPaint 消息处理程序




void CButtonAutoCall3DPaint::OnBnClicked()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * main_window;
	main_window=(CMainFrame *)AfxGetMainWnd();
	if(!main_window||!::IsWindow(main_window->GetSafeHwnd()))
		return ;
	CArbitraryEnergyView * arbitrary_energy_view;
	arbitrary_energy_view=(CArbitraryEnergyView * )main_window->GetActiveView();
	if(!arbitrary_energy_view||!::IsWindow(arbitrary_energy_view->GetSafeHwnd()))
		return ;
	arbitrary_energy_view->DoPaint();
}
