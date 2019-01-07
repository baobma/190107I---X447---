#if !defined(AFX_MSGDLG_H__91BBF38A_6618_4799_83A1_1334F0C376B0__INCLUDED_)
#define AFX_MSGDLG_H__91BBF38A_6618_4799_83A1_1334F0C376B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MsgDlg dialog

class MsgDlg : public CDialog
{
// Construction
public:
	int timespace;
	MsgDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MsgDlg)
	enum { IDD = IDD_DIALOG_MSGDLG };
	CString	m_strMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MsgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGDLG_H__91BBF38A_6618_4799_83A1_1334F0C376B0__INCLUDED_)
