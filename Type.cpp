#include "stdafx.h"
#include <math.h>
#include "Type.h"

CVector::CVector()
{
}
CVector::CVector(double v[3])
{
	this->v[X]=v[X];
	this->v[Y]=v[Y];
	this->v[Z]=v[Z];
}
CVector::CVector(double a)
{
	this->v[X]=a;
	this->v[Y]=a;
	this->v[Z]=a;
}
CVector::CVector(int a)
{
	this->v[X]=a;
	this->v[Y]=a;
	this->v[Z]=a;
}
CVector::~CVector()
{
}
CVector::operator double *()
{
	return (double*)v;
}
double &CVector::operator[](int index)
{
	return v[index];
}
CVector& CVector::operator =(const CVector&source)
{
	v[X]=source.v[X];
	v[Y]=source.v[Y];
	v[Z]=source.v[Z];
	return *this;
}
CVector& CVector::operator =(double x)
{
	v[X]=x;
	v[Y]=x;
	v[Z]=x;
	return *this;
}
CVector CVector::operator +(const CVector&source) const
{
	CVector ret;
	ret=*this;
	ret+=source;
	return ret;
}
CVector &CVector::operator +=(const CVector&source)
{
	v[X]+=source.v[X];
	v[Y]+=source.v[Y];
	v[Z]+=source.v[Z];
	return *this;
}
CVector CVector::operator -(const CVector&source) const
{
	CVector ret;
	ret=*this;
	ret+=source;
	return ret;
}
CVector &CVector::operator -=(const CVector&source)
{
	v[X]-=source.v[X];
	v[Y]-=source.v[Y];
	v[Z]-=source.v[Z];
	return *this;
}
CVector CVector::operator *(const double&source) const
{
	CVector ret;
	ret=*this;
	ret*=source;
	return ret;	
}
CVector &CVector::operator *=(const double&source)
{
	v[X]*=source;
	v[Y]*=source;
	v[Z]*=source;
	return *this;
}

CVector CVector::operator /(const double&source) const
{
	CVector ret;
	ret=*this;
	ret/=source;
	return ret;	
}
CVector &CVector::operator /=(const double&source)
{
	v[X]/=source;
	v[Y]/=source;
	v[Z]/=source;
	return *this;
}

bool CVector::In(const CVector & center,double delta)
{
	if(v[X]<center.v[X]-delta)
		return false;
	if(v[X]>center.v[X]+delta)
		return false;
	if(v[Y]<center.v[Y]-delta)
		return false;
	if(v[Y]>center.v[Y]+delta)
		return false;
	if(v[Z]<center.v[Z]-delta)
		return false;
	if(v[Z]>center.v[Z]+delta)
		return false;
	return true;
}
double CVector::GetLength() const
{
	return sqrt(pow(v[X],2.0)+pow(v[Y],2.0)+pow(v[Z],2.0));
}