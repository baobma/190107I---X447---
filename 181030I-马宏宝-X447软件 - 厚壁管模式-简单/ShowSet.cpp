// ShowSet.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "ShowSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "GobalData.h"
#include "MParDlg.h"
#include "StrParDlg.h"
/////////////////////////////////////////////////////////////////////////////
// ShowSet dialog
extern int  Ready_Only;


ShowSet::ShowSet(CWnd* pParent /*=NULL*/)
	: CDialog(ShowSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(ShowSet)
	m_ishowset = 0;
	m_b1 = FALSE;
	m_b2 = FALSE;
	m_b4 = FALSE;
	m_b3 = FALSE;
	m_b5 = FALSE;
	m_b6 = FALSE;
	m_b7 = FALSE;
	m_b8 = FALSE;
	//}}AFX_DATA_INIT
}


void ShowSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShowSet)
	DDX_Control(pDX, IDC_COMBO_VACC, m_comb_vacc);
	DDX_Control(pDX, IDC_COMBO_HACC, m_comb_hacc);
	DDX_Control(pDX, IDC_LIST_THR, m_conListTHR);
	DDX_Control(pDX, IDC_COMBO8, m_constep8);
	DDX_Control(pDX, IDC_COMBO7, m_constep7);
	DDX_Control(pDX, IDC_COMBO6, m_constep6);
	DDX_Control(pDX, IDC_COMBO5, m_constep5);
	DDX_Control(pDX, IDC_COMBO4, m_constep4);
	DDX_Control(pDX, IDC_COMBO3, m_constep3);
	DDX_Control(pDX, IDC_COMBO2, m_constep2);
	DDX_Control(pDX, IDC_COMBO1, m_constep1);
	DDX_Control(pDX, IDC_LIST_SHOWCH, m_conListCtrl);
	DDX_Radio(pDX, IDC_RADIO1, m_ishowset);
	DDX_Check(pDX, IDC_CHECK1, m_b1);
	DDX_Check(pDX, IDC_CHECK2, m_b2);
	DDX_Check(pDX, IDC_CHECK4, m_b4);
	DDX_Check(pDX, IDC_CHECK3, m_b3);
	DDX_Check(pDX, IDC_CHECK5, m_b5);
	DDX_Check(pDX, IDC_CHECK6, m_b6);
	DDX_Check(pDX, IDC_CHECK7, m_b7);
	DDX_Check(pDX, IDC_CHECK8, m_b8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShowSet, CDialog)
	//{{AFX_MSG_MAP(ShowSet)
	ON_WM_PAINT()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SHOWCH, OnDblclkListShowch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_THR, OnDblclkListThr)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_HACC, OnSelchangeComboHacc)
	ON_CBN_SELENDCANCEL(IDC_COMBO_VACC, OnSelendcancelComboVacc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShowSet message handlers

BOOL ShowSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	RECT Client_Size;
	GetClientRect(&Client_Size);	
	dx = Client_Size.right/20;
	dy = Client_Size.bottom/20;

	m_conListCtrl.InsertColumn(0,"显示块号  ",LVCFMT_LEFT,100,-1);
	m_conListCtrl.InsertColumn(1,"1  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(2,"2  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(3,"3  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(4,"4  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(5,"5  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(6,"6  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(7,"7  ",LVCFMT_LEFT,40,-1);
	m_conListCtrl.InsertColumn(8,"8  ",LVCFMT_LEFT,40,-1);
	
	m_conListCtrl.SetTextColor(COLORREF(RGB(0,66,33)));

	m_conListTHR.InsertColumn(0,"显示块号  ",LVCFMT_LEFT,100,-1);
	m_conListTHR.InsertColumn(1,"1  ",LVCFMT_LEFT,40,-1);
	m_conListTHR.InsertColumn(2,"2  ",LVCFMT_LEFT,40,-1);
	m_conListTHR.InsertColumn(3,"3  ",LVCFMT_LEFT,40,-1);
	m_conListTHR.InsertColumn(4,"4  ",LVCFMT_LEFT,40,-1);
	m_conListTHR.InsertColumn(5,"5  ",LVCFMT_LEFT,40,-1);
	m_conListTHR.InsertColumn(6,"6  ",LVCFMT_LEFT,40,-1);
	m_conListTHR.InsertColumn(7,"7  ",LVCFMT_LEFT,40,-1);
	m_conListTHR.InsertColumn(8,"8  ",LVCFMT_LEFT,40,-1);
	
	m_conListTHR.SetTextColor(COLORREF(RGB(0,66,33)));


	m_comb_hacc.AddString("0");
	m_comb_hacc.AddString("1");
	m_comb_hacc.AddString("2");
	m_comb_hacc.AddString("3");
	m_comb_hacc.AddString("4");
	

	m_comb_vacc.AddString("0");
	m_comb_vacc.AddString("1");
	m_comb_vacc.AddString("2");
	m_comb_vacc.AddString("3");
	m_comb_vacc.AddString("4");

	GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();

	hacc = set.nserl_hacc;
	vacc = set.nserl_vacc;

	m_comb_hacc.SetCurSel(hacc);
	m_comb_vacc.SetCurSel(vacc);

	
//	g->getShowCHSfromFile();
	
    ParsInit();
    ThrInit();
if( Ready_Only == 1 )
	{
		this->GetDlgItem(IDC_BUTTON_RESET)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO3)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO4)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO5)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO6)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO7)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO8)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_COMBO4)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_COMBO5)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_COMBO6)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_COMBO7)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_COMBO8)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);
