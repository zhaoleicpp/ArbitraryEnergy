#include "stdafx.h"
#include "Fuel.h"

CFuel g_fuel;

CFuel::CFuel(void)
{
	m_fuel=FUEL_DEUTERIUM_TRITIUM;
	m_mass=1e-5;//10g
	//m_temperature=1e8;
	m_temperature=1e7;
}


CFuel::~CFuel(void)
{
}
int CFuel::GetNuclearMass(double mass[])
{
	//English: https://en.wikipedia.org/wiki/Relative_atomic_mass
	//Chinese: http://baike.baidu.com/link?url=j0i3y1rqgARRTIssPDjA3XKmmoDWmic-7phRLraDWJu7oJhI8Qtt4hx6MoQlD1KSgCwU6e5pWuVhL3no_4MREq
	static const double relative_atomic_mass=1.667e-27;
	switch(m_fuel)
	{
	case FUEL_DEUTERIUM_TRITIUM:
		if(mass)
		{
			mass[0]=2.014*relative_atomic_mass;//DEUTERIUM //http://baike.baidu.com/link?url=UrHgFCcV4nMJr4brWBg9RoV0N91I7FS-5wXxBslOYIHFMJDLox0vup-SDyBxT97aqguk4JaGaPK7RLDoPwIvqa
			mass[1]=3.016*relative_atomic_mass;//TRITIUM //http://baike.baidu.com/link?url=CNyiV2__rQDf1dFwX8PIqJ-2UyCCM3n4_Rtan_0Z1-48M5YvEDxV4isD06YJ0VKf8cMdnF97DTs-tJX_B-g5SK
		}
		return 2;
		break;
	default:
		ASSERT(0);
		break;
	}
}
double CFuel::GetNuclearMass()
{
	double mass[m_max_fuel_count];
	int count;
	count=GetNuclearMass(mass);
	double ret;
	ret=0;
	for(int index=0;index<count;index++)
		ret+=mass[index]/count;
	return ret;
}
int CFuel::GetNuclearElectricity(double electricity[])//C
{
	//Chinese: http://www.zybang.com/question/9beda380a5c936819897d4644deeefa6.html
	static const double electron_charge=1.602176462e-19;
	switch(m_fuel)
	{
	case FUEL_DEUTERIUM_TRITIUM:
		if(electricity)
		{
			electricity[0]=1*electron_charge;//DEUTERIUM
			electricity[1]=1*electron_charge;//TRITIUM
		}
		return 2;
		break;
	default:
		ASSERT(0);
		break;
	}
}
double CFuel::GetNuclearElectricity()
{
	double electricity[m_max_fuel_count];
	int count;
	count=GetNuclearElectricity(electricity);
	double ret;
	ret=0;
	for(int index=0;index<count;index++)
		ret+=electricity[index]/count;
	return ret;
}
double CFuel::GetNuclearCount()
{
	return m_mass/GetNuclearMass();
}
double CFuel::GetElectricity()
{
	return GetNuclearElectricity()*GetNuclearCount();
}