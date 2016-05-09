// DialogTool.cpp : 实现文件
//

#include "stdafx.h"
#include "ArbitraryEnergy.h"
#include "DialogTool.h"
#include "afxdialogex.h"
#include "Type.h"
#include "Simulate.h"
#include "Fuel.h"
#include "Misc.h"

// CDialogTool 对话框
CDialogTool g_dialog_tool;

IMPLEMENT_DYNAMIC(CDialogTool, CDialog)

CDialogTool::CDialogTool(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogTool::IDD, pParent)
{

}

CDialogTool::~CDialogTool()
{
}

void CDialogTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_CHECK_DISPLAY_COORDINATE_AXES, m_check_display_coordinate_axes);
	DDX_Control(pDX, IDC_CHECK_DISPLAY_HALF_OF_THE_REACTOR, m_check_display_half_of_the_reactor);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_ELECTRIC_FIELD_NONE, m_radio_display_electric_field_none);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_ELECTRIC_FIELD_WHOLE, m_radio_display_electric_field_whole);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_ELECTRIC_FIELD_ELECTRET, m_radio_display_electric_field_electret);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_ELECTRIC_FIELD_ELECTRET_BY_POSITIVE_ELECTRICITY_ONLY, m_radio_display_electric_field_electret_by_positive_electricity_only);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_ELECTRIC_FIELD_ELECTRET_BY_NEGATIVE_ELECTRICITY_ONLY, m_radio_display_electric_field_electret_by_negative_electricity_only);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_ELECTRIC_FIELD_ELECTRON_ON_THE_KETTLE_INWALL, m_radio_display_electric_field_electron_on_the_kettle_inwall);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_ELECTRIC_FIELD_NUCLEUS_ESCAPED_ON_THE_KETTLE_INWALL, m_radio_display_electric_field_nucleus_escaped_on_the_kettle_inwall);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_ELECTRIC_FIELD_NUCLEUS_IN_THE_KETTLE, m_radio_display_electric_field_nucleus_in_the_kettle);
	DDX_Control(pDX, IDC_STATIC_ELECTRET_CHARGE_DENSITY, m_static_electret_charge_density);
	DDX_Control(pDX, IDC_SLIDER_ELECTRET_CHARGE_DENSITY, m_slider_electret_charge_density);
	DDX_Control(pDX, IDC_EDIT_ELECTRET_CHARGE_DENSITY, m_edit_electret_charge_density);
	DDX_Control(pDX, IDC_STATIC_ELECTRET_THICKNESS, m_static_electret_thickness);
	DDX_Control(pDX, IDC_SLIDER_ELECTRET_THICKNESS, m_slider_electret_thickness);
	DDX_Control(pDX, IDC_EDIT_ELECTRET_THICKNESS, m_edit_electret_thickness);
	DDX_Control(pDX, IDC_STATIC_KETTLE_OUTER_DIAMETER, m_static_kettle_outer_diameter);
	DDX_Control(pDX, IDC_SLIDER_KETTLE_OUTER_DIAMETER, m_slider_kettle_outer_diameter);
	DDX_Control(pDX, IDC_EDIT_KETTLE_OUTER_DIAMETER, m_edit_kettle_outer_diameter);
	DDX_Control(pDX, IDC_STATIC_KETTLE_THICKNESS, m_static_kettle_thickness);
	DDX_Control(pDX, IDC_SLIDER_KETTLE_THICKNESS, m_slider_kettle_thickness);
	DDX_Control(pDX, IDC_EDIT_KETTLE_THICKNESS, m_edit_kettle_thickness);
	DDX_Control(pDX, IDC_STATIC_KETTLE_AVERAGE_RELATIVE_DIELECTRIC_CONSTANT, m_static_kettle_average_relative_dielectric_constant);
	DDX_Control(pDX, IDC_SLIDER_KETTLE_AVERAGE_RELATIVE_DIELECTRIC_CONSTANT, m_slider_kettle_average_relative_dielectric_constant);
	DDX_Control(pDX, IDC_EDIT_KETTLE_AVERAGE_RELATIVE_DIELECTRIC_CONSTANT, m_edit_kettle_average_relative_dielectric_constant);
	DDX_Control(pDX, IDC_RADIO_FUEL_DEUTERIUM_AND_TRITIUM, m_radio_fuel_deuterium_and_tritium);
	DDX_Control(pDX, IDC_STATIC_FUEL_TOTAL_MASS, m_static_fuel_total_mass);
	DDX_Control(pDX, IDC_SLIDER_FUEL_TOTAL_MASS, m_slider_fuel_total_mass);
	DDX_Control(pDX, IDC_EDIT_FUEL_TOTAL_MASS, m_edit_fuel_total_mass);
	DDX_Control(pDX, IDC_STATIC_FUEL_EQUIVALENT_OF_COAL, m_static_fuel_equivalent_of_coal);
	DDX_Control(pDX, IDC_EDIT_FUEL_EQUIVALENT_OF_COAL, m_edit_fuel_equivalent_of_coal);
	DDX_Control(pDX, IDC_STATIC_FUEL_TEMPERATURE, m_static_fuel_termperature);
	DDX_Control(pDX, IDC_SLIDER_FUEL_TEMPERATURE, m_slider_fuel_termperature);
	DDX_Control(pDX, IDC_EDIT_FUEL_TEMPERATURE, m_edit_fuel_termperature);
	DDX_Control(pDX, IDC_STATIC_SIMULATE_TIME, m_static_simulate_time);
	DDX_Control(pDX, IDC_EDIT_SIMULATE_TIME, m_edit_simulate_time);
	DDX_Control(pDX, IDC_STATIC_SIMULATE_ESCAPE, m_static_simulate_escaped);
	DDX_Control(pDX, IDC_EDIT_SIMULATE_ESCAPE, m_edit_simulate_escaped);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_FUEL_TEMPERATURE, m_radio_display_fuel_temperature);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_PARTICLE_DENSITY, m_radio_display_particle_density);
	DDX_Control(pDX, IDC_RADIO_DISPLAY_LAWSON, m_radio_display_lawson);
	DDX_Control(pDX, IDC_STATIC_SIMULATE_CENTER_TEMPERATURE, m_static_simulate_center_temperature);
	DDX_Control(pDX, IDC_EDIT_SIMULATE_TEMPERATURE, m_edit_simulate_center_temperature);
	DDX_Control(pDX, IDC_STATIC_SIMULATE_CENTER_LAWSON, m_static_simulate_center_lawson);
	DDX_Control(pDX, IDC_EDIT_SIMULATE_LAWSON, m_edit_simulate_center_lawson);
	DDX_Control(pDX, IDC_STATIC_SIMULATE_CENTER_LAWSON_CRITERION, m_static_simulate_center_lawson_criterion);
	DDX_Control(pDX, IDC_RADIO_SIMULATE_CENTER_LAWSON_CRITERION_PASS, m_radio_simulate_center_lawson_criterion_pass);
	DDX_Control(pDX, IDC_RADIO_SIMULATE_CENTER_LAWSON_CRITERION_FAIL, m_radio_simulate_center_lawson_criterion_fail);
	DDX_Control(pDX, IDC_STATIC_SIMULATE_LOG, m_static_simulate_log);
	DDX_Control(pDX, IDC_STATIC_SIMULATE_CENTER_PARTIDE_DENSITY, m_static_simulate_center_partide_density);
	DDX_Control(pDX, IDC_EDIT_SIMULATE_CENTER_PARTIDE_DENSITY, m_edit_simulate_center_partide_density);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_RAINBOW_VALUE, m_static_display_rainbow_value);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_MIN, m_edit_display_min);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_MIDDLE, m_edit_display_middle);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_MAX, m_edit_display_max);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_UINT, m_edit_display_unit);
	DDX_Control(pDX, IDC_BUTTON_SIMULATE_RESTART, m_button_simulate_restart);
	DDX_Control(pDX, IDC_BUTTON_SIMULATE_PAUSE, m_button_simulate_pause);
	DDX_Control(pDX, IDC_BUTTON_FILE_SAVE, m_button_file_save);
	DDX_Control(pDX, IDC_BUTTON_FILE_SAVE_AS, m_button_file_save_as);
	DDX_Control(pDX, IDC_BUTTON_FILE_OPEN, m_button_file_save_open);
	DDX_Control(pDX, IDC_BUTTON_FILE_HELP, m_button_file_help);
	DDX_Control(pDX, IDC_BUTTON_FILE_ABOUT, m_button_file_about);
	DDX_Control(pDX, IDC_EDIT_SIMULATE_OUTPUT, m_eidt_simulate_output);
}


