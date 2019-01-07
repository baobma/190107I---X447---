// MParDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "MParDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MParDlg dialog


MParDlg::MParDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MParDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MParDlg)
	m_s1 = 0;
	m_s2 = 0;
	m_s3 = 0;
	m_s4 = 0;
	m_s5 = 0;
	m_s6 = 0;
	m_s7 = 0;
	m_s8 = 0;
	offset = 0;
	title ="参数设置";
	//}}AFX_DATA_INIT
}


void MParDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MParDlg)
	DDX_Control(pDX, IDC_STATIC8, m_static8);
	DDX_Control(pDX, IDC_STATIC7, m_static7);
	DDX_Control(pDX, IDC_STATIC6, m_static6);
	DDX_Control(pDX, IDC_STATIC5, m_static5);
	DDX_Control(pDX, IDC_STATIC4, m_static4);
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC2, m_static2);
	DDX_Control(pDX, IDC_STATIC1, m_static1);
	DDX_Text(pDX, IDC_EDIT1, m_s1);
	DDX_Text(pDX, IDC_EDIT2, m_s2);
	DDX_Text(pDX, IDC_EDIT3, m_s3);
	DDX_Text(pDX, IDC_EDIT4, m_s4);
	DDX_Text(pDX, IDC_EDIT5, m_s5);
	DDX_Text(pDX, IDC_EDIT6, m_s6);
	DDX_Text(pDX, IDC_EDIT7, m_s7);
	DDX_Text(pDX, IDC_EDIT8, m_s8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MParDlg, CDialog)
	//{{AFX_MSG_MAP(MParDlg)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_RESUME, OnButtonResume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MParDlg message handlers


BOOL MParDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	mdata[0] = &m_s1;
	mdata[1] = &m_s2;
	mdata[2] = &m_s3;
	mdata[3] = &m_s4;
	mdata[4] = &m_s5;
	mdata[5] = &m_s6;
	mdata[6] = &m_s7;
	mdata[7] = &m_s8;

	for(int i = 0; i <8; i++)
	{
		*mdata[i] = data[i];
	}
	CStatic* csc[8] = {
		&m_static1,&m_static2,&m_static3,&m_static4,
		&m_static5,&m_static6,&m_static7,&m_static8,
	};

	for(int j = 0; j < 8; j++)
	{
		char s[20];
		itoa(int(index*8 + j + 1+offset),s,10);
	    csc[j]->SetWindowText(s);
	}
	this->SetWindowText(title);
	UpdateData(FALSE);	
	return TRUE;
}

void MParDlg::OnButtonReset() 
{
	UpdateData();
    for(int i = 0; i < 8; i++)
	{
		*mdata[i] = *mdata[0];
	}
	UpdateData(FALSE);
}

void MParDlg::OnButtonResume() 
{
    for(int i = 0; i < 8; i++)
	{
		*mdata[i] = data[i];
	}
	
	UpdateData(FALSE);	
}

void MParDlg::OnOK() 
{
	UpdateData();
	for(int i = 0; i < 8; i++)
	{
		if(*mdata[i] < min || *mdata[i] > max)
		{
			AfxMessageBox("输入范围不正确");
			return;
		}
	}
    for(    i = 0; i < 8; i++)
	{
	    data[i] = *mdata[i];
	}
	CDialog::OnOK();
}
