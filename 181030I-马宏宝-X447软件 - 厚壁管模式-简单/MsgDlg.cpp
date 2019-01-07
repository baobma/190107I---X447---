// MsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "MsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MsgDlg dialog


MsgDlg::MsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MsgDlg)
	timespace = 1000;
	m_strMsg = _T("");
	//}}AFX_DATA_INIT
}


void MsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MsgDlg)
	DDX_Text(pDX, IDC_STATIC_MSG, m_strMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MsgDlg, CDialog)
	//{{AFX_MSG_MAP(MsgDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MsgDlg message handlers

BOOL MsgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetTimer(1,timespace,0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MsgDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(1);
	CDialog::OnTimer(nIDEvent);
	CDialog::OnCancel();
}
