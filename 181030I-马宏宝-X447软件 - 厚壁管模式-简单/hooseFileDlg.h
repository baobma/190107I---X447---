#if !defined(AFX_HOOSEFILEDLG_H__0CB51846_6684_437B_8098_81D9E8E53E8A__INCLUDED_)
#define AFX_HOOSEFILEDLG_H__0CB51846_6684_437B_8098_81D9E8E53E8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// hooseFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ChooseFileDlg dialog

class ChooseFileDlg : public CDialog
{
// Construction
public:
	BOOL IsOpen;    //TURE为采集打开  FALSE为历史打开
	char* suffix;
	ChooseFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ChooseFileDlg)
	enum { IDD = IDD_DIALOG_CHOOSEFILE };
	CListCtrl	m_conListctrl;
	CListBox	m_listBack;
	CString	m_strFileName;
	CString	m_strMan;
	CString	m_strFind;
	int		m_iSid;
	int		m_dataOpenMode;
	CString	m_strGuige;
	CString	m_strPly;
	CString	m_strSteel;
	BOOL	m_bSaveToFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ChooseFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ChooseFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListFilenamelist(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnClickListFilenamelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditFind();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void myInit(CString str);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOOSEFILEDLG_H__0CB51846_6684_437B_8098_81D9E8E53E8A__INCLUDED_)
