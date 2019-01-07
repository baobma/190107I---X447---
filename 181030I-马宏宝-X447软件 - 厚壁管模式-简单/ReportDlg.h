#if !defined(AFX_REPORTDLG_H__3A89A236_BD8E_4DA7_91CD_8FFE2AF73FC6__INCLUDED_)
#define AFX_REPORTDLG_H__3A89A236_BD8E_4DA7_91CD_8FFE2AF73FC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDlg.h : header file
//

#include "HUSTNDT.H"
/////////////////////////////////////////////////////////////////////////////
// ReportDlg dialog

class ReportDlg : public CDialog
{
// Construction
public:
	void reFreshReport();
	ReportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ReportDlg)
	enum { IDD = IDD_DIALOG_REPORTS };
	CListCtrl	m_conListReport;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ReportDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExcel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDLG_H__3A89A236_BD8E_4DA7_91CD_8FFE2AF73FC6__INCLUDED_)
