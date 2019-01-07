#if !defined(AFX_STRPARDLG_H__667CFDDE_890B_4846_A412_6C1FF645DEEE__INCLUDED_)
#define AFX_STRPARDLG_H__667CFDDE_890B_4846_A412_6C1FF645DEEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StrParDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStrParDlg dialog
/*
 *	字符串参数设置辅助对话框
 */
class CStrParDlg : public CDialog
{
// Construction
public:
	int maxCharNum;
	CStrParDlg(CWnd* pParent = NULL);   // standard constructor
    CString strs[8];
// Dialog Data
	//{{AFX_DATA(CStrParDlg)
	enum { IDD = IDD_DIALOG_STRPAR };
	CString	m_str1;
	CString	m_str2;
	CString	m_str3;
	CString	m_str4;
	CString	m_str5;
	CString	m_str6;
	CString	m_str7;
	CString	m_str8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrParDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStrParDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonResume();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString* mstrs[8];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRPARDLG_H__667CFDDE_890B_4846_A412_6C1FF645DEEE__INCLUDED_)
