// IntialSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "IntialSetDlg.h"
#include "enmuHead.h"
#include "TestFuc.h"
#include "GobalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IntialSetDlg dialog


IntialSetDlg::IntialSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IntialSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(IntialSetDlg)
	m_bAutoOpen = FALSE;
	//}}AFX_DATA_INIT
}


void IntialSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IntialSetDlg)
	DDX_Check(pDX, IDC_CHECK_AUTO, m_bAutoOpen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IntialSetDlg, CDialog)
	//{{AFX_MSG_MAP(IntialSetDlg)
	ON_BN_CLICKED(IDC_BUTTON_SINGLE, OnButtonSingle)
	ON_BN_CLICKED(IDC_BUTTON_NET, OnButtonNet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IntialSetDlg message handlers

/*
 *	单机工作模式选择
 */
void IntialSetDlg::OnButtonSingle() 
{
    GobalData* g = GobalData::getGobalData();
	g->setWorkModel(WorkModel_SINGLE);
	setAutoSetDlg();
	CDialog::OnCancel();
}

/*
 *	网络工作模式选择
 */
void IntialSetDlg::OnButtonNet() 
{
    GobalData* g = GobalData::getGobalData();
	g->setWorkModel(WorkModel_NETWORK);
	setAutoSetDlg();
	CDialog::OnCancel();
}

/*
 *	设置工作模式对话框自动弹出
 */
void IntialSetDlg::setAutoSetDlg()
{
    UpdateData();
	GobalData* g = GobalData::getGobalData();
	g->getAutoSetFromFile(); 
	AUTOSET a = g->getAutoSet();
	a.b_initalDlg = m_bAutoOpen;
	g->setAutoSet(a);
	g->setAutoSetToFile();
}

BOOL IntialSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GobalData* g = GobalData::getGobalData();
	g->getAutoSetFromFile(); 
	AUTOSET a = g->getAutoSet();
	if(a.b_initalDlg)
	{
		m_bAutoOpen = TRUE;
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
