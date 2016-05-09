// StaticRainbowValue.cpp : ʵ���ļ�
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



// CStaticRainbowValue ��Ϣ�������




void CStaticRainbowValue::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CStatic::OnPaint()
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
