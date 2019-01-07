#if !defined(AFX_MPARDLG_H__21BBB60D_359F_4034_AFBD_919C02A25F1A__INCLUDED_)
#define AFX_MPARDLG_H__21BBB60D_359F_4034_AFBD_919C02A25F1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MParDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MParDlg dialog
/*
 *	参数设置辅助对话框
 */
class MParDlg : public CDialog
{
// Construction
public:
	int max;
	int min;
	int index;
	int offset;
	short int data[8];
	short* mdata[8];
	MParDlg(CWnd* pParent = NULL);   // standard constructor
	char* title;
// Dialog Data
	//{{AFX_DATA(MParDlg)
	enum { IDD = IDD_DIALOG_M_Par };
	CStatic	m_static8;
	CStatic	m_static7;
	CStatic	m_static6;
	CStatic	m_static5;
	CStatic	m_static4;
	CStatic	m_static3;
	CStatic	m_static2;
	CStatic	m_static1;
	short	m_s1;
	short	m_s2;
	short	m_s3;
	short	m_s4;
	short	m_s5;
	short	m_s6;
	short	m_s7;
	short	m_s8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MParDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MParDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonResume();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MPARDLG_H__21BBB60D_359F_4034_AFBD_919C02A25F1A__INCLUDED_)
