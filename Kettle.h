#pragma once
class CKettle
{
private:
	double m_inner_radius;//m
	double m_thickness;//m
public:
	double GetInnerRadius();
	double GetOuterRadius();
	CKettle(void);
	~CKettle(void);
};

extern CKettle g_kettle;