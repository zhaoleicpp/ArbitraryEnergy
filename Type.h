#pragma once

#define X 0
#define Y 1
#define Z 2
class CVector
{
public:
	double v[3];
	CVector();
	CVector(double v[3]);
	CVector(double a);
	CVector(int a);
	~CVector();
	operator double *();
	CVector& operator =(const CVector&source);
	CVector& operator =(double x);
	double & operator[](int index);
	CVector operator +(const CVector&source) const;
	CVector &operator +=(const CVector&source);
	CVector operator -(const CVector&source) const;
	CVector &operator -=(const CVector&source);
	CVector operator *(const double&source) const;
	CVector &operator *=(const double&source);
	CVector operator /(const double&source) const;
	CVector &operator /=(const double&source);
	bool In(const CVector & center,double delta);
	double GetLength() const;
};
