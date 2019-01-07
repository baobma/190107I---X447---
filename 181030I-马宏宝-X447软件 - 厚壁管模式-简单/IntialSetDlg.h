#if !defined(AFX_INTIALSETDLG_H__A58078A7_8565_448B_AE75_38CA584F1A83__INCLUDED_)
#define AFX_INTIALSETDLG_H__A58078A7_8565_448B_AE75_38CA584F1A83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IntialSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IntialSetDlg dialog
/*
 *	初始化设置对话框类
 */
class IntialSetDlg : public CDialog
{
// Construction
private:
	void setAutoSetDlg();
public:
	IntialSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IntialSetDlg)
	enum { IDD = IDD_DIALOG_INTIALSET };
	BOOL	m_bAutoOpen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IntialSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IntialSetDlg)
	afx_msg void OnButtonSingle();
	afx_msg void OnButtonNet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTIALSETDLG_H__A58078A7_8565_448B_AE75_38CA584F1A83__INCLUDED_)
