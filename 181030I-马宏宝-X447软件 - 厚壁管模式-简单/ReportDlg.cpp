// ReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReportDlg.h"
#include "GobalData.h"
#include "DataSaveFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReportDlg dialog


ReportDlg::ReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ReportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if(Create(ReportDlg::IDD, pParent))
		ShowWindow(SW_SHOW);
	else
		AfxMessageBox("×´Ì¬¼à¿ØÆô¶¯Ê§°Ü");
}


void ReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ReportDlg)
	DDX_Control(pDX, IDC_LIST_REPORT, m_conListReport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ReportDlg, CDialog)
	//{{AFX_MSG_MAP(ReportDlg)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL, OnButtonExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ReportDlg message handlers

void ReportDlg::OnCancel() 
{
	CDialog::OnCancel();
	delete this;
	GobalData* g = GobalData::getGobalData();
	g->reportdlg = NULL;
}

BOOL ReportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	reFreshReport();
	return TRUE;
}

void ReportDlg::OnButtonExcel() 
{
    GobalData* g = GobalData::getGobalData();
    DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());
	style->DoReport(m_conListReport,TRUE);
	
	DeletePtr(style);
}

void ReportDlg::reFreshReport()
{
    GobalData* g = GobalData::getGobalData();
    DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());
	style->DoReport(m_conListReport,FALSE);
	
	DeletePtr(style);
}
