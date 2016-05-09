#pragma once
class CElectret
{
public:
	double m_charge_density;// C/m^2;
	double m_thickness;//m
	void GetElectricField(CVector &electric_field,const CVector &position);
	CElectret(void);
	~CElectret(void);
};

extern CElectret g_electret;