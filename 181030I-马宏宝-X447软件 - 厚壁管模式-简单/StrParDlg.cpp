// StrParDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "StrParDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrParDlg dialog


CStrParDlg::CStrParDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStrParDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStrParDlg)
	m_str1 = _T("");
	m_str2 = _T("");
	m_str3 = _T("");
	m_str4 = _T("");
	m_str5 = _T("");
	m_str6 = _T("");
	m_str7 = _T("");
	m_str8 = _T("");
	//}}AFX_DATA_INIT
}


void CStrParDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrParDlg)
	DDX_Text(pDX, IDC_EDIT1, m_str1);
	DDX_Text(pDX, IDC_EDIT2, m_str2);
	DDX_Text(pDX, IDC_EDIT3, m_str3);
	DDX_Text(pDX, IDC_EDIT4, m_str4);
	DDX_Text(pDX, IDC_EDIT5, m_str5);
	DDX_Text(pDX, IDC_EDIT6, m_str6);
	DDX_Text(pDX, IDC_EDIT7, m_str7);
	DDX_Text(pDX, IDC_EDIT8, m_str8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStrParDlg, CDialog)
	//{{AFX_MSG_MAP(CStrParDlg)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_RESUME, OnButtonResume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStrParDlg message handlers

BOOL CStrParDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    mstrs[0] = &m_str1;
	mstrs[1] = &m_str2;
	mstrs[2] = &m_str3;
	mstrs[3] = &m_str4;
	mstrs[4] = &m_str5;
	mstrs[5] = &m_str6;
	mstrs[6] = &m_str7;
	mstrs[7] = &m_str8;

	for(int i = 0; i < 8; i++)
	{
        *mstrs[i] = strs[i];
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStrParDlg::OnOK() 
{
	UpdateData();
	for(int i = 0; i < 8; i++)
	{
		if((*mstrs[i]).GetLength() > maxCharNum-1)
		{
			AfxMessageBox("字段过长，请重新输入");
			return;
		}
	}

    for(    i = 0; i < 8; i++)
	{
		strs[i] = *mstrs[i];
	}
	CDialog::OnOK();
}

void CStrParDlg::OnButtonReset() 
{
	UpdateData();
    for(int i = 0; i < 8; i++)
	{
		*mstrs[i] = *mstrs[0];
	}
	UpdateData(FALSE);
}

void CStrParDlg::OnButtonResume() 
{
	for(int i = 0; i < 8; i++)
	{
		*mstrs[i] = strs[i];
	}
	
	UpdateData(FALSE);	
}
