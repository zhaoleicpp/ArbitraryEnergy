#include "stdafx.h"
#include "Kettle.h"

CKettle g_kettle;

CKettle::CKettle(void)
{
	m_inner_radius=1;
	m_thickness=0.2;
}


CKettle::~CKettle(void)
{
}

double CKettle::GetInnerRadius()
{
	return m_inner_radius;
}
double CKettle::GetOuterRadius()
{
	return m_inner_radius+m_thickness;
}
