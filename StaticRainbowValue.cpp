// StaticRainbowValue.cpp : 实现文件
//

#include "stdafx.h"
#include "ArbitraryEnergy.h"
#include "StaticRainbowValue.h"
#include "Misc.h"

// CStaticRainbowValue

IMPLEMENT_DYNAMIC(CStaticRainbowValue, CStatic)

CStaticRainbowValue::CStaticRainbowValue()
{

}

CStaticRainbowValue::~CStaticRainbowValue()
{
}


BEGIN_MESSAGE_MAP(CStaticRainbowValue, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CStaticRainbowValue 消息处理程序




void CStaticRainbowValue::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	int width,height;
	width=rect.Width();
	height=rect.Height();
	for(int x=0;x<width;x++)
	{
		unsigned char red,green,blue;
		ColorFromValue(red,green,blue,x/(double)(width-1));
		for(int y=0;y<height;y++)
			dc.SetPixel(x,y,RGB(red,green,blue));
	}
}
