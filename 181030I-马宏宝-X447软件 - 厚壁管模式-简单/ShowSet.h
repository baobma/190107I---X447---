#if !defined(AFX_SHOWSET_H__AD52699C_7DE1_4AFF_9BDF_F38481906904__INCLUDED_)
#define AFX_SHOWSET_H__AD52699C_7DE1_4AFF_9BDF_F38481906904__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowSet.h : header file
//
#include "WaveShow.h"
/////////////////////////////////////////////////////////////////////////////
// ShowSet dialog

class ShowSet : public CDialog
{
// Construction
public:
	BOOL halfs[8];
	short showcompress[8];
	short timelapes[8];
	short alertlines[8];
	short alertlines2[8];
	short alertlines3[8];
	short differadjust[8];
	short differ[8];
	int steps[8];
	ShowSet(CWnd* pParent = NULL);   // standard constructor
    int stepArray[10];
	char titles[8][20];
	char DItitles[8][20];
	char DOtitles[8][20];
	short restrain[8];
// Dialog Data
	//{{AFX_DATA(ShowSet)
	enum { IDD = IDD_DIALOG_SHOWSET };
	CComboBox	m_comb_vacc;
	CComboBox	m_comb_hacc;
	CListCtrl	m_conListTHR;
	CComboBox	m_constep8;
	CComboBox	m_constep7;
	CComboBox	m_constep6;
	CComboBox	m_constep5;
	CComboBox	m_constep4;
	CComboBox	m_constep3;
	CComboBox	m_constep2;
	CComboBox	m_constep1;
	CListCtrl	m_conListCtrl;
	int		m_ishowset;
	BOOL	m_b1;
	BOOL	m_b2;
	BOOL	m_b4;
	BOOL	m_b3;
	BOOL	m_b5;
	BOOL	m_b6;
	BOOL	m_b7;
	BOOL	m_b8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShowSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShowSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnDblclkListShowch(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListThr(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonReset();
	afx_msg void OnButton1();
	afx_msg void OnSelchangeComboHacc();
	afx_msg void OnSelendcancelComboVacc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ThrInit();
    CComboBox* boxs[8];
	void ParsInit();
	int dx;
	int dy;
	int hacc;
	int vacc;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWSET_H__AD52699C_7DE1_4AFF_9BDF_F38481906904__INCLUDED_)
