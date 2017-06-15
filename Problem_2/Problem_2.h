
// Problem_2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CProblem_2App:
// See Problem_2.cpp for the implementation of this class
//

class CProblem_2App : public CWinApp
{
public:
	CProblem_2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CProblem_2App theApp;