#if 1
		this->GetDlgItem(IDC_STATIC_STEP)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC_HALF)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_CHECK2)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_CHECK3)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_CHECK4)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_CHECK5)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_CHECK6)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_CHECK7)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_CHECK8)->ShowWindow(SW_HIDE);


#endif		
	}
	boxs[0] = &m_constep1;
	boxs[1] = &m_constep2;
	boxs[2] = &m_constep3;
	boxs[3] = &m_constep4;
	boxs[4] = &m_constep5;
	boxs[5] = &m_constep6;
	boxs[6] = &m_constep7;
	boxs[7] = &m_constep8;

	m_b1 = halfs[0];
	m_b2 = halfs[1];
	m_b3 = halfs[2];
	m_b4 = halfs[3];
	m_b5 = halfs[4];
	m_b6 = halfs[5];
	m_b7 = halfs[6];
	m_b8 = halfs[7];

	stepArray[0] = 1;   
	stepArray[1] = 2;
	stepArray[2] = 3;  
	stepArray[3] = 4;   
	stepArray[4] = 5;
	stepArray[5] = 10;   
	stepArray[6] = 50;
	stepArray[7] = 100;  
	stepArray[8] = 200;   
	stepArray[9] = 400;
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < sizeof(stepArray)/sizeof(stepArray[0]); j++)
		{
			char s[20];
			itoa(stepArray[j],s,10);
            boxs[i]->AddString(s);
		}
	}
	for(    i = 0; i < 8; i++)
	{
		char s[20];
		itoa(steps[i],s,10);
		int index = boxs[i]->FindString(-1,s);
		boxs[i]->SetCurSel(index);
	}
	
	UpdateData(FALSE);
	return TRUE;
}

void ShowSet::OnPaint() 
{
	CPaintDC dc(this);
	/*
	CPen yellowPen(PS_SOLID,2,RGB(220,255,220));
	CBrush yellowBrush(RGB(220,255,220));
	dc.SelectObject(&yellowBrush);
	dc.SelectObject(&yellowPen);
    dc.Rectangle(5*dx,0*dy,6*dx,25*dy);
	*/
}


