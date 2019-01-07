#if !defined(AFX_ARDSET_H__4B583B52_5167_4DA4_9A62_08158EDA4213__INCLUDED_)
#define AFX_ARDSET_H__4B583B52_5167_4DA4_9A62_08158EDA4213__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ARDSET.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CARDSET dialog
/*
 *	采集卡设置对话框
 */
class CARDSET : public CDialog
{
// Construction
private:
	float VZero,VMax;
	int dx;
	int dy;
public:
	HWND cardWnd;
	void setParDlg();
	CARDSET(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CARDSET)
	enum { IDD = IDD_DIALOG_SETCARD };
	CStatic	m_sStartCH;
	CEdit	m_eCH;
	CButton	m_cbCoding;
	CStatic	m_sSampleSpeed;
	CStatic	m_sChannelNum;
	CStatic	m_sBlock;
	CEdit	m_eSampleSpeed;
	CEdit	m_eChannelNum;
	CEdit	m_eBlock;
	CComboBox	m_conCardChoose;
	int		m_iBlock;
	int		m_iChannelNum;
	int		m_iSampleSpeed;
	BOOL	m_bCoding;
	int		m_iStartCH;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CARDSET)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CARDSET)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARDSET_H__4B583B52_5167_4DA4_9A62_08158EDA4213__INCLUDED_)
