// EditFloat.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ArbitraryEnergy.h"
#include "EditFloat.h"


// CEditFloat

IMPLEMENT_DYNAMIC(CEditFloat, CEdit)

CEditFloat::CEditFloat()
{

}

CEditFloat::~CEditFloat()
{
}


BEGIN_MESSAGE_MAP(CEditFloat, CEdit)
END_MESSAGE_MAP()



// CEditFloat ��Ϣ�������



double CEditFloat::operator = (double x)
{
	CString string;
	string.Format(_T("%0.6g"),x);
	SetWindowText(string);
	return x;
}