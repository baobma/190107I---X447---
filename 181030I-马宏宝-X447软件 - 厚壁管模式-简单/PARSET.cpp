// PARSET.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "PARSET.h"
#include "DataBuf.h"
#include "GobalData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PARSET dialog
//extern float G_m_menxianzhi=0;
extern int  Ready_Only;

PARSET::PARSET(CWnd* pParent /*=NULL*/)
	: CDialog(PARSET::IDD, pParent)
{
	//{{AFX_DATA_INIT(PARSET)
	m_fSpeed = 0.0f;
	m_menxianzhi = 0.0f;
	//}}AFX_DATA_INIT
}


void PARSET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PARSET)
	DDX_Control(pDX, IDC_COMBO_INDEX, m_conBoxIndex);
	DDX_Control(pDX, IDC_LIST_PAR, m_conListCtrl);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_fSpeed);
	DDX_Text(pDX, IDC_EDIT_menxian, m_menxianzhi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PARSET, CDialog)
	//{{AFX_MSG_MAP(PARSET)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_PAR, OnEndlabeleditListPar)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PAR, OnClickListPar)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PAR, OnDblclkListPar)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_WM_HELPINFO()
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, OnSelchangeComboIndex)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PARSET message handlers

BOOL PARSET::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ReadlvboToFile("par\\automaneofnew.par");
	UpdateData(FALSE);
	for(int i = 0; i < PARMAXNUM; i++)
	{
		char s[20];
		_itoa(i+1,s,10);
		m_conBoxIndex.AddString(s);
	}
	m_conBoxIndex.SetCurSel(0);

	m_conListCtrl.InsertColumn(0,"通道编号  ",LVCFMT_LEFT,100,-1);
	m_conListCtrl.InsertColumn(1,"1  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(2,"2  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(3,"3  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(4,"4  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(5,"5  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(6,"6  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(7,"7  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(8,"8  ",LVCFMT_LEFT,40,-1);
	
	m_conListCtrl.SetTextColor(COLORREF(RGB(100,0,100)));
	if(analysis == TRUE)
	{
		m_conBoxIndex.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
	}
	if ( Ready_Only == 1 )
	{
		this->GetDlgItem(IDC_BUTTON_RESET)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_BUTTON_H)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_BUTTON_Z)->ShowWindow(SW_HIDE);
	}
	
    ParsInit();

	return TRUE;
}

void PARSET::OnEndlabeleditListPar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	int item = (pDispInfo->item).iItem;
	int subitem = (pDispInfo->item).iSubItem;
	CString str = (pDispInfo->item).pszText;
	m_conListCtrl.SetItemText(item,subitem,str);
	
	*pResult = 0;
}

void PARSET::OnClickListPar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void PARSET::OnDblclkListPar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    	int index = (pDispInfo->item).mask;

	if(index < 0)
		return;
	MParDlg dlg;
	dlg.min = 0;
	dlg.max = 20000;   ///max增益
	dlg.index = index;
	dlg.offset = 4;
    	short a[8];
if(index > 7 )
	dlg.offset =8;
	for(int j = 1; j < 9; j++)
	{
		char s[20];
		m_conListCtrl.GetItemText(index,j,s,20);
		a[j-1]= atoi(s);	
	}
	memcpy(dlg.data,a,8*sizeof(short));

	if(dlg.DoModal() == IDOK)
	{
         memcpy(a,dlg.data,8*sizeof(short));
	}

	for(j = 1; j < 9; j++)
	{
		char s[20];
		itoa(a[j-1],s,10);
		m_conListCtrl.SetItemText(index,j,s);	
	}

	*pResult = 0;
}

/*
 *	初始化按钮
 */
