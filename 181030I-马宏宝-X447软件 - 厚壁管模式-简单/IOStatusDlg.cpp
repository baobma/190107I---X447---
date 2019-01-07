// IOStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "IOStatusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "GobalData.h"
#include "TestSampleControl.h"
/////////////////////////////////////////////////////////////////////////////
// CIOStatusDlg dialog


CIOStatusDlg::CIOStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIOStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIOStatusDlg)
	m_bCheckPlus = FALSE;
	//}}AFX_DATA_INIT
	if(Create(CIOStatusDlg::IDD, pParent))
		ShowWindow(SW_SHOW);
	else
		AfxMessageBox("状态监控启动失败");
}


void CIOStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIOStatusDlg)
	DDX_Control(pDX, IDC_STATIC8, m_pic8);
	DDX_Control(pDX, IDC_STATIC7, m_pic7);
	DDX_Control(pDX, IDC_STATIC6, m_pic6);
	DDX_Control(pDX, IDC_STATIC5, m_pic5);
	DDX_Control(pDX, IDC_STATIC4, m_pic4);
	DDX_Control(pDX, IDC_STATIC3, m_pic3);
	DDX_Control(pDX, IDC_STATIC2, m_pic2);
	DDX_Control(pDX, IDC_STATIC1, m_pic1);
	DDX_Check(pDX, IDC_CHECK_PLUS, m_bCheckPlus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIOStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CIOStatusDlg)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIOStatusDlg message handlers

void CIOStatusDlg::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CIOStatusDlg::OnClose() 
{	
	CDialog::OnClose();
}

BOOL CIOStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GobalData* g = GobalData::getGobalData();
    AUTOSET set = g->getAutoSet();
	pics[0] = &m_pic1;
	pics[1] = &m_pic2;
	pics[2] = &m_pic3;
	pics[3] = &m_pic4;
	pics[4] = &m_pic5;
	pics[5] = &m_pic6;
	pics[6] = &m_pic7;
	pics[7] = &m_pic8;

	int pictitles[] = {
		IDC_STATIC_DI1,IDC_STATIC_DI2,IDC_STATIC_DI3,IDC_STATIC_DI4,
		IDC_STATIC_DI5,IDC_STATIC_DI6,IDC_STATIC_DI7,IDC_STATIC_DI8,
	};
	int buttontitles[] = {
		IDC_BUTTON1,IDC_BUTTON2,IDC_BUTTON3,IDC_BUTTON4,
		IDC_BUTTON5,IDC_BUTTON6,IDC_BUTTON7,IDC_BUTTON8,
	};
	for(int i = 0; i < 8; i++)
	{
//        GetDlgItem(pictitles[i])->SetWindowText(set.DItitles[i]);
		GetDlgItem(buttontitles[i])->SetWindowText(set.DOtitles[i]);
	}
	/*
	 *	图象载入
	 */
	VERIFY(iconClose.LoadBitmap(IDB_BITMAP_CLOSE));
	VERIFY(iconOpen.LoadBitmap(IDB_BITMAP_OPEN));

	setStatus(0);             //全灯灭设置
	SetTimer(1,500,NULL);     //启动监控计时器
	return TRUE;
}

/*
 *	监控状态设置 s为8位char,每一位代表一个监控灯  1为开 0为灭
 */
void CIOStatusDlg::setStatus(char s)
{
    for(int i = 0; i < 8; i++)
	{
        if( (s&char(i)) == 0)
		    pics[i]->SetBitmap(iconClose);
		else
		    pics[i]->SetBitmap(iconOpen);
	}
}

/*
 *	状态监控计时器
 */
void CIOStatusDlg::OnTimer(UINT nIDEvent) 
{
//	char r = (TestSampleControl::cardPtr)->GetDigitalInputByNet();  //读取采集卡数字口状态
	BYTE r = (TestSampleControl::cardPtr)->GetDigitalInput();  
	BYTE r1 = (TestSampleControl::cardPtr)->GetDigitalInput1();  
	char k = 1;
	/*
	 *	根据数字口状态设置监控灯开灭
	 */

    for(int i  = 0; i < 6; i++)
	{
		if( (k&r) == 0 )
		{
			pics[i]->SetBitmap(iconOpen);
		}
		else
		{
            		pics[i]->SetBitmap(iconClose);
		}
		k *= 2;
		//
		if((r1&16)==0)
			{
				pics[6]->SetBitmap(iconOpen);
			}
		else{
				pics[6]->SetBitmap(iconClose);
			}
		if((r1&32)==0)
			{
				pics[7]->SetBitmap(iconOpen);
			}
		else{
				pics[7]->SetBitmap(iconClose);
			}
	}
//	m_bCheckPlus	
//	(TestSampleControl::cardPtr)->SendDigitalOuput(1,TRUE);
	CDialog::OnTimer(nIDEvent);
}
/*
 *	点击输出按钮
 */
void CIOStatusDlg::OnButton1() 
{
	UpdateData();
	(TestSampleControl::cardPtr)->SendDigitalOuputByNet(1,!m_bCheckPlus);  //采集卡数字口输出
//	(TestSampleControl::cardPtr)->SendDigitalOuput(1,TRUE);
//	(TestSampleControl::cardPtr)->SendDigitalOuput(16,!m_bCheckPlus);
//	(TestSampleControl::cardPtr)->SendDigitalOuput(32,!m_bCheckPlus);
}

void CIOStatusDlg::OnButton2() 
{
	UpdateData();
	(TestSampleControl::cardPtr)->SendDigitalOuputByNet(2,!m_bCheckPlus);
//	(TestSampleControl::cardPtr)->SendDigitalOuput(2,TRUE);
}

void CIOStatusDlg::OnButton3() 
{
	UpdateData();
	(TestSampleControl::cardPtr)->SendDigitalOuputByNet(4,!m_bCheckPlus);
}

void CIOStatusDlg::OnButton4() 
{
	UpdateData();
//	(TestSampleControl::cardPtr)->SendDigitalOuput(8,!m_bCheckPlus);
	(TestSampleControl::cardPtr)->SendDigitalOuputByNet(8,!m_bCheckPlus);
}

void CIOStatusDlg::OnButton5() 
{
	UpdateData();
	(TestSampleControl::cardPtr)->SendDigitalOuput(16,!m_bCheckPlus); // no5
}

void CIOStatusDlg::OnButton6() 
{
	UpdateData();
	(TestSampleControl::cardPtr)->SendDigitalOuput(32,!m_bCheckPlus);
}

void CIOStatusDlg::OnButton7() 
{
	UpdateData();
	(TestSampleControl::cardPtr)->SendDigitalOuput2(16,!m_bCheckPlus);
}

void CIOStatusDlg::OnButton8() 
{
	UpdateData();
	(TestSampleControl::cardPtr)->SendDigitalOuput2(32,!m_bCheckPlus);
}

/*
 *	停止输出
 */
void CIOStatusDlg::OnButtonStop() 
{
//	(TestSampleControl::cardPtr)->SendDigitalOuputByNet(char(0x10),TRUE);
	(TestSampleControl::cardPtr)->SendDigitalOuput(0,TRUE);
}

/*
 *	关闭对话框
 */
void CIOStatusDlg::OnCancel() 
{
	CDialog::OnCancel();
	delete this;
	GobalData* g = GobalData::getGobalData();
	g->IoStatusDlg = NULL;
}
