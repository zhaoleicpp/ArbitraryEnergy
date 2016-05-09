#pragma once
class CSimulate
{
public:
	template <typename CType> class TInitializer
	{
	public:
		class SSegment : public CType
		{
		public:
			double nuclear_count;
			double total_nuclear_count;
		};
		SSegment *m_segment;
		int m_segment_count;
		int m_max_segment_count;
		static const int m_malloc_step=1024*1024;
	public:
		TInitializer()
		{
			m_segment_count=0;
			m_max_segment_count=m_malloc_step;
			m_segment=(SSegment*)malloc(sizeof(SSegment)*m_max_segment_count);
		}
		~TInitializer()
		{
			m_segment_count=0;
			m_max_segment_count=0;
			free(m_segment);
		}
		void Add(const CType &value,double nuclear_count)
		{
			m_segment_count++;
			if(m_segment_count>m_max_segment_count)
			{
				m_max_segment_count+=m_malloc_step;
				m_segment=(SSegment*)realloc(m_segment,sizeof(SSegment)*m_max_segment_count);
			}
			SSegment &new_segment=m_segment[m_segment_count-1];
			double last_total_nuclear_count;
			if(m_segment_count<2)
				last_total_nuclear_count=0;
			else
				last_total_nuclear_count=m_segment[m_segment_count-2].total_nuclear_count;
			*(CType*)&new_segment=value;
			new_segment.nuclear_count=nuclear_count;
			new_segment.total_nuclear_count=last_total_nuclear_count+nuclear_count;
		}
		void Get(CType &value,int nuclear_index,int total_nuclear_count)
		{
			if(m_segment_count<=0)
				ASSERT(0);
			double total_nuclear_count_input;
			total_nuclear_count_input=m_segment[m_segment_count-1].total_nuclear_count;
			double target;
			target=nuclear_index*total_nuclear_count_input/total_nuclear_count;
			for(int loop=0;loop<m_segment_count;loop++)
			{
				SSegment &current_segment=m_segment[loop];
				double last_total_nuclear_count;
				if(loop==0)
					last_total_nuclear_count=0;
				else
					last_total_nuclear_count=m_segment[loop-1].total_nuclear_count;
				double current_nuclear_count;
				current_nuclear_count=current_segment.total_nuclear_count;
				if(last_total_nuclear_count<=target&&target<=current_nuclear_count)
				{
					value=(CType)current_segment;
					return ;
				}
			}
			ASSERT(0);
		}
	};
	struct SNuclear
	{
		bool on;
		double mass;//kg
		double electricity;//C
		CVector position;//m
		CVector speed;//m/s
	};
#ifdef _DEBUG
	static const int m_nuclear_count=50*50*50;
#else
	static const int m_nuclear_count=200*200*200;
#endif
	SNuclear m_nuclear[m_nuclear_count];

	double m_representative;
	int m_escaped;
#ifdef _DEBUG
	static const int m_block_count=100;
#else
	static const int m_block_count=1000;
#endif
	struct SBlock
	{
		double electric_field_by_nuclear;// N/C
		double density;// /m^3
		double temperature;//K
		double lawson;//m^-3 s KeV
	}m_block[m_block_count];
	static const double m_time_step;
	__int64 m_loop;
	double GetElectricFieldByNuclear(double x,void * nouse);
	double GetBlockX(int block_index);
	int GetBlockIndex(double x);
	void UpdateElectricFieldByNuclear();
	void GetElectricFieldByNuclear(CVector &electric_field,const CVector &position);
	void GetElectricFieldByElectronAndNuclearEscapedOnKettleInwall(CVector &electric_field,const CVector &position);
	bool m_on,m_pause,m_restart;
	void Go();
	bool m_updating_statistic;
	void UpdateStatistic();
	static const int m_max_log_count=1024;
	struct SBlock m_log[m_max_log_count];
	int m_log_count;
	TCHAR m_output[1024];
	void Output(LPCTSTR format,...);
	enum EGetElectricField
	{
		NUCLEAR_IN_KETTLE=1<<0,
		ELECTRON_ON_KETTLE_INWALL=1<<1,
		NUCLEAR_ESCAPED_ON_KETTLE_INWALL=1<<2
	};
	double GetElectricField(int block_index,EGetElectricField source);
	static UINT Thread(void *thiz);
	void Start();
	void Stop();
	CSimulate(void);
	~CSimulate(void);
};

extern CSimulate g_simulate;