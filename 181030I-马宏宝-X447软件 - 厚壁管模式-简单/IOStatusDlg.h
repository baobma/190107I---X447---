#if !defined(AFX_IOSTATUSDLG_H__77E1616E_E7AE_4960_9777_70999CB98186__INCLUDED_)
#define AFX_IOSTATUSDLG_H__77E1616E_E7AE_4960_9777_70999CB98186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOStatusDlg.h : header file
//
#define IDD_DIALOG_IOSTATUS             143
/////////////////////////////////////////////////////////////////////////////
// CIOStatusDlg dialog
/*
 *	×´Ì¬¼à¿Ø¶Ô»°¿ò£¨Ä£Ì¬£©
 */
class CIOStatusDlg : public CDialog
{
// Construction
public:
	void setStatus(char s); //ÉèÖÃ¼à¿Ø×´Ì¬
	CIOStatusDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIOStatusDlg)
	enum { IDD = IDD_DIALOG_IOSTATUS };
	CStatic	m_pic8;
	CStatic	m_pic7;
	CStatic	m_pic6;
	CStatic	m_pic5;
	CStatic	m_pic4;
	CStatic	m_pic3;
	CStatic	m_pic2;
	CStatic	m_pic1;
	BOOL	m_bCheckPlus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIOStatusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIOStatusDlg)
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButtonStop();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBitmap iconClose;  //µÆÃðÍ¼
	CBitmap iconOpen;   //µÆ¿ªÍ¼
	CStatic* pics[8];   //Í¼±ê
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOSTATUSDLG_H__77E1616E_E7AE_4960_9777_70999CB98186__INCLUDED_)
