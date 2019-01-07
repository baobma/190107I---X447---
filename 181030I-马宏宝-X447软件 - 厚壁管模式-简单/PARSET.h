#if !defined(AFX_PARSET_H__589447DE_A61F_49DA_AB92_603B554348CA__INCLUDED_)
#define AFX_PARSET_H__589447DE_A61F_49DA_AB92_603B554348CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PARSET.h : header file
//

#include "MParDlg.h"
/////////////////////////////////////////////////////////////////////////////
// PARSET dialog
/*
 *	参数设置对话框类
 */
class PARSET : public CDialog
{
// Construction
public:
	BOOL analysis;  //是否是做分析时使用TRUE 是 FALSE否
	PARSET(CWnd* pParent = NULL);   // standard constructor
     void WritelvboTofile(CString strFileName);
void ReadlvboToFile(CString strFileName);
// Dialog Data
	//{{AFX_DATA(PARSET)
	enum { IDD = IDD_DIALOG_PARSET };
	CComboBox	m_conBoxIndex;
	CListCtrl	m_conListCtrl;
	float	m_fSpeed;
	float		m_menxianzhi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PARSET)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PARSET)
	virtual BOOL OnInitDialog();
	afx_msg void OnEndlabeleditListPar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListPar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListPar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonReset();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnSelchangeComboIndex();
	afx_msg void OnButtonSave();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void changeParIndex(int index);
	void ParsInit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSET_H__589447DE_A61F_49DA_AB92_603B554348CA__INCLUDED_)
