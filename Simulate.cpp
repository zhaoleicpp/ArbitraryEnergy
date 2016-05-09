#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Type.h"
#include "Simulate.h"
#include "Fuel.h"
#include "Misc.h"
#include "Kettle.h"
#include "Sphere.h"
#include "Electret.h"

CSimulate g_simulate;

const double CSimulate::m_time_step=1e-11;// s

CSimulate::CSimulate(void)
{
	m_output[0]=_T('0');
}


CSimulate::~CSimulate(void)
{
}
void CSimulate::GetElectricFieldByElectronAndNuclearEscapedOnKettleInwall(CVector &electric_field,const CVector &position)
{
	double electric;
	electric=-g_fuel.GetElectricity();
	electric+=m_escaped*m_representative*g_fuel.GetNuclearElectricity();
	double radius;
	radius=g_kettle.GetInnerRadius();
	g_sphere.GetElectricField(electric_field,radius,electric,position);
}
double CSimulate::GetBlockX(int block_index)
{
	double radius;
	radius=g_kettle.GetInnerRadius();
	double ret;
	ret=block_index;
	ret*=radius;
	ret/=(m_block_count-1);
	return ret;
}
int CSimulate::GetBlockIndex(double x)
{
	double radius;
	radius=g_kettle.GetInnerRadius();

	double double_index;
	double_index=x;
	double_index*=(m_block_count-1);
	double_index/=radius;
	int index;
	index=(int)(double_index+0.5);
	if(index<0||index>=m_block_count)
		ASSERT(0);
	return index;
}
void CSimulate::UpdateElectricFieldByNuclear()
{
	for(int block_index=0;block_index<m_block_count;block_index++)
	{
		SBlock & block=m_block[block_index];

		CVector position_to_solve;
		double &x_of_position_to_solve=position_to_solve[X];
		x_of_position_to_solve=GetBlockX(block_index);
		position_to_solve[Y]=0;
		position_to_solve[Z]=0;

		CVector electric_field;
		electric_field=0;
		for(int index=0;index<m_nuclear_count;index++)
		{
			SNuclear &nuclear=m_nuclear[index];
			if(nuclear.on)
				continue;
			CVector &electric_field_source_positoin=nuclear.position;
			CVector distance; 
			distance=position_to_solve-electric_field_source_positoin;
			double distance_length;
			distance_length=distance.GetLength();
			if(distance_length<1e-10)// :-)    :-(   ?->  bomb!!!!!,  NO, Just to avoid deviding by zero
				continue;
			double electric_field_length;
			electric_field_length=nuclear.electricity;
			electric_field_length*=8.988e9;
			electric_field_length/=pow(distance_length,2.0);
			electric_field+=(distance/distance_length)*electric_field_length;
		}
		double electric_field_x;
		electric_field_x=electric_field[X];
		double abs_electric_field_x;
		abs_electric_field_x=abs(electric_field_x);
		if(abs_electric_field_x>1e-3)
		{
			ASSERT_RANGE(0,abs_electric_field_x/10000,electric_field[Y]);
			ASSERT_RANGE(0,abs_electric_field_x/10000,electric_field[Z]);
		}
		block.electric_field_by_nuclear=electric_field_x*m_representative;
	}
}
double CSimulate::GetElectricFieldByNuclear(double x,void * nouse)
{
	int index;
	index=GetBlockIndex(x);
	return m_block[index].electric_field_by_nuclear;
}
void CSimulate::GetElectricFieldByNuclear(CVector &electric_field,const CVector &position)
{
	union
	{
		double (CSphere::CVectorFromXAxis::*Out)(double x,void * user);
		double (CSimulate::*In)(double x,void * nouse);
	}funtion;
	funtion.In=&CSimulate::GetElectricFieldByNuclear;
	CSphere::VectorFromXAxis(electric_field,position,*(CSphere::CVectorFromXAxis*)this,funtion.Out,NULL);
}
void CSimulate::Output(LPCTSTR format,...)
{
	va_list args;
	va_start(args, format);
	_vsntprintf(m_output,sizeof(m_output)/sizeof(m_output[0])-1,format,args);
	va_end(args);
}
void CSimulate::Go()
{
#define RETURN() {m_on=false; return ;}
#define BREATH() do{if(!m_on)return;if(m_restart) goto START; Sleep(1);}while(m_pause);

START:
	Output(_T("Initializing...\r\n"));
	m_on=true;
	m_pause=false;
	m_restart=false;
	m_log_count=0;
	m_updating_statistic=false;
	m_loop=0;
	m_representative=g_fuel.GetNuclearCount()/m_nuclear_count;
	{
		Output(_T("Initializing mass electricity and \'on\'.\r\n"));
		double mass[CFuel::m_max_fuel_count];
		double electricity[CFuel::m_max_fuel_count];
		int count;
		count=g_fuel.GetNuclearMass(mass);
		g_fuel.GetNuclearElectricity(electricity);
		srand(0);
		double average_mass;
		average_mass=0;
		for(int loop=0;loop<m_nuclear_count;loop++)
		{
			SNuclear &nuclear=m_nuclear[loop];
			int index;
			index=(((rand()&0xff)<<0)|((rand()&0xff)<<8));
			index%=count;
			nuclear.mass=mass[index];
			nuclear.electricity=electricity[index];
			average_mass+=nuclear.mass;
			nuclear.on=true;
		}
		average_mass/=m_nuclear_count;
		ASSERT_RANGE(g_fuel.GetNuclearMass(),g_fuel.GetNuclearMass()/1e3,average_mass);
		BREATH();
	}

	{
		Output(_T("Initializing position.\r\n"));
		TInitializer<CVector> position_initializer;
		double radius;//m
		radius=g_kettle.GetInnerRadius();
		srand(0);
		CVector average_position;
		average_position=0;
		for(int loop=0;loop<m_nuclear_count;loop++)
		{
			CVector position;
			while(true)
			{
				position[X]=radius*((((rand()&0xff)<<0)|((rand()&0xff)<<8))-0xffff/2)/(0xffff/2);
				position[Y]=radius*((((rand()&0xff)<<0)|((rand()&0xff)<<8))-0xffff/2)/(0xffff/2);
				position[Z]=radius*((((rand()&0xff)<<0)|((rand()&0xff)<<8))-0xffff/2)/(0xffff/2);
				if(position.GetLength()<radius)
					break;
			}
			SNuclear &nuclear=m_nuclear[loop];
			average_position+=position;
			nuclear.position=position;
		}
		average_position/=m_nuclear_count;
		ASSERT(average_position.In(0,radius/200));
		BREATH();
	}

	//speed
	{
		Output(_T("Initializing speed.\r\n"));
		//English: https://en.wikipedia.org/wiki/Maxwell%E2%80%93Boltzmann_distribution
		//Chinese http://bos.wenku.bdimg.com/v1/wenku8//68f60b32bd21081022ad99195ee1e4f5?responseContentDisposition=attachment%3B%20filename%3D%22%B4%F3%D1%A7%CE%EF%C0%ED04%C2%F3%BF%CB%CB%B9%CE%A4%CB%D9%C2%CA%B7%D6%B2%BC%C2%C9.ppt%22&responseContentType=application%2Foctet-stream&responseCacheControl=no-cache&authorization=bce-auth-v1%2Ffa1126e91489401fa7cc85045ce7179e%2F2016-04-27T08%3A26%3A56Z%2F3600%2Fhost%2Ffa09e3b5d799b38f961e33589854aa700e94a9e3e1c2e73f309110b13268b0be&token=a78c99f8d71c7945bd51e1c5a30da84ee6cc6ecf53620a9c65410b873a2fb1f2&expire=2016-04-27T09:26:56Z
		TInitializer<CVector> direction_initializer;
		{
			double total_area;
			total_area=0;
			static const int loop_count=100;
			for(int longitude_loop=0;longitude_loop<loop_count;longitude_loop++)
			{
				double start_longitude,end_longitude,longitude;
				start_longitude=M_PI*2*longitude_loop/loop_count-M_PI;
				end_longitude=M_PI*2*(longitude_loop+1)/loop_count-M_PI;
				longitude=(start_longitude+end_longitude)/2;
				for(int latitude_loop=0;latitude_loop<loop_count;latitude_loop++)
				{
					double start_latitude,end_latitude,latitude;
					start_latitude=M_PI*latitude_loop/loop_count-M_PI/2;
					end_latitude=M_PI*(latitude_loop+1)/loop_count-M_PI/2;
					latitude=(start_latitude+end_latitude)/2;
					double height;
					height=-start_latitude+end_latitude;
					double arc_length;
					arc_length=-start_longitude+end_longitude;
					arc_length*=cos(latitude);
					double area;
					area=height*arc_length;
					total_area+=area;
					CVector direction;
					direction[X]=cos(longitude)*cos(latitude);
					direction[Y]=sin(longitude)*cos(latitude);
					direction[Z]=sin(latitude);
					direction_initializer.Add(direction,area);
				}
			}
			ASSERT_RANGE(M_PI*4,1e-3,total_area);
		}

		class CSpeed
		{
		public:
			CSpeed()
			{
			}
			CSpeed(double speed)
			{
				this->speed=speed;
			}
			~CSpeed()
			{
			}
			double speed;
			operator double()
			{
				return speed;
			}
		};
		TInitializer<CSpeed> speed_initializer;
		double theoretic_average_speed;//m/s
		double speed_step;//m/s
		{
			double T;//K
			T=g_fuel.m_temperature;
			static const double boltzmann_constant=1.38064852e-23;//k J/K
			double kT;
			kT=boltzmann_constant*T;
			double m;//kg
			m=g_fuel.GetNuclearMass();
			double constant;
			constant=4*M_PI*pow(m/(2*M_PI*kT),3.0/2.0);
			double _m_2kT;
			_m_2kT=-m/(2*kT);
			theoretic_average_speed=sqrt(8*kT/(M_PI*m));
			speed_step=theoretic_average_speed/10000;
			for(double speed=0;true;speed+=speed_step)
			{
				double v;
				v=speed+speed_step/2;
				double v2;
				v2=pow(v,2);
				double probability;
				probability=constant*v2*pow(M_E,_m_2kT*v2);
				if(speed>theoretic_average_speed)
					if(probability<1e-9)
						break;
				speed_initializer.Add(v,probability);
			}
		}
		srand(0);
		double average_speed;
		average_speed=0;
		CVector average_direction;
		average_direction=0;
		for(int loop=0;loop<m_nuclear_count;loop++)
		{
			CSpeed speed;
			speed_initializer.Get(speed,(((rand()&0xff)<<0)|((rand()&0xff)<<8)),0xffff);
			average_speed+=speed;
			CVector direction;
			direction_initializer.Get(direction,(((rand()&0xff)<<0)|((rand()&0xff)<<8)),0xffff);
			SNuclear &nuclear=m_nuclear[loop];
			average_direction+=direction;
			nuclear.speed=direction*speed;
			if((loop%50)==49)
			{
				Output(_T("Initializing speed %d/%d.\r\n"),loop,m_nuclear_count);
				BREATH();
			}
		}
		average_speed/=m_nuclear_count;
		ASSERT_RANGE(theoretic_average_speed,theoretic_average_speed/300,average_speed);
		average_direction/=theoretic_average_speed;
		ASSERT(average_direction.In(0,speed_step));
	}
	m_escaped=0;
	double radius_limit;//m
	radius_limit=g_kettle.GetInnerRadius();
	Output(_T("Updating the first statistic.\r\n"));
	UpdateStatistic();
	Output(_T("Prepare is ready, how hard the work is!\r\n"));
	for(m_loop=0;true;m_loop++)
	{
		UpdateElectricFieldByNuclear();
		for each (SNuclear & nuclear in m_nuclear)
		{
			if(!nuclear.on)
				continue;
			CVector &position=nuclear.position;
			CVector electric_field,child_electric_field;
			electric_field=0;
			GetElectricFieldByNuclear(child_electric_field,position);
			electric_field+=child_electric_field;
			GetElectricFieldByElectronAndNuclearEscapedOnKettleInwall(child_electric_field,position);
			electric_field+=child_electric_field;
			g_electret.GetElectricField(child_electric_field,position);
			electric_field+=child_electric_field;
			nuclear.position+=nuclear.speed*m_time_step;
			double radius;
			radius=nuclear.position.GetLength();
			if(radius>=radius_limit)
			{
				//根据热力学第三定律，各种原子核混在一起，不可能自动分开。这里只计数，不计种类
				//According to the third law of thermodynamics, all kinds of atomic nuclear are mixed together and can not be separated automatically. Here only count, regardless of species
				m_escaped++;
				nuclear.on=false;
				continue;
			}
			CVector force;
			force=electric_field*nuclear.electricity;
			CVector accelerate;
			accelerate=force/nuclear.mass;
			nuclear.speed+=accelerate*m_time_step;
		}
		Output(_T("Hard working %0.9fs\r\n"),m_loop*m_time_step);
		UpdateStatistic();
		BREATH();
	}

	RETURN();
#undef BREATH
#undef RETURN
}
void CSimulate::UpdateStatistic()
{
	Output(_T("Updating statistic.\r\n"));
	m_updating_statistic=true;
	double radius;
	radius=g_kettle.GetInnerRadius();

	double statistic_range;
	{
		double volume;
		volume=4*M_PI*pow(radius,3.0)/3;
		//pow(statistic_range,3)*m_nuclear_count/volume==10000
		statistic_range=pow(10000*volume/m_nuclear_count,1.0/3.0);
	}
	double density_array[m_block_count];
	for each (double & density in density_array)
		density=0;
	double temperature_array[m_block_count];
	for each (double & temperature in temperature_array)
		temperature=0;
	for each (SNuclear & nuclear in m_nuclear)
	{
		if(!nuclear.on)
			continue;
		double nuclear_x;
		nuclear_x=nuclear.position[X];
		if(nuclear_x<-statistic_range)
			continue;
		if(nuclear.position[Y]<-statistic_range)
			continue;
		if(nuclear.position[Y]>statistic_range)
			continue;
		if(nuclear.position[Z]<-statistic_range)
			continue;
		if(nuclear.position[Z]>statistic_range)
			continue;
		int start_index,end_index;
		double x;
		x=nuclear_x-statistic_range-(radius/2)/(m_block_count-1);
		if(x<0)
		{
			start_index=0;
		}
		else
		{
			start_index=GetBlockIndex(x)-1;
			if(start_index<0)
				start_index=0;
		}
		x=nuclear_x+statistic_range+(radius/2)/(m_block_count-1);
		if(x>=radius)
		{
			end_index=m_block_count-1;
		}
		else
		{
			end_index=GetBlockIndex(x)+1;
			if(end_index>=m_block_count)
				end_index=m_block_count-1;
		}
		for(int index=start_index;index<=end_index;index++)
		{
			double block_x;
			block_x=GetBlockX(index);
			double min_x;
			min_x=block_x-statistic_range;
			double max_x;
			max_x=block_x+statistic_range;
			if(min_x<=nuclear_x&&nuclear_x<=max_x)
			{
				density_array[index]++;
				temperature_array[index]+=(1.0/2.0)*nuclear.mass*pow(nuclear.speed.GetLength(),2.0);
			}
		}
	}
	double density_rate;
	density_rate=m_representative/pow((statistic_range*2),3.0);
	for(int index=0;index<m_block_count;index++)
	{
		double density;
		density=density_array[index];
		density*=density_rate;
		SBlock &block=m_block[index];
		block.density=density;
		if(density)
		{
			double temperature;
			temperature=temperature_array[index];
			//http://baike.baidu.com/link?url=KMuDmpJJggD1Msn1e6e8AOWq2EZ-pTvCfd4NlcwrKboPvxoOXSJBEahZzXl2RtnKwOrI6QAuXjXGh-XbV52C0a
			//https://en.wikipedia.org/wiki/Boltzmann_constant
			temperature*=2;
			temperature/=3;
			static const double boltzmann_constant=1.38064852e-23;//k J/K
			temperature/=boltzmann_constant;
			block.temperature=temperature;
		}
		else
			block.temperature=0;
		double temperature_eV;
		temperature_eV=TemperatureKeVFromK(block.temperature);
		block.lawson=m_time_step*m_loop*block.density*temperature_eV;
	}

	if(m_log_count>=m_max_log_count)
	{
		m_log_count/=2;
		for(int index=0;index<m_log_count;index++)
			m_log[index]=m_log[index*2+1];
	}
	m_log[m_log_count]=m_block[0];
	m_log_count++;
	m_updating_statistic=false;
	Output(_T("Statistic updated.\r\n"));
}