void ShowSet::ParsInit()
{
	CString str[2] = {"起始","结束"};
    GobalData* g = GobalData::getGobalData();
	
	m_conListCtrl.DeleteAllItems();
    for(int i = 0; i < 2; i++)
	{
		m_conListCtrl.InsertItem(i,"");
		m_conListCtrl.SetItemText(i,0,str[i]);
		for(int j = 1; j < 9; j++)
		{
			short a = g->showCHS[i][j - 1];
			char s[20];
			_itoa(int(a),s,10);
			m_conListCtrl.SetItemText(i,j,s);
		}
	}
}

void ShowSet::OnOK() 
{
    UpdateData();
	GobalData* g = GobalData::getGobalData();
    for(int i = 0; i < 2; i++)
	{
		for(int j = 1; j < 9; j++)
		{
			char s[20];
			m_conListCtrl.GetItemText(i,j,s,20);
			int ch = atoi(s);
	     	g->showCHS[i][j - 1] = ch;	
		}
	}

//	for(    i = 0; i < 8; i++ )//最多一个块中显示8个通道
//	{
//        if(g->showCHS[1][i] - g->showCHS[0][i] >= 8)
//		{
//			g->showCHS[1][i] = g->showCHS[0][i];
//		}
//	}

	g->setShowCHStoFile();
	AUTOSET set = g->getAutoSet();
	set.nserl_hacc = hacc ;
	set.nserl_vacc = vacc ;
	g->setAutoSet(set);

	for(    i = 0; i < 8; i++)
	{
        steps[i] = stepArray[boxs[i]->GetCurSel()];
	}

	halfs[0] = m_b1;
	halfs[1] = m_b2;
	halfs[2] = m_b3;
	halfs[3] = m_b4;
	halfs[4] = m_b5;
	halfs[5] = m_b6;
	halfs[6] = m_b7;
	halfs[7] = m_b8;

	CDialog::OnOK();
}

void ShowSet::OnDblclkListShowch(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if( Ready_Only == 1 )
	return ;

	try
	{
		LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
		GobalData* g = GobalData::getGobalData();
		int index = (pDispInfo->item).mask;
		if(index < 0)
			return;
		MParDlg dlg;
		dlg.max = 136;
		dlg.min = 1;
		dlg.index = 0;
		memcpy(dlg.data,g->showCHS[index],8*sizeof(short int));
		
		if(dlg.DoModal() == IDOK)
		{
			memcpy(g->showCHS[index],dlg.data,8*sizeof(short));
		}
		ParsInit();
		
		*pResult = 0;
	}
	catch (...) 
	{
		AfxMessageBox("inside error1");
	}
}

