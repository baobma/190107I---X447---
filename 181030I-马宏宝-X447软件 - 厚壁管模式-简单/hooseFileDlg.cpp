// hooseFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "hooseFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "TestFuc.h"
#include "GobalData.h"
/////////////////////////////////////////////////////////////////////////////
// ChooseFileDlg dialog

 int caijimodel=0;
ChooseFileDlg::ChooseFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ChooseFileDlg::IDD, pParent)
{
	IsOpen = TRUE;
	//{{AFX_DATA_INIT(ChooseFileDlg)
	m_strFileName = _T("");
	m_strMan = _T("");
	m_strFind = _T("");
	m_iSid = 0;
	m_dataOpenMode = -1;
	m_strGuige = _T("");
	m_strPly = _T("");
	m_strSteel = _T("");
	m_bSaveToFile = FALSE;
	//}}AFX_DATA_INIT
}


void ChooseFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ChooseFileDlg)
	DDX_Control(pDX, IDC_LIST_FILENAMELIST, m_conListctrl);
	DDX_Control(pDX, IDC_LIST_BACK, m_listBack);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_MAN, m_strMan);
	DDX_Text(pDX, IDC_EDIT_FIND, m_strFind);
	DDX_Text(pDX, IDC_EDIT_SID, m_iSid);
	DDX_Radio(pDX, IDC_RADIO1, m_dataOpenMode);
	DDX_Text(pDX, IDC_EDIT_GUIGE, m_strGuige);
	DDX_Text(pDX, IDC_EDIT_PLY, m_strPly);
	DDX_Text(pDX, IDC_EDIT_STEEL, m_strSteel);
	DDX_Check(pDX, IDC_CHECK_JPG, m_bSaveToFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ChooseFileDlg, CDialog)
	//{{AFX_MSG_MAP(ChooseFileDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILENAMELIST, OnDblclkListFilenamelist)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FILENAMELIST, OnClickListFilenamelist)
	ON_EN_CHANGE(IDC_EDIT_FIND, OnChangeEditFind)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ChooseFileDlg message handlers

BOOL ChooseFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_conListctrl.InsertColumn(0,"文件名",LVCFMT_LEFT,120,-1);
	m_conListctrl.InsertColumn(1,"时间",LVCFMT_LEFT,90,-1);
	m_conListctrl.InsertColumn(2,"次数",LVCFMT_LEFT,50,-1);
	m_conListctrl.InsertColumn(3,"操作员",LVCFMT_LEFT,80,-1);
	m_conListctrl.InsertColumn(4,"钢级",LVCFMT_LEFT,80,-1);
	m_conListctrl.InsertColumn(5,"壁厚",LVCFMT_LEFT,80,-1);
	m_conListctrl.InsertColumn(6,"规格",LVCFMT_LEFT,80,-1);
	myInit(".");
	
	return TRUE;
}

