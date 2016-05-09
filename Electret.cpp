#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Type.h"
#include "Misc.h"
#include "Sphere.h"
#include "Kettle.h"
#include "Electret.h"

CElectret g_electret;
CElectret::CElectret(void)
{
	m_thickness=0.5;
	//http://wk.baidu.com/view/b21a73610b1c59eef8c7b43f.html?pn=2&vw=all&pu=
	m_charge_density=0.9;
}


CElectret::~CElectret(void)
{
}
void CElectret::GetElectricField(CVector &electric_field,const CVector &position)
{
	double inner_radius;
	inner_radius=g_kettle.GetOuterRadius();//Just Outer
	double total_electricity;
	total_electricity=4*M_PI*pow(inner_radius,2.0);
	total_electricity*=m_charge_density;
	CVector electric_field_from_inner;
	g_sphere.GetElectricField(electric_field_from_inner,inner_radius,total_electricity,position);
	double outer_radius;
	outer_radius=inner_radius+m_thickness;
	g_sphere.GetElectricField(electric_field,outer_radius,total_electricity,position);
	electric_field+=electric_field_from_inner;
}
