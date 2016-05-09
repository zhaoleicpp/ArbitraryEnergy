#pragma once
class CFuel
{
public:
	enum EFuel {FUEL_DEUTERIUM_TRITIUM} m_fuel;
	static const int m_max_fuel_count=10;
	double m_temperature;//K
	double m_mass;//kg
	int GetNuclearMass(double mass[]);//kg
	double GetNuclearMass();//kg
	int GetNuclearElectricity(double electricity[]);//C
	double GetNuclearElectricity();//C
	double GetNuclearCount();
	double GetElectricity();//C
	CFuel(void);
	~CFuel(void);
};

extern CFuel g_fuel;