void ChooseFileDlg::myInit(CString findstr)
{
	if(findstr.IsEmpty())
		findstr.Format(".");
	
	GobalData* g = GobalData::getGobalData();
    m_conListctrl.DeleteAllItems();

	m_conListctrl.SetTextColor(COLORREF(RGB(100,0,100)));

	m_dataOpenMode = 0;
	
	CString str;
	if(IsOpen == TRUE)
	{
		str.Format("data\\*.%s",suffix);
		GetDlgItem(IDC_EDIT_FILENAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAN)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PLY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_STEEL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GUIGE)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		m_iSid = g->getSid();
	}
	else
	{
		str.Format("data\\*.*");
		GetDlgItem(IDC_EDIT_FILENAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PLY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_STEEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GUIGE)->EnableWindow(FALSE);
	
	//	m_dataOpenMode = 1;
	//	GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	}
	m_dataOpenMode = 0;	
UpdateData(FALSE);
	m_listBack.ResetContent();
	m_listBack.Dir(0x0000,str);
	int k = 0;
	for(int i = 0; i < m_listBack.GetCount(); i++)
	{
		CString s;
		m_listBack.GetText(i,s);
		if(s.Find(findstr,0) == -1)
			continue;
		/*
		 *	添加时间、次数和操作员
		 */
		CFile file;
		try
		{   
			CString name;
			name.Format("data\\%s",s);
			DATAHEAD dHead;
			CString str = g->getWholeFileName();
			if(str != s)
			{
				if(!file.Open(name ,CFile::modeRead | CFile::typeBinary))
				{
					AfxMessageBox("ErrorCode:00009 文件读取失败");
					continue;
				}
				m_conListctrl.InsertItem(k,"");	
				m_conListctrl.SetItemText(k,0,s);
				file.Read(&dHead,sizeof(DATAHEAD));
				s.Format("%4d-%02d-%02d",dHead.year,dHead.month,dHead.day);
				m_conListctrl.SetItemText(i,1,s);
				s.Format("%d",dHead.blocksum);
				m_conListctrl.SetItemText(i,2,s);
				s.Format("%s",dHead.Uoperator);
				m_conListctrl.SetItemText(i,3,s);
				s.Format("%s",dHead.steel);
				m_conListctrl.SetItemText(i,4,s);
				s.Format("%s",dHead.ply);
				m_conListctrl.SetItemText(i,5,s);
				s.Format("%s",dHead.guige);
				m_conListctrl.SetItemText(i,6,s);
				file.Close();
			}
			else
			{
				m_conListctrl.InsertItem(k,"");	
				m_conListctrl.SetItemText(k,0,s);
				dHead = g->dataHead;
				s.Format("%4d-%02d-%02d",dHead.year,dHead.month,dHead.day);
				m_conListctrl.SetItemText(i,1,s);
				s.Format("%d",dHead.blocksum);
				m_conListctrl.SetItemText(i,2,s);
				s.Format("%s",dHead.Uoperator);
				m_conListctrl.SetItemText(i,3,s);
				s.Format("%s",dHead.steel);
				m_conListctrl.SetItemText(i,4,s);
				s.Format("%s",dHead.ply);
				m_conListctrl.SetItemText(i,5,s);
				s.Format("%s",dHead.guige);
				m_conListctrl.SetItemText(i,6,s);
			}
			k++;
		}
		catch (CException e)
		{
			file.Close();
			continue;
		}
	}
}

void ChooseFileDlg::OnDblclkListFilenamelist(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	UpdateData();
    int index = (pDispInfo->item).mask;
    if(IsOpen == TRUE)
	{
		char s1[100];
		char s2[100];
		s1[0] = '\0';
		m_conListctrl.GetItemText(index,0,s1,100);
		if(strlen(s1) < 5)
			return;
		memcpy(s2,s1,(strlen(s1)-4)*sizeof(char));
		s2[strlen(s1)-4] ='\0';
		m_strFileName = s2;

		m_conListctrl.GetItemText(index,3,s1,100);
		m_strMan = s1;

		m_conListctrl.GetItemText(index,4,s1,100);
		m_strSteel = s1;

		m_conListctrl.GetItemText(index,5,s1,100);
		m_strPly = s1;

		m_conListctrl.GetItemText(index,6,s1,100);
		m_strGuige = s1;
	}
	else
	{
		char s1[100];
		s1[0] = '\0';
		m_conListctrl.GetItemText(index,0,s1,100);
		if(strlen(s1) < 5)
			return;
		m_strFileName = s1;

		m_conListctrl.GetItemText(index,3,s1,100);;
		m_strMan = s1;

		m_conListctrl.GetItemText(index,4,s1,100);
		m_strSteel = s1;

		m_conListctrl.GetItemText(index,5,s1,100);
		m_strPly = s1;

		m_conListctrl.GetItemText(index,6,s1,100);
		m_strGuige = s1;
	}
	*pResult = 0;
	UpdateData(FALSE);
}

void ChooseFileDlg::OnOK() 
{	
	GobalData* g = GobalData::getGobalData();
	UpdateData();
	if(m_strFileName.GetLength() == 0)
		return;	
	memcpy((g->dataHead).Uoperator,m_strMan,m_strMan.GetLength());
	(g->dataHead).Uoperator[m_strMan.GetLength()] = '\0';
	
	memcpy((g->dataHead).steel,m_strSteel,m_strSteel.GetLength());
	(g->dataHead).steel[m_strSteel.GetLength()] = '\0';
	memcpy((g->dataHead).ply,m_strPly,m_strPly.GetLength());
	(g->dataHead).ply[m_strPly.GetLength()] = '\0';
	memcpy((g->dataHead).guige,m_strGuige,m_strGuige.GetLength());
	(g->dataHead).guige[m_strGuige.GetLength()] = '\0';
	
	CDialog::OnOK();
}

void ChooseFileDlg::OnClickListFilenamelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnDblclkListFilenamelist(pNMHDR, pResult);
	
	*pResult = 0;
}

void ChooseFileDlg::OnChangeEditFind() 
{
	UpdateData();
	myInit(m_strFind);
}

void ChooseFileDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	caijimodel=0;
}

void ChooseFileDlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	caijimodel=1;
}