BEGIN_MESSAGE_MAP(CDialogTool, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CDialogTool::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CDialogTool 消息处理程序


void CDialogTool::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	ShowWindow(SW_HIDE);
	return ;
	//CDialog::OnCancel();
}


void CDialogTool::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	return ;
	//CDialog::OnOK();
}


BOOL CDialogTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_check_display_half_of_the_reactor.SetCheck(TRUE);
	m_radio_display_lawson.SetCheck(TRUE);


	SetWindowPos(NULL,0,0,330,260,SWP_NOZORDER|SWP_NOMOVE);
	int page_count;
	page_count=0;
	m_tab.InsertItem(page_count,_T("Display"));
	m_page[page_count].count=0;
#define ADD(control_window) \
	if(m_page[page_count].count>=m_max_control_per_page) \
		ASSERT(0);\
	m_page[page_count].control[m_page[page_count].count].window=&control_window;\
	m_page[page_count].count++;
	ADD(m_check_display_coordinate_axes);
	ADD(m_check_display_half_of_the_reactor);
	ADD(m_radio_display_electric_field_none);
	ADD(m_radio_display_electric_field_whole);
	ADD(m_radio_display_electric_field_electret);
	ADD(m_radio_display_electric_field_electret_by_positive_electricity_only);
	ADD(m_radio_display_electric_field_electret_by_negative_electricity_only);
	ADD(m_radio_display_electric_field_electron_on_the_kettle_inwall);
	ADD(m_radio_display_electric_field_nucleus_escaped_on_the_kettle_inwall);
	ADD(m_radio_display_electric_field_nucleus_in_the_kettle);
	ADD(m_radio_display_fuel_temperature);
	ADD(m_radio_display_particle_density);
	ADD(m_radio_display_lawson);
	ADD(m_static_display_rainbow_value);
	ADD(m_edit_display_min);
	ADD(m_edit_display_middle);
	ADD(m_edit_display_max);
	ADD(m_edit_display_unit);
	page_count++;
	m_tab.InsertItem(page_count,_T("Electret"));
	m_page[page_count].count=0;
	ADD(m_static_electret_charge_density);
	ADD(m_slider_electret_charge_density);
	ADD(m_edit_electret_charge_density);
	ADD(m_static_electret_thickness);
	ADD(m_slider_electret_thickness);
	ADD(m_edit_electret_thickness);
	page_count++;
	m_tab.InsertItem(page_count,_T("Kettle"));
	m_page[page_count].count=0;
	ADD(m_static_kettle_outer_diameter);
	ADD(m_slider_kettle_outer_diameter);
	ADD(m_edit_kettle_outer_diameter);
	ADD(m_static_kettle_thickness);
	ADD(m_slider_kettle_thickness);
	ADD(m_edit_kettle_thickness);
	ADD(m_static_kettle_average_relative_dielectric_constant);
	ADD(m_slider_kettle_average_relative_dielectric_constant);
	ADD(m_edit_kettle_average_relative_dielectric_constant);
	page_count++;
	m_tab.InsertItem(1,_T("Fuel"));
	m_page[page_count].count=0;
	ADD(m_radio_fuel_deuterium_and_tritium);
	ADD(m_static_fuel_total_mass);
	ADD(m_slider_fuel_total_mass);
	ADD(m_edit_fuel_total_mass);
	ADD(m_static_fuel_equivalent_of_coal);
	ADD(m_edit_fuel_equivalent_of_coal);
	ADD(m_static_fuel_termperature);
	ADD(m_slider_fuel_termperature);
	ADD(m_edit_fuel_termperature);
	page_count++;
	m_tab.InsertItem(page_count,_T("Simulate"));
	m_page[page_count].count=0;
	ADD(m_static_simulate_time);
	ADD(m_edit_simulate_time);
	ADD(m_static_simulate_escaped);
	ADD(m_edit_simulate_escaped);
	ADD(m_static_simulate_center_partide_density);
	ADD(m_edit_simulate_center_partide_density);
	ADD(m_static_simulate_center_temperature);
	ADD(m_edit_simulate_center_temperature);
	ADD(m_static_simulate_center_lawson);
	ADD(m_edit_simulate_center_lawson);
	ADD(m_static_simulate_center_lawson_criterion);
	ADD(m_radio_simulate_center_lawson_criterion_pass);
	ADD(m_radio_simulate_center_lawson_criterion_fail);
	ADD(m_static_simulate_log);
	ADD(m_button_simulate_restart);
	ADD(m_button_simulate_pause);
	ADD(m_eidt_simulate_output);

	page_count++;
	m_tab.InsertItem(page_count,_T("File"));
	m_page[page_count].count=0;
	ADD(m_button_file_save);
	ADD(m_button_file_save_as);
	ADD(m_button_file_save_open);
	ADD(m_button_file_help);
	ADD(m_button_file_about);