void PARSET::OnButtonReset() 
{
	CFile parfile;
	CString filename;
	int id = 0;
	filename.Format("par\\pars.par");
	if(!parfile.Open(filename,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:0001 参数文件读取失败");
		return;
	}
    	short b = 1;
	parfile.Write(&b,sizeof(short)); //当前使用第一组数据
	m_conBoxIndex.SetCurSel(0);
	GobalData* g = GobalData::getGobalData();
	int channel = (g->getDataBuf())->getChannelNum();
	/*
	 *	增益参数全部清0
	 */
	for(int i = 0; i < PARMAXNUM; i++)
	{
		short* a = new short[channel];
		memset(a,0,channel*sizeof(short));
		parfile.Write(a,channel*sizeof(short));
		DeleteArray(a);
	}
	parfile.Close();
	AfxMessageBox("参数初始化成功");
	ParsInit();
}

BOOL PARSET::OnHelpInfo(HELPINFO* pHelpInfo) 
{	
	return CDialog::OnHelpInfo(pHelpInfo);
}

void PARSET::ParsInit()
{
	GobalData* g = GobalData::getGobalData();
	int index = (g->getDataBuf())->getParsIndex();
	changeParIndex(index);
	m_conBoxIndex.SetCurSel(index-1);

	AUTOSET& set = g->getAutoSet();
	m_fSpeed = set.speed;
	UpdateData(FALSE);
}

void PARSET::OnSelchangeComboIndex() 
{
	int index = m_conBoxIndex.GetCurSel() + 1;
    changeParIndex(index);
}

/*
 *	切换选择参数组号
 *  index：要切换到的参数组号
 */
void PARSET::changeParIndex(int index)
{
    CString str[] = {
		"5 ~  12","13 ~  20","21 ~  28","29 ~  36","37 ~  44","45 ~  52","53 ~  60","61 ~  68",
		"73 ~ 80","81 ~ 88","89 ~ 96","97 ~104","105~112","113~120","121~128","129~136"		
	};
	
	GobalData* g = GobalData::getGobalData();
	int channel = (g->getDataBuf())->getChannelNum();
	short* ps = new short[channel];
	if(analysis == FALSE)
	    (g->getDataBuf())->loadParFromFile(index,ps);
	else
		memcpy(ps,(g->getDataBuf())->getParPtr(),channel*sizeof(short));
	m_conListCtrl.DeleteAllItems();
	for(int i = 0; i < channel/8-1; i++)
	{
		m_conListCtrl.InsertItem(i,"");
		m_conListCtrl.SetItemText(i,0,str[i]);
		for(int j = 1; j < 9; j++)
		{
			short a ;
			if(i < 8)
				a= ps[8*i + j - 1+4];
			else
				a= ps[8*i + j - 1+8];
			char s[20];
			_itoa(int(a),s,10);
			m_conListCtrl.SetItemText(i,j,s);
		}
	}
	DeleteArray(ps);;
}

void PARSET::OnButtonSave() 
{
	GobalData* g = GobalData::getGobalData();
	int channel = (g->getDataBuf())->getChannelNum();
	short* ps = new short[channel];
	
	for(int i = 0; i < channel/8-1; i++)
	{
		for(int j = 1; j < 9; j++)
		{
			char s[20];
			m_conListCtrl.GetItemText(i,j,s,20);
			if(i < 8 )
				ps[i*8+j-1+4]= atoi(s);
			else
				ps[i*8+j-1+8]= atoi(s);
			//ps[i*8+j-1]= atoi(s);	
		}
	}
	int index = m_conBoxIndex.GetCurSel() + 1;
	(g->getDataBuf())->saveParToFile(index,ps,FALSE);
	DeleteArray(ps);
}

/*
 *	选择按钮
 */
void PARSET::OnOK() 
{
	UpdateData();
	GobalData* g = GobalData::getGobalData();
	int channel = (g->getDataBuf())->getChannelNum();
	short* ps = new short[channel];
	
	/*
	 *	取得当前增益参数
	 */
	for(int i = 0; i < channel/8-1; i++)
	{
		for(int j = 1; j < 9; j++)
		{
			char s[20];
			m_conListCtrl.GetItemText(i,j,s,20);
		//	ps[i*8+j-1]= atoi(s);	
			if(i < 8 )
				ps[i*8+j-1+4]= atoi(s);
			else
				ps[i*8+j-1+8]= atoi(s);
		}
	}
	int index = m_conBoxIndex.GetCurSel() + 1;
	if(analysis == FALSE) //如不是分析状态则将增益保存到文件中
	{
	    (g->getDataBuf())->saveParToFile(index,ps,TRUE);
	    (g->getDataBuf())->loadIndexParsFromFile();
    	}
	else //如是分析状态则不保存
	{
         	DataBuf* buf = g->getDataBuf();
		 memcpy(buf->getParPtr(),ps,channel*sizeof(short));
	}
	DeleteArray(ps);
	
	AUTOSET set = g->getAutoSet();
	set.speed = m_fSpeed;
	g->setAutoSet(set);
	if(analysis == FALSE)
	g->setAutoSetToFile();
//	G_m_menxianzhi=m_menxianzhi;

	WritelvboTofile("par\\automaneofnew.par");	
	CDialog::OnOK();
}


void PARSET::WritelvboTofile(CString strFileName)
{
	
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {
	//	AfxMessageBox("lvbo File write error!");
		return;
	}	
	CString strData;
	
	strData.Format("%.1f\n",m_menxianzhi);
	file.WriteString(strData);

	file.Close();
	
}


void PARSET::ReadlvboToFile(CString strFileName)
{
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeRead)) 
	{
	//	AfxMessageBox("Read lvbo file error!");
		return;
	}
	
	CString strData;
	if (!file.ReadString(strData)) 
	{
		return;
	}
	sscanf(strData.GetBuffer(0), "%f", &m_menxianzhi);
	
	file.Close();
	
}

void PARSET::OnButton1() 
{
	// TODO: Add your control notification handler code here
	short a = 0;
	char s[20];
	m_conListCtrl.GetItemText(0,1,s,20);
	a= atoi(s);		
	
    for(int i = 0; i<8;i++)
	{
		for(int j = 1; j < 9; j++)
		{
			char s[20];
			itoa(a,s,10);
			m_conListCtrl.SetItemText(i,j,s);	
		}
	}
}

void PARSET::OnButton2() 
{
	// TODO: Add your control notification handler code here
	short a = 0;
	char s[20];
	m_conListCtrl.GetItemText(8,1,s,20);
	a= atoi(s);		

	for( int i = 8; i<18;i++)
	{
		for(int j = 1; j < 9; j++)
		{
			char s[20];
			itoa(a,s,10);
			m_conListCtrl.SetItemText(i,j,s);	
		}
	}
}
