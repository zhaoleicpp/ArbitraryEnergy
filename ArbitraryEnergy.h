
// ArbitraryEnergy.h : main header file for the ArbitraryEnergy application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CArbitraryEnergyApp:
// See ArbitraryEnergy.cpp for the implementation of this class
//

class CArbitraryEnergyApp : public CWinApp
{
public:
	CArbitraryEnergyApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CArbitraryEnergyApp theApp;