void ShowSet::ThrInit()
{
	m_conListTHR.DeleteAllItems();

	m_conListTHR.InsertItem(0,"");
	m_conListTHR.SetItemText(0,0,"门限");
	for(int j = 1; j < 9; j++)
	{
		short a = alertlines[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(0,j,s);
	}

	m_conListTHR.InsertItem(1,"");
	m_conListTHR.SetItemText(1,0,"滤波门限");
	for(    j = 1; j < 9; j++)
	{
		short a = alertlines2[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(1,j,s);
	}
	
/*
	m_conListTHR.InsertItem(2,"");
	m_conListTHR.SetItemText(2,0,"长度修正");
	for(    j = 1; j < 9; j++)
	{
		short a = alertlines3[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(2,j,s);
	}
*/
	m_conListTHR.InsertItem(2,"");
	m_conListTHR.SetItemText(2,0,"二阶参数");
    for(    j = 1; j < 9; j++)
	{
		short a = differ[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(2,j,s);
	}
	
	m_conListTHR.InsertItem(3,"");
	m_conListTHR.SetItemText(3,0,"二阶幅值");
	for(    j = 1; j < 9; j++)
	{
		short a = differadjust[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(3,j,s);
	}

	m_conListTHR.InsertItem(4,"");
	m_conListTHR.SetItemText(4,0,"显示标题");
    for(    j = 1; j < 9; j++)
	{
		m_conListTHR.SetItemText(4,j,titles[j-1]);
	}
	
	m_conListTHR.InsertItem(5,"");
	m_conListTHR.SetItemText(5,0,"抑制比");
    for(    j = 1; j < 9; j++)
	{
		short a = restrain[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(5,j,s);
	}
	

	
	m_conListTHR.InsertItem(6,"");
	m_conListTHR.SetItemText(6,0,"状态输出标题");
    for(    j = 1; j < 9; j++)
	{
		m_conListTHR.SetItemText(6,j,DOtitles[j-1]);
	}
	
	m_conListTHR.InsertItem(7,"");
	m_conListTHR.SetItemText(7,0,"显示块压缩比");
    for(    j = 1; j < 9; j++)
	{
		short a = showcompress[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(7,j,s);
	}

	m_conListTHR.InsertItem(8,"");
	m_conListTHR.SetItemText(8,0,"延时参数");
    for(    j = 1; j < 9; j++)
	{
		short a = timelapes[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(8,j,s);
	}
	m_conListTHR.InsertItem(9,"");
	m_conListTHR.SetItemText(9,0,"端部参数");
    for(    j = 1; j < 9; j++)
	{
		short a = alertlines3[j-1];
		char s[20];
		_itoa(int(a),s,10);
		m_conListTHR.SetItemText(9,j,s);
	}
}

void ShowSet::OnDblclkListThr(NMHDR* pNMHDR, LRESULT* pResult) 
{
if( Ready_Only == 1 )
	return ;

	try
	{
		LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
		int index = (pDispInfo->item).mask;
		if(index < 0)
			return;
		
		switch(index) 
		{
		case 0://设置门限
			{
				MParDlg dlg;
				dlg.min = -100;
				dlg.max = 100;
				dlg.index = 0;
				dlg.title="打标门限设置";
				memcpy(dlg.data,alertlines,8*sizeof(short));
				if(dlg.DoModal() == IDOK)
				{
					memcpy(alertlines,dlg.data,8*sizeof(short));
				}
			}
			break;
		case 1://设置2门限
			{
				MParDlg dlg;
				dlg.min = -100;
				dlg.max = 100;
				dlg.index = 0;
				dlg.title="滤波门限设置";
				memcpy(dlg.data,alertlines2,8*sizeof(short));
				if(dlg.DoModal() == IDOK)
				{
					memcpy(alertlines2,dlg.data,8*sizeof(short));
				}
			}
			break;

	/*	case 2://设置2门限
			{
		    	GobalData* g = GobalData::getGobalData();
	            AUTOSET set = g->getAutoSet();
	            if (set.timelapes[7]==1)
				MessageBox("第一个参数为长度修正,\n第二个参数为起始位置");
				MParDlg dlg;
				dlg.min = -1000000;
				dlg.max = 1000000;
				dlg.index = 0;
				memcpy(dlg.data,alertlines3,8*sizeof(short));
				if(dlg.DoModal() == IDOK)
				{
					memcpy(alertlines3,dlg.data,8*sizeof(short));
				}
			}
			break;
*/
		case 2://设置二阶间隔
			{
				MParDlg dlg;
				dlg.min = 1;
				dlg.max = 100;
				dlg.index = 0;
				dlg.title="二阶参数";
				memcpy(dlg.data,differ,sizeof(differ));
				if(dlg.DoModal() == IDOK)
				{
					memcpy(differ,dlg.data,sizeof(differ));
				}		
			}
			break;
		case 3://设置二阶幅值
			{
				MParDlg dlg;
				dlg.min = 0;
				dlg.max = 100;
				dlg.index = 0;
				dlg.title="二阶幅值";
				memcpy(dlg.data,differadjust,8*sizeof(short));
				if(dlg.DoModal() == IDOK)
				{
					memcpy(differadjust,dlg.data,8*sizeof(short));
				}
			}
			break;
		case 4:
			{
				CStrParDlg dlg;
				dlg.maxCharNum = 20;
				for(int i = 0; i < 8; i++)
				{
					dlg.strs[i] = titles[i];
				}
				if(dlg.DoModal() == IDOK)
				{
					for(int i = 0; i < 8; i++)
					{
						int len = (dlg.strs[i]).GetLength();
						memcpy(titles[i],(dlg.strs[i]).GetBuffer(20), len);
						titles[i][len] = '\0';
					}
					
				}
			}
			break;
		case 5:
			{
				MParDlg dlg;
				dlg.min = -100;
				dlg.max = 100;
				dlg.index = 0;
				memcpy(dlg.data,restrain,8*sizeof(short));
				if(dlg.DoModal() == IDOK)
				{
					memcpy(restrain,dlg.data,8*sizeof(short));
				}
			}
			break;
		case 6:
			{
				CStrParDlg dlg;
				dlg.maxCharNum = 20;
				for(int i = 0; i < 8; i++)
				{
					dlg.strs[i] = DOtitles[i];
				}
				if(dlg.DoModal() == IDOK)
				{
					for(int i = 0; i < 8; i++)
					{
						int len = (dlg.strs[i]).GetLength();
						memcpy(DOtitles[i],(dlg.strs[i]).GetBuffer(20), len);
						DOtitles[i][len] = '\0';
					}
					
				}
			}
			break;
		case 7:
			{
				MParDlg dlg;
				dlg.min = 1;
				dlg.max = 1000;
				dlg.index = 0;
				dlg.title="显示块压缩比";
				memcpy(dlg.data,showcompress,sizeof(showcompress));
				if(dlg.DoModal() == IDOK)
				{
					memcpy(showcompress,dlg.data,sizeof(showcompress));
				}		
			}
			break;
		case 8:
			{  
				GobalData* g = GobalData::getGobalData();
			//	AUTOSET set = g->getAutoSet();
				MParDlg dlg;
				
				dlg.min = 0;
				dlg.max = 10000;
				dlg.index = 0;
				memcpy(dlg.data,timelapes,8*sizeof(short));
				dlg.title="块延时参数";
				if(dlg.DoModal() == IDOK)
				{
					memcpy(timelapes,dlg.data,8*sizeof(short));
				}
			}
			break;
		case 9:
			{  
				GobalData* g = GobalData::getGobalData();
	           	//	AUTOSET set = g->getAutoSet();
				MParDlg dlg;

				//AfxMessageBox("第一个参数横向开始延时，第二个参数横向延时结束点数.\n第三个参数纵向开始延时，第四个参数纵向结束延时.\n第五个参数纵向后4通道延时开始，第六个参数纵向前4通道延时结束.");
				dlg.min = 0;
				dlg.max = 10000;
				dlg.index = 0;
				memcpy(dlg.data,alertlines3,8*sizeof(short));
				if(dlg.DoModal() == IDOK)
				{
					memcpy(alertlines3,dlg.data,8*sizeof(short));
				}
			}
			break;	
		}
			ThrInit();
			*pResult = 0;
		
	}
	catch (...) 
	{
		AfxMessageBox("inside error2");
	}
}

void ShowSet::OnButtonReset() 
{
    for(int i = 0; i < 8; i++)
	{
         boxs[i]->SetCurSel(0);
	}
	memset(alertlines,0,8*sizeof(alertlines[0]));
	memset(alertlines2,0,8*sizeof(alertlines2[0]));
	memset(alertlines3,0,8*sizeof(alertlines2[0]));
	memset(restrain,0,8*sizeof(restrain[0]));
	ThrInit();
}

void ShowSet::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	char s[20];
	itoa(stepArray[boxs[0]->GetCurSel()],s,10);
	int index = boxs[0]->FindString(-1,s);
    for(int i = 0; i < 8; i++)
	{	
		boxs[i]->SetCurSel(index);
	}
	UpdateData(FALSE);
}

void ShowSet::OnSelchangeComboHacc() 
{
	// TODO: Add your control notification handler code here
	hacc = m_comb_hacc.GetCurSel();
	
}

void ShowSet::OnSelendcancelComboVacc() 
{
	// TODO: Add your control notification handler code here
	vacc = m_comb_vacc.GetCurSel();
	
}
