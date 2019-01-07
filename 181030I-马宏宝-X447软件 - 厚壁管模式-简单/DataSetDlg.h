#if !defined(AFX_DATASETDLG_H__6C84B911_0409_408E_9E00_C1B816CED9FA__INCLUDED_)
#define AFX_DATASETDLG_H__6C84B911_0409_408E_9E00_C1B816CED9FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DataSetDlg dialog

/*
 *	数据保存格式设置对话框
 */
class DataSetDlg : public CDialog
{
// Construction
public:
	DataSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DataSetDlg)
	enum { IDD = IDD_DIALOG_DATASET };
	CComboBox	m_conBoxDataSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DataSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DataSetDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASETDLG_H__6C84B911_0409_408E_9E00_C1B816CED9FA__INCLUDED_)