double CSimulate::GetElectricField(int block_index,EGetElectricField source)
{
	double radius;
	radius=g_kettle.GetInnerRadius();
	double x;
	x=GetBlockX(block_index);
	CVector position;
	position[X]=x;
	position[Y]=0;
	position[Z]=0;
	CVector electric_field,child_electric_field;
	electric_field=0;
	if(source&NUCLEAR_IN_KETTLE)
	{
		GetElectricFieldByNuclear(child_electric_field,position);
		electric_field+=child_electric_field;
	}
	if(source&ELECTRON_ON_KETTLE_INWALL)
	{
		double electric;
		electric=-g_fuel.GetElectricity();
		g_sphere.GetElectricField(child_electric_field,radius,electric,position);
		electric_field+=child_electric_field;
	}
	if(source&NUCLEAR_ESCAPED_ON_KETTLE_INWALL)
	{
		double electric;
		electric=m_escaped*m_representative*g_fuel.GetNuclearElectricity();
		g_sphere.GetElectricField(child_electric_field,radius,electric,position);
		electric_field+=child_electric_field;
	}
	if(abs(electric_field[X])>0.001)
	{
		ASSERT(abs(electric_field[X])>abs(electric_field[Y])*10);
		ASSERT(abs(electric_field[X])>abs(electric_field[Z])*10);
	}
	return electric_field[X];
}
UINT CSimulate::Thread(void *thiz)
{
	((CSimulate*)thiz)->Go();
	return 0;
}
void CSimulate::Start()
{
	m_on=false;
	AfxBeginThread(Thread,this);
	Sleep(100);
}
void CSimulate::Stop()
{
	m_on=false;
	Sleep(500);
}
