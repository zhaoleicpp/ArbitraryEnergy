#pragma once
class CSphere
{
public:
	class CVectorFromXAxis
	{
	public:
		double Get(double x,void * user);
	};
private:
	static const int m_electric_field_in_sphere_x_axis_sample_count=1000*5;
	static const double m_electric_field_in_sphere_x_axis_sample[m_electric_field_in_sphere_x_axis_sample_count];
	struct SElectricFieldParameter
	{
		double radius;
		double total_electricity;
	};
	double GetElectricField(double x,SElectricFieldParameter * electric_field_parameter);
public:
	static void VectorFromXAxis(CVector &value,const CVector &position,class CVectorFromXAxis &thiz,double (CVectorFromXAxis::*Get)(double x,void * user),void *user=NULL);
	void GetElectricField(CVector &electric_field,double radius,double total_electricity,const CVector &position);
	CSphere(void);
	~CSphere(void);
};

extern CSphere g_sphere;