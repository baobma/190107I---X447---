// HUSTNDT.h : main header file for the HUSTNDT application
//

#if !defined(AFX_HUSTNDT_H__E4FCB3A9_553F_4F33_AF1C_2A1B2F71612D__INCLUDED_)
#define AFX_HUSTNDT_H__E4FCB3A9_553F_4F33_AF1C_2A1B2F71612D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTApp:
// See HUSTNDT.cpp for the implementation of this class
//

class CHUSTNDTApp : public CWinApp
{
public:
	void myInit();
	CHUSTNDTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHUSTNDTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHUSTNDTApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EnableLoad();
	void ReadlvboToFile(CString strFileName);
	void WritelvboTofile(CString strFileName);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUSTNDT_H__E4FCB3A9_553F_4F33_AF1C_2A1B2F71612D__INCLUDED_)
