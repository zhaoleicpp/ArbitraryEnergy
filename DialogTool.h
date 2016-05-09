#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ButtonAutoCall3DPaint.h"
#include "EditFloat.h"
#include "StaticLog.h"
#include "StaticRainbowValue.h"
// CDialogTool 对话框

class CDialogTool : public CDialog
{
	DECLARE_DYNAMIC(CDialogTool)

public:
	CDialogTool(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogTool();

// 对话框数据
	enum { IDD = IDD_DIALOG_TOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnCancel();

	CTabCtrl m_tab;

	CButtonAutoCall3DPaint m_check_display_coordinate_axes;
	CButtonAutoCall3DPaint m_check_display_half_of_the_reactor;
	CButtonAutoCall3DPaint m_radio_display_electric_field_none;
	CButtonAutoCall3DPaint m_radio_display_electric_field_whole;
	CButtonAutoCall3DPaint m_radio_display_electric_field_electret;
	CButtonAutoCall3DPaint m_radio_display_electric_field_electret_by_positive_electricity_only;
	CButtonAutoCall3DPaint m_radio_display_electric_field_electret_by_negative_electricity_only;
	CButtonAutoCall3DPaint m_radio_display_electric_field_electron_on_the_kettle_inwall;
	CButtonAutoCall3DPaint m_radio_display_electric_field_nucleus_escaped_on_the_kettle_inwall;
	CButtonAutoCall3DPaint m_radio_display_electric_field_nucleus_in_the_kettle;
	CButtonAutoCall3DPaint m_radio_display_fuel_temperature;
	CButtonAutoCall3DPaint m_radio_display_particle_density;
	CButtonAutoCall3DPaint m_radio_display_lawson;
	CStaticRainbowValue m_static_display_rainbow_value;
	CEditFloat m_edit_display_min;
	CEditFloat m_edit_display_middle;
	CEditFloat m_edit_display_max;
	CEdit m_edit_display_unit;

	CStatic m_static_electret_charge_density;
	CSliderCtrl m_slider_electret_charge_density;
	CEdit m_edit_electret_charge_density;
	CStatic m_static_electret_thickness;
	CSliderCtrl m_slider_electret_thickness;
	CEdit m_edit_electret_thickness;

	CStatic m_static_kettle_outer_diameter;
	CSliderCtrl m_slider_kettle_outer_diameter;
	CEdit m_edit_kettle_outer_diameter;
	CStatic m_static_kettle_thickness;
	CSliderCtrl m_slider_kettle_thickness;
	CEdit m_edit_kettle_thickness;
	CStatic m_static_kettle_average_relative_dielectric_constant;
	CSliderCtrl m_slider_kettle_average_relative_dielectric_constant;
	CEdit m_edit_kettle_average_relative_dielectric_constant;

	CButton m_radio_fuel_deuterium_and_tritium;
	CStatic m_static_fuel_total_mass;
	CSliderCtrl m_slider_fuel_total_mass;
	CEdit m_edit_fuel_total_mass;
	CStatic m_static_fuel_equivalent_of_coal;
	CEdit m_edit_fuel_equivalent_of_coal;
	CStatic m_static_fuel_termperature;
	CSliderCtrl m_slider_fuel_termperature;
	CEdit m_edit_fuel_termperature;

	CStatic m_static_simulate_time;
	CEditFloat m_edit_simulate_time;
	CStatic m_static_simulate_escaped;
	CEditFloat m_edit_simulate_escaped;
	CStatic m_static_simulate_center_partide_density;
	CEditFloat m_edit_simulate_center_partide_density;
	CStatic m_static_simulate_center_temperature;
	CEditFloat m_edit_simulate_center_temperature;
	CStatic m_static_simulate_center_lawson;
	CEditFloat m_edit_simulate_center_lawson;
	CStatic m_static_simulate_center_lawson_criterion;
	CButton m_radio_simulate_center_lawson_criterion_pass;
	CButton m_radio_simulate_center_lawson_criterion_fail;
	CStaticLog m_static_simulate_log;
	CButton m_button_simulate_restart;
	CButton m_button_simulate_pause;
	CEdit m_eidt_simulate_output;

	CButton m_button_file_save;
	CButton m_button_file_save_as;
	CButton m_button_file_save_open;
	CButton m_button_file_help;
	CButton m_button_file_about;

	virtual void OnOK();


	struct SControl
	{
		CWnd * window;
		int original_x;
		int original_y;
		int width;
		int height;
	};
	static const int m_max_control_per_page=25;
	struct SPage
	{
		SControl control[m_max_control_per_page];
		int count;
		int top_left_x,top_left_y;
	};
	static const  int m_page_count=6;
	SPage m_page[m_page_count];
	virtual BOOL OnInitDialog();
	void OnTabSelect(int index);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

	void Update();
};
extern CDialogTool g_dialog_tool;