#undef ADD
	page_count++;
	for(int page_index=0;page_index<m_page_count;page_index++)
	{
		SPage &page=m_page[page_index];
		page.top_left_x=0x7fffffff;
		page.top_left_y=0x7fffffff;
		for(int window_index=0;window_index<page.count;window_index++)
		{
			SControl &control=page.control[window_index];
			CRect rect;
			control.window->GetWindowRect(rect);
			ScreenToClient(rect);
			control.original_x=rect.left;
			control.original_y=rect.top;
			control.width=rect.Width();
			control.height=rect.Height();
			if(control.original_x<page.top_left_x)
				page.top_left_x=control.original_x;
			if(control.original_y<page.top_left_y)
				page.top_left_y=control.original_y;
		}
	}
	OnTabSelect(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDialogTool::OnTabSelect(int index)
{
	int x_start,y_start;
	{
		CRect rect;
		m_tab.GetWindowRect(rect);
		ScreenToClient(rect);
		x_start=rect.left;
		y_start=rect.top;
	}
	{
		SPage &page=m_page[index];
		int top_left_x,top_left_y;
		top_left_x=page.top_left_x;
		top_left_y=page.top_left_y;
		for(int window_index=0;window_index<page.count;window_index++)
		{
			SControl &control=page.control[window_index];
			CRect rect;
			rect.left=3+x_start+control.original_x-top_left_x;
			rect.top=30+y_start+control.original_y-top_left_y;
			rect.right=rect.left+control.width;
			rect.bottom=rect.top+control.height;
			control.window->ShowWindow(SW_SHOW);
			control.window->MoveWindow(&rect,TRUE);
		}
	}
	for(int page_index=0;page_index<m_page_count;page_index++)
	{
		if(page_index==index)
			continue;
		SPage &page=m_page[page_index];
		for(int window_index=0;window_index<page.count;window_index++)
		{
			SControl &control=page.control[window_index];
			CRect rect;
			rect.left=3+x_start+control.original_x;
			rect.top=30+y_start+control.original_y;
			rect.right=rect.left+control.width;
			rect.bottom=rect.top+control.height;
			control.window->ShowWindow(SW_HIDE);
			control.window->MoveWindow(&rect,TRUE);
		}
	}
}

void CDialogTool::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	OnTabSelect(m_tab.GetCurSel());
}

void CDialogTool::Update()
{
	m_edit_simulate_time=g_simulate.m_loop*g_simulate.m_time_step;
	m_edit_simulate_escaped=g_simulate.m_escaped*g_simulate.m_representative*100/g_fuel.GetNuclearCount();
	m_edit_simulate_center_partide_density=g_simulate.m_block[0].density;
	m_edit_simulate_center_temperature=TemperatureKeVFromK(g_simulate.m_block[0].temperature);
	m_edit_simulate_center_lawson=g_simulate.m_block[0].lawson;
	if(g_simulate.m_block[0].lawson>2e21)
	{
		m_radio_simulate_center_lawson_criterion_pass.SetCheck(TRUE);//All for this
		m_radio_simulate_center_lawson_criterion_fail.SetCheck(FALSE);
	}
	else
	{
		m_radio_simulate_center_lawson_criterion_pass.SetCheck(FALSE);
		m_radio_simulate_center_lawson_criterion_fail.SetCheck(TRUE);
	}
	m_static_simulate_log.Paint();
	m_eidt_simulate_output.SetWindowText(g_simulate.m_output);
}