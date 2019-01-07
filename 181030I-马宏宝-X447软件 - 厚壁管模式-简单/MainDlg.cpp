// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "MainDlg.h"
#include "ShowSet.h"
#include "TestFuc.h"
#include "GobalData.h"
#include "TestSampleControl.h"
#include "ARDSET.h"
#include "PARSET.h"
#include "DataSetDlg.h"
#include "hooseFileDlg.h"
#include "DataSaveFactory.h"
#include "SimpleDataSave.h"
#include "IOStatusDlg.h"
#include "MsgDlg.h"
#include "reportDlg.h"
#include "PrintReportDlg.h"

#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib") 
 
extern "C" {
	
#include "jpeglib.h"
	
#include "jmorecfg.h"
	
#include "jconfig.h"
	
}
#define WM_SampleMsg WM_USER+101

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BOOL addOrDel = FALSE;
#ifdef AddYcord
extern BOOL REN_DUANBU ; 
#endif
//DWORD calculatespeed1=0;
//DWORD calculatespeed2=0;
//DWORD calculatespeed3=0;
//BOOL  firstcalculate=FALSE;
BOOL showLengthRule = FALSE;
static bool SaveBmptoFile = FALSE;
static bool m_bSaveToFile = FALSE;
static bool SaveBmptoFile1 = FALSE;
/////////////////////////////////////////////////////////////////////////////
// MainDlg dialog


//extern  nummax;
//extern  nummax1;
MainDlg::MainDlg(CWnd* pParent /*=NU LL*/)
	: CDialog(MainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MainDlg)
	m_iCurrentNum = 0;
	m_strPlyValue = _T("");
	m_strPosition = _T("");
	//}}AFX_DATA_INIT
}
void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MainDlg)
	DDX_Control(pDX, IDC_STATIC_LEN, m_staticLEN);
	DDX_Control(pDX, IDC_STATIC_MINPLY, m_staticMinPly);
	DDX_Control(pDX, IDC_EDIT_MINPLY, m_conMinPly);
	DDX_Control(pDX, IDC_STATIC_POSITION, m_staticPosition);
	DDX_Control(pDX, IDC_EDIT_POSITION, m_conPosition);
	DDX_Control(pDX, IDC_STATIC9, m_conStatic9);
	DDX_Control(pDX, IDC_STATIC_CURRENTPLY, m_StaticPly);
	DDX_Control(pDX, IDC_EDIT_CURRENTPLY, m_conPlyValue);
	DDX_Control(pDX, IDC_BUTTON_SPRENT, m_conPrint);
	DDX_Control(pDX, IDC_STATIC8, m_conStatic8);
	DDX_Control(pDX, IDC_STATIC7, m_conStatic7);
	DDX_Control(pDX, IDC_STATIC6, m_conStatic6);
	DDX_Control(pDX, IDC_STATIC5, m_conStatic5);
	DDX_Control(pDX, IDC_STATIC4, m_conStatic4);
	DDX_Control(pDX, IDC_STATIC3, m_conStatic3);
	DDX_Control(pDX, IDC_STATIC2, m_conStatic2);
	DDX_Control(pDX, IDC_STATIC1, m_conStatic1);
	DDX_Control(pDX, IDC_BUTTON_IOSTATUS, m_conBiostatus);
	DDX_Control(pDX, IDC_LIST_MSG, m_conEmsg);
	DDX_Control(pDX, IDC_STATIC_T8, m_staticTitle8);
	DDX_Control(pDX, IDC_STATIC_T7, m_staticTitle7);
	DDX_Control(pDX, IDC_STATIC_T6, m_staticTitle6);
	DDX_Control(pDX, IDC_STATIC_T5, m_staticTitle5);
	DDX_Control(pDX, IDC_STATIC_T4, m_staticTitle4);
	DDX_Control(pDX, IDC_STATIC_T3, m_staticTitle3);
	DDX_Control(pDX, IDC_STATIC_T2, m_staticTitle2);
	DDX_Control(pDX, IDC_STATIC_T1, m_staticTitle1);
	DDX_Control(pDX, IDC_BUTTON_waven, m_conBwaven);
	DDX_Control(pDX, IDC_BUTTON_wavepp, m_conBwavepp);
	DDX_Control(pDX, IDC_BUTTON_wavep, m_conBwavep);
	DDX_Control(pDX, IDC_BUTTON_wavenn, m_conBwavenn);
	DDX_Control(pDX, IDC_EDIT_CURRENTNUM, m_conEcurrentnum);
	DDX_Control(pDX, IDC_BUTTON_allpp, m_conBallpp);
	DDX_Control(pDX, IDC_BUTTON_allp, m_conBallp);
	DDX_Control(pDX, IDC_BUTTON_allnn, m_conBallnn);
	DDX_Control(pDX, IDC_BUTTON_alln, m_conBalln);
	DDX_Control(pDX, IDC_STATIC_CURRENTNUM, m_conSgonum);
	DDX_Control(pDX, IDC_BUTTON_GONUM, m_conBgonum);
	DDX_Control(pDX, IDC_BUTTON_DATASAVESET, m_conBdataset);
	DDX_Control(pDX, IDC_BUTTON_ANALYSIS, m_conBanalysis);
	DDX_Control(pDX, IDC_BUTTON_RESHOW, m_conBreshow);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_conBhistorydata);
	DDX_Control(pDX, IDC_PROGRESS, m_conProgress);
	DDX_Control(pDX, IDC_EDIT_HELP, m_conEhelp);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_conBstop);
	DDX_Control(pDX, IDC_BUTTON_START, m_conBstart);
	DDX_Control(pDX, IDC_BUTTON_SHOWSET, m_conBshowset);
	DDX_Control(pDX, IDC_BUTTON_REPORT, m_conBreport);
	DDX_Control(pDX, IDC_BUTTON_DEMOCRATE, m_conBdemocrate);
	DDX_Control(pDX, IDC_BUTTON_PARSET, m_conBparset);
	DDX_Control(pDX, IDC_BUTTON_DATABASE, m_conBdatabase);
	DDX_Control(pDX, IDC_BUTTON_CARDSET, m_conBcardset);
	DDX_Text(pDX, IDC_EDIT_CURRENTNUM, m_iCurrentNum);
	DDX_Text(pDX, IDC_EDIT_CURRENTPLY, m_strPlyValue);
	DDX_Text(pDX, IDC_EDIT_POSITION, m_strPosition);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MainDlg, CDialog)
	//{{AFX_MSG_MAP(MainDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SHOWSET, OnButtonShowset)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CARDSET, OnButtonCardset)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_DEMOCRATE, OnButtonDemocrate)
	ON_BN_CLICKED(IDC_BUTTON_PARSET, OnButtonParset)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENUITEM_FIRSTC, OnMenuitemFirstc)
	ON_COMMAND(ID_MENUITEM_NEXTC, OnMenuitemNextc)
	ON_COMMAND(ID_MENUITEM_PREC, OnMenuitemPrec)
	ON_BN_CLICKED(IDC_BUTTON_DATASAVESET, OnButtonDatasaveset)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_1p, OnBUTTON1p)
	ON_BN_CLICKED(IDC_BUTTON_1n, OnBUTTON1n)
	ON_BN_CLICKED(IDC_BUTTON_2p, OnBUTTON2p)
	ON_BN_CLICKED(IDC_BUTTON_2n, OnBUTTON2n)
	ON_BN_CLICKED(IDC_BUTTON_3p, OnBUTTON3p)
	ON_BN_CLICKED(IDC_BUTTON_3n, OnBUTTON3n)
	ON_BN_CLICKED(IDC_BUTTON_4p, OnBUTTON4p)
	ON_BN_CLICKED(IDC_BUTTON_4n, OnBUTTON4n)
	ON_BN_CLICKED(IDC_BUTTON_5p, OnBUTTON5p)
	ON_BN_CLICKED(IDC_BUTTON_5n, OnBUTTON5n)
	ON_BN_CLICKED(IDC_BUTTON_6p, OnBUTTON6p)
	ON_BN_CLICKED(IDC_BUTTON_6n, OnBUTTON6n)
	ON_BN_CLICKED(IDC_BUTTON_7p, OnBUTTON7p)
	ON_BN_CLICKED(IDC_BUTTON_7n, OnBUTTON7n)
	ON_BN_CLICKED(IDC_BUTTON_8p, OnBUTTON8p)
	ON_BN_CLICKED(IDC_BUTTON_8n, OnBUTTON8n)
	ON_BN_CLICKED(IDC_BUTTON_pp1, OnBUTTONpp1)
	ON_BN_CLICKED(IDC_BUTTON_pp2, OnBUTTONpp2)
	ON_BN_CLICKED(IDC_BUTTON_pp3, OnBUTTONpp3)
	ON_BN_CLICKED(IDC_BUTTON_pp4, OnBUTTONpp4)
	ON_BN_CLICKED(IDC_BUTTON_pp5, OnBUTTONpp5)
	ON_BN_CLICKED(IDC_BUTTON_pp6, OnBUTTONpp6)
	ON_BN_CLICKED(IDC_BUTTON_pp7, OnBUTTONpp7)
	ON_BN_CLICKED(IDC_BUTTON_pp8, OnBUTTONpp8)
	ON_BN_CLICKED(IDC_BUTTON_allpp, OnBUTTONallpp)
	ON_BN_CLICKED(IDC_BUTTON_allp, OnBUTTONallp)
	ON_BN_CLICKED(IDC_BUTTON_GONUM, OnButtonGonum)
	ON_BN_CLICKED(IDC_BUTTON_alln, OnBUTTONalln)
	ON_BN_CLICKED(IDC_BUTTON_allnn, OnBUTTONallnn)
	ON_BN_CLICKED(IDC_BUTTON_RESHOW, OnButtonReshow)
	ON_BN_CLICKED(IDC_BUTTON_wavepp, OnBUTTONwavepp)
	ON_BN_CLICKED(IDC_BUTTON_wavep, OnBUTTONwavep)
	ON_BN_CLICKED(IDC_BUTTON_waven, OnBUTTONwaven)
	ON_BN_CLICKED(IDC_BUTTON_wavenn, OnBUTTONwavenn)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_nn1, OnBUTTONnn1)
	ON_BN_CLICKED(IDC_BUTTON_nn2, OnBUTTONnn2)
	ON_BN_CLICKED(IDC_BUTTON_nn3, OnBUTTONnn3)
	ON_BN_CLICKED(IDC_BUTTON_nn4, OnBUTTONnn4)
	ON_BN_CLICKED(IDC_BUTTON_nn5, OnBUTTONnn5)
	ON_BN_CLICKED(IDC_BUTTON_nn6, OnBUTTONnn6)
	ON_BN_CLICKED(IDC_BUTTON_nn7, OnBUTTONnn7)
	ON_BN_CLICKED(IDC_BUTTON_nn8, OnBUTTONnn8)
	ON_COMMAND(ID_COMBINE, OnCombine)
	ON_COMMAND(ID_SIMPLE, OnSimple)
	ON_BN_CLICKED(IDC_BUTTON_ANALYSIS, OnButtonAnalysis)
	ON_COMMAND(IDC_FAULT, OnFault)
	ON_BN_CLICKED(IDC_BUTTON_IOSTATUS, OnButtonIostatus)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnButtonReport)
	ON_BN_CLICKED(IDC_BUTTON_DATABASE, OnButtonDatabase)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON_SPRENT, OnButtonSprent)
	ON_COMMAND(ID_DIFFER, OnDiffer)
	ON_COMMAND(ID_PHASE, OnPhase)
	ON_COMMAND(ID_PLY, OnPly)
	ON_COMMAND(ID_DIFFERENCE, OnDifference)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_ThickPipe, OnThickPipe)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MyNotify,OnMyNotify)
	ON_MESSAGE(WM_SampleMsg,SampleMsg)
	ON_MESSAGE(WM_NEW_MSG,DlgNewMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MainDlg message handlers

BOOL MainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    	ReadlvboToFile("par\\automaneofnew.par");
	m_bIsCapturing = FALSE;
	ShowWindow(SW_SHOWMAXIMIZED);
	RECT Client_Size;
	GetClientRect(&Client_Size);	
	dx = Client_Size.right/20;
	dy = Client_Size.bottom/24;

	dyanniu = Client_Size.bottom/12;

	StaticShow[0] = &m_conStatic1;
	StaticShow[1] = &m_conStatic2;
	StaticShow[2] = &m_conStatic3;
	StaticShow[3] = &m_conStatic4;
	StaticShow[4] = &m_conStatic5;
	StaticShow[5] = &m_conStatic6;
	StaticShow[6] = &m_conStatic7;
	StaticShow[7] = &m_conStatic8;

	GobalData* g = GobalData::getGobalData();
    g->setShowNum(WaveShowNum_EIGHT);
	DlgShowInit();
	myInit();   
//	G_m_menxianzhi= m_menxianzhi;
//	SetTimer(1,300,NULL);     //启动监控计时器
	//单位毫秒执行次，
//	(TestSampleControl::cardPtr)->workwithPlc();
	 CRect rt;
	this->GetClientRect(&rt);
	this->SetWindowPos(this,rt.left,rt.top,rt.right,rt.bottom,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	this->ShowWindow(SW_SHOWMAXIMIZED);
	return TRUE;
}

void MainDlg::DlgShowInit()
{
	pnButtons[0][0] = IDC_BUTTON_1p;    pnButtons[1][0] = IDC_BUTTON_1n;
	pnButtons[0][1] = IDC_BUTTON_2p;    pnButtons[1][1] = IDC_BUTTON_2n;
	pnButtons[0][2] = IDC_BUTTON_3p;    pnButtons[1][2] = IDC_BUTTON_3n;
	pnButtons[0][3] = IDC_BUTTON_4p;    pnButtons[1][3] = IDC_BUTTON_4n;
	pnButtons[0][4] = IDC_BUTTON_5p;    pnButtons[1][4] = IDC_BUTTON_5n;
	pnButtons[0][5] = IDC_BUTTON_6p;    pnButtons[1][5] = IDC_BUTTON_6n;
	pnButtons[0][6] = IDC_BUTTON_7p;    pnButtons[1][6] = IDC_BUTTON_7n;
	pnButtons[0][7] = IDC_BUTTON_8p;    pnButtons[1][7] = IDC_BUTTON_8n;

	pnButtons[2][0] = IDC_BUTTON_pp1;   pnButtons[3][0] = IDC_BUTTON_nn1;
	pnButtons[2][1] = IDC_BUTTON_pp2;   pnButtons[3][1] = IDC_BUTTON_nn2;
	pnButtons[2][2] = IDC_BUTTON_pp3;   pnButtons[3][2] = IDC_BUTTON_nn3;
	pnButtons[2][3] = IDC_BUTTON_pp4;   pnButtons[3][3] = IDC_BUTTON_nn4;
	pnButtons[2][4] = IDC_BUTTON_pp5;   pnButtons[3][4] = IDC_BUTTON_nn5;
	pnButtons[2][5] = IDC_BUTTON_pp6;   pnButtons[3][5] = IDC_BUTTON_nn6;
	pnButtons[2][6] = IDC_BUTTON_pp7;   pnButtons[3][6] = IDC_BUTTON_nn7;
	pnButtons[2][7] = IDC_BUTTON_pp8;   pnButtons[3][7] = IDC_BUTTON_nn8;

	DlgAllButton[0] = IDC_BUTTON_allpp;
	DlgAllButton[1] = IDC_BUTTON_allp;
	DlgAllButton[2] = IDC_BUTTON_allnn;
	DlgAllButton[3] = IDC_BUTTON_alln;
	DlgAllButton[4] = IDC_BUTTON_GONUM;

	AllWaveButton[0] = IDC_BUTTON_wavepp;
	AllWaveButton[1] = IDC_BUTTON_wavep;
	AllWaveButton[2] = IDC_BUTTON_waven;
	AllWaveButton[3] = IDC_BUTTON_wavenn;

    	titles[0] = &m_staticTitle1;
	titles[1] = &m_staticTitle2;
	titles[2] = &m_staticTitle3;
	titles[3] = &m_staticTitle4;
	titles[4] = &m_staticTitle5;
	titles[5] = &m_staticTitle6;
	titles[6] = &m_staticTitle7;
	titles[7] = &m_staticTitle8;
	

	int ix = 0; int iy = 0; int ex = 3*dx/2; int ey = dyanniu; 
	m_conBstart.MoveWindow(ix,iy,ex,ey+1);      iy += ey+1;
	m_conBstop.MoveWindow(ix,iy,ex,ey+1);       iy += ey+1;
	m_conBdemocrate.MoveWindow(ix,iy,ex,ey+1);  iy += ey+1;
	m_conBparset.MoveWindow(ix,iy,ex,ey+1);     iy += ey+1;
	m_conBcardset.MoveWindow(ix,iy,ex,ey+1);    iy += ey+1;
	m_conBshowset.MoveWindow(ix,iy,ex,ey+1);    iy += ey+1;
	m_conBhistorydata.MoveWindow(ix,iy,ex,ey+1); iy += ey+1;
    	m_conBanalysis.MoveWindow(ix,iy,ex,ey+1);    iy += ey+1;
	m_conBreshow.MoveWindow(ix,iy,ex,ey+1);      iy += ey+1;
	m_conBdataset.MoveWindow(ix,iy,ex,ey+1);     iy += ey+1;
	m_conBiostatus.MoveWindow(ix,iy,ex,ey+1);    iy += ey+1;
    	m_conPrint.MoveWindow(ix,iy,ex,ey+1);        iy += ey+1;
//	m_conBreport.MoveWindow(ix,iy,ex,ey+1);     
//	m_conBdatabase.MoveWindow(ix,iy,ex,ey);   iy += ey;
	m_staticLEN.MoveWindow(ex,iy-ey,2*ex+40,ey);    ix += ex+40; //"长度0.0m"
	
	ix = 7*dx; iy = 20*dy+5; ex = 5*dx; ey = 2*dy;
	m_conEhelp.MoveWindow(ix,iy,ex+80,ey);
	
	ix = 18*dx; iy = 23*dy; ex = 2*dx; ey = 1*dy;
	m_conProgress.MoveWindow(ix,iy,ex,ey);
	
	ix = 14*dx; iy = 22*dy+5; ex = 2*dx; ey = 2*dy;
	m_conEmsg.MoveWindow(ix,iy,3*ex,2*dy);
	
	ix = 2*dx; iy = 22*dy+5; ex = dx; ey = dy;
	m_conBallpp.MoveWindow(ix,iy,ex,ey);                    ix += ex;
	m_conBallp.MoveWindow(ix,iy,ex,ey);                   ix += ex;   
	m_conEcurrentnum.MoveWindow(ix,iy+ey/4,ex,ey/2);     ix += ex;
	m_conSgonum.MoveWindow(ix,iy+ey/4,ex*2+100,ey/2);   ix += ex*2;
	m_conBgonum.MoveWindow(ix+100,iy,ex,ey);                   ix += ex;
	m_conBalln.MoveWindow(ix+100,iy,ex,ey);                   ix += ex;
	m_conBallnn.MoveWindow(ix+100,iy,ex,ey);                    ix += ex;
	
	
	ix = 2*dx; iy = 23*dy+5; ex = dx; ey = dy;
	m_conBwavepp.MoveWindow(ix,iy,ex,ey);      ix += ex;
	m_conBwavep.MoveWindow(ix,iy,ex,ey);       ix += ex;
	m_conBwaven.MoveWindow(ix,iy,ex,ey);       ix += ex;
	m_conBwavenn.MoveWindow(ix,iy,ex,ey);      ix += ex;

	m_StaticPly.MoveWindow(10*dx+2*dx/3,23*dy,dx+10,ey/2);
	m_conPlyValue.MoveWindow(11*dx+dx+10,23*dy,dx,ey/2);
	m_staticPosition.MoveWindow(10*dx+2*dx/3,22*dy+dy/2,dx+10,ey/2);
	m_staticLEN.MoveWindow(10*dx+2*dx/3,22*dy+dy/2,2*dx+10,ey/2);
	m_conPosition.MoveWindow(11*dx+dx+10,22*dy+dy/2,dx,ey/2);
	m_staticMinPly.MoveWindow(10*dx+2*dx/3,23*dy+dy/2,dx+40,ey/2);
	m_conMinPly.MoveWindow(11*dx+dx+10,23*dy+dy/2,dx,ey/2);

	m_conStatic9.MoveWindow(19*dx,4*dy,dx,ey*2);

	CRect r(19*dx,4*dy,10*dx,6*dy);
	statisticrRect = r;

	ix = 3*dx + dx/2; iy = 2*dy; ex = 6*dx; ey = 3*dy + dy/2;

	GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	for(int i = 0; i < 8; i++)
	    {
			waveshow[i] = new CWaveShow(StaticShow[i],100000,4096);
			waveshow[i]->setStep(set.steps[i]);
			waveshow[i]->setHalfShow(set.halfs[i]);
			waveshow[i]->setAlertLine(set.alertline[i]);
			waveshow[i]->setAlertLine2(set.alertline2[i]);
			waveshow[i]->setAlertLine3(set.alertline3[i]);
			waveshow[i]->setRestrainY(set.restrain[i]);
			waveshow[i]->setWaveStyle(set.showstyle[i]);
			waveshow[i]->setShowCompress(set.showcompress[i]);
			waveshow[i]->setTimeLapes(set.timelapes[i]);

			waveshow[i]->setDiffer(set.differ[i]);
			waveshow[i]->setDifferAdjust(set.differadjust[i]);
	    }
	statisticShow = new CWaveShow(&m_conStatic9,10000,4096);
	g->setShowNum(set.showNum);
	m_conBreport.MoveWindow(16*dx,0,19*dx+dx*2/3,2);
#ifdef REN_ZHENG	
//	m_conBreport.MoveWindow(19*dx,10*dy/2,19*dx+dx*2/3,17*dy+dy/4-3);	
	m_conBreport.EnableWindow(FALSE);
#endif
	ChangeShowBlock();
}

void MainDlg::OnPaint() 
{
	CPaintDC dc(this); 
	GobalData* g = GobalData::getGobalData();
    try
	{
		CPen Pen0(PS_SOLID,10,RGB(160,82,45));  //综红
		CPen Pen1(PS_SOLID,10,RGB(255,97,0));   //橙
		CPen Pen2(PS_SOLID,10,RGB(255,200,0));  //黄
		CPen Pen3(PS_SOLID,10,RGB(0,255,0));	//绿
		CPen Pen4(PS_SOLID,10,RGB(8,46,84));    //靛青 
		CPen Pen5(PS_SOLID,10,RGB(0,0,255));    //蓝
		CPen Pen6(PS_SOLID,10,RGB(160,32,240)); //紫 
		CPen Pen7(PS_SOLID,10,RGB(135,206,235));//天蓝

		CBrush Brush1(RGB(160,82,45));
		CBrush Brush2(RGB(255,97,0));
		CBrush Brush3(RGB(255,200,0));
		CBrush Brush4(RGB(0,255,0));
		CBrush Brush5(RGB(8,46,84));
		CBrush Brush6(RGB(0,0,255));
		CBrush Brush7(RGB(160,32,240));
		CBrush Brush8(RGB(135,206,235));
		
		CPen* pens[8] = 
		{
			&Pen0,&Pen1 ,&Pen2,&Pen3,
			&Pen4,&Pen5 ,&Pen6,&Pen7
		};
		CBrush* brushs[8] = 
		{
			&Brush1,&Brush2,&Brush3,&Brush4,
			&Brush5,&Brush6,&Brush7,&Brush8,
		};
		CGdiObject* systemPen   = NULL;
		CGdiObject* systemBrush = NULL;
		CGdiObject* org         = NULL;

		for (int k = 0; k < 8;k++)
		{
			systemPen = dc.SelectObject(brushs[k]);
			systemBrush = dc.SelectObject(pens[k]);
			dc.Rectangle(19*dx+dx/3,(k+2)*dy/2,19*dx+dx*2/3,(k+2)*dy/2+dy/8);

			org = dc.SelectObject(systemPen);
			org->DeleteObject();
			org = dc.SelectObject(systemBrush);
			org->DeleteObject();
		}
		
		int b = (g->getUsb8221Par()).block;
		for(int i = 0; i <  g->getShowNum(); i++)
		{
			if(waveshow[i] != NULL)
			{
				CRect rect;
				CWnd* pWnd = waveshow[i]->getWnd();
				pWnd->GetClientRect(&rect);
				CDC* pDC = pWnd->GetDC();
								
				CBitmap* pOldBmp = NULL;
				memDC.CreateCompatibleDC(NULL);
				memBitmap.CreateCompatibleBitmap(pDC,rect.right, rect.bottom);
				pOldBmp = memDC.SelectObject(&memBitmap);
			
				switch(waveshow[i]->getWaveShowStyle())
				{
				case WaveShowStyle_SimpleShow:
					{
						waveshow[i]->DrawBackEx(&memDC,FALSE);
						waveshow[i]->DrawWave_blockEx(&memDC,g->showCHS[0][i]-1,g->showCHS[1][i]-1,b,false,dataOpenMode);
					}
					break;	
				case WaveShowStyle_Difference://热凹
					{
						waveshow[i]->DrawBackEx(&memDC,TRUE);
						waveshow[i]->DrawDifference(&memDC,g->showCHS[0][i]-1,g->showCHS[1][i]-1,b,dataOpenMode);
					}
					break;
				case WaveShowStyle_Combine:
					{
						waveshow[i]->DrawBackEx(&memDC,TRUE);
						waveshow[i]->DrawWave_combineEx(&memDC,g->showCHS[0][i]-1,g->showCHS[1][i]-1,b,dataOpenMode);
					}
					break;
				case WaveShowStyle_Fault:
					{
						waveshow[i]->DrawWaveFaultBackEx(&memDC);
						waveshow[i]->DrawWave_blockEx(&memDC,g->showCHS[0][i]-1,g->showCHS[1][i]-1,b,true,dataOpenMode);
					}
					break;
				case WaveShowStyle_Differ:
					{
						waveshow[i]->DrawBackEx(&memDC,FALSE);
						waveshow[i]->DrawDifferWave(&memDC,g->showCHS[0][i]-1,g->showCHS[1][i]-1,b,dataOpenMode);
					}
					break;
				case WaveShowStyle_Phase:
					{
						waveshow[i]->DrawBackEx(&memDC,TRUE);
						waveshow[i]->DrawWavePhase(&memDC,g->showCHS[0][i]-1,g->showCHS[1][i]-1,b);
					}
					break;
				case WaveShowStyle_Ply:
					{
						waveshow[i]->DrawBackEx(&memDC,FALSE);
						waveshow[i]->DrawPly(&memDC,g->showCHS[0][i]-1,g->showCHS[1][i]-1,b);
					}
					break;
		
				}
				
//				statisticShow->DrawBackEx(&memDC,TRUE);
//				pDC->BitBlt(0,0,rect.right,rect.bottom,&memDC,0,0,SRCCOPY);
				pDC->StretchBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,rect.right-rect.left,rect.bottom-rect.top,SRCCOPY);
				memDC.DeleteDC();
				memBitmap.DeleteObject();
                		pWnd->ReleaseDC(pDC);
			}
		}
    }
	catch (CException e) 
	{
		AfxMessageBox("波形显示异常");
		return;
	}	
		if( SaveBmptoFile  == TRUE )
			{
				SaveBmptoFile1 = TRUE;
				SetTimer(1,500,NULL);     //启动监控计时器
			}
}

/*
 *	8221采集卡信号获取触发
 */
void MainDlg::OnMyNotify(WPARAM wParam, LPARAM lParam)
{
	GobalData* g = GobalData::getGobalData();
	int gotblock= 0;
	//CString msg;
	//msg.Format("Msg %d,%d",wParam,lParam);

	if(g->getStatus() == Status_START || g->getStatus() == Status_DEMORATE )
		;
	else
		return;
	
//	if(g->getStatus() == Status_START && autoControl == FALSE )
//		return;
	try
	{
		RbhUsb20* usbcard = (RbhUsb20*)TestSampleControl::cardPtr;

	//	int	NumFill = QueryBuf_1();  //填充满的缓冲区个数
	//	if( NumFill > 10 )
	//		AfxMessageBox("data not used");
	//	for (int i=0;i<NumFill;i++)//表明本次采集的数据包数，每包数据存放在ADBuf数组中
	//	{
#if 0	
//		if( wParam == 48 )
	//		{
				if( ADResult((struct structADResult *)usbcard->getADbuf()) == ADCard_Success) 
				{			
					gotblock++;
				}
		
	//		}
//		if( wParam == 49 )
		//	{
				if( ADResult_1((struct structADResult *)usbcard->getADbuf1()) == ADCard_Success) 
				{			
					gotblock++;
				}			
		//	}
//		}
			if( gotblock  < 1 )			
				return ;
#else
		//	{
				if( ADResult((struct structADResult *)usbcard->getADbuf()) != ADCard_Success) 
				{			
					return;
				}
			//	else
			//		gotblock++;
			//}
//		if( wParam == 49 )
			//{
				if( ADResult_1((struct structADResult *)usbcard->getADbuf1()) != ADCard_Success) 
				{			
					return;
				}
			//	else				
			//		gotblock++;
			//}
		//	if( gotblock  < 1 )
		//		return ;
#endif			
			if((g->getUsb8221Par()).coding == TRUE)   //使用编码器
			{
			//	RbhUsb20* usbcard = (RbhUsb20*)TestSampleControl::cardPtr;
				if(usbcard->getDIsingal() == TRUE)    //有编码触发
				{
					if(g->gstyle->getDateFromCard() == FALSE) //数据已满
					{
						doGetWholeData();
					}
					else
					{
						usbcard->setDIsingal(FALSE);
						RefreshWave();
					}
				}
			}
			else                                      //未使用编码器
			{
				if(g->gstyle->getDateFromCard() == FALSE)
				{
				//	doGetWholeData();
					if(  g->getStatus() == Status_DEMORATE )
						{
								DataBuf* d = g->getDataBuf();
								d->resetDataLen();   //数据清空
								reSetPage();         //显示块回置
						}
				}
				else
				{
					RefreshWave();
				}
			}
	//	}
	}
	catch (CException e) 
	{
		AfxMessageBox("数据处理异常");
		return;
	}
		
}
/*
 *	显示各个显示块
 */
void MainDlg::showWaveBlock(int ix, int iy, int ex, int ey)
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	int end = 0;
	switch(g->getShowNum()) 
	{
	case WaveShowNum_EIGHT:
		{
			for(int i = 0; i < 8; i++)
			{
				StaticShow[i]->MoveWindow(ix,iy,2*ex,ey/2);
                CRect r(ix,iy,ix+2*ex,iy+ey/2);
				waverect[i] = r;
				iy += ey/2 + dy/2;
				/*
				if(i == 3)
				{
					ix = 10*dx + dx/2;  iy = 2*dy;
				}
				*/
			}
			end = 8;
		}
		break;
	case WaveShowNum_SEVEN:
		{
			for (int i = 0;i < 7;i++)
			{
				StaticShow[i]->MoveWindow(ix,iy,2*ex,3*ey/5);
				CRect r(ix,iy,ix+2*ex,iy+3*ey/5);
				waverect[i] = r;
				iy += 3*ey/5 + dy/2;
			}
			end = 7;
		}
		break;
	case WaveShowNum_SIX:
		{
			for (int i = 0;i < 6;i++)
			{
				StaticShow[i]->MoveWindow(ix,iy,2*ex,5*ey/7);
				CRect r(ix,iy,ix+2*ex,iy+5*ey/7);
				waverect[i] = r;
				iy += 5*ey/7 + dy/2;
			}
			end = 6;
		}
		break;
	case WaveShowNum_FIVE:
		{
			for (int i = 0;i < 5;i++)
			{
				StaticShow[i]->MoveWindow(ix,iy,2*ex,6*ey/7);
				CRect r(ix,iy,ix+2*ex,iy+6*ey/7);
				waverect[i] = r;
				iy += 6*ey/7 + dy/2;
			}
			end = 5;
		}
		break;
	case WaveShowNum_FOUR:
		{
			for(int i = 0; i < 4; i++)
			{
				StaticShow[i]->MoveWindow(ix,iy,2*ex,ey);
				CRect r(ix,iy,ix+2*ex,iy+ey);
				waverect[i] = r;
				iy += ey + dy/2;
			}
			end = 4;
		}
		break;
	case WaveShowNum_THREE:
		{
			for (int i = 0;i < 3;i++)
			{
				StaticShow[i]->MoveWindow(ix,iy,2*ex,3*ey/2);
				CRect r(ix,iy,ix+2*ex,iy+3*ey/2);
				waverect[i] = r;
				iy += 3*ey/2 + dy/2;
			}
			end = 3;
		}
		break;
	case WaveShowNum_TWO:
		{
			for(int i = 0; i < 2; i++)
			{
				StaticShow[i]->MoveWindow(ix,iy,2*ex,2*ey);
				CRect r(ix,iy,ix+2*ex,iy+2*ey);
				waverect[i] = r;
				iy += 2*ey + dy/2;
			}
			end = 2;
		}
		break;
	case WaveShowNum_ONE:
		{
			for(int i = 0; i < 1; i++)
			{
				StaticShow[i]->MoveWindow(ix,iy,2*ex,4*ey);
				CRect r(ix,iy,ix+2*ex,iy+4*ey);
				waverect[i] = r;
				iy += 4*ey + dy/2;
			}
			end = 1;
		}
		break;
	}
	for(int j = end; j < 8; j++)
	{
		StaticShow[j]->MoveWindow(-1,-1,1,1);
	}
	for(int k = 0; k < end; k++)
	{
		int sy = (waverect[k].bottom-waverect[k].top)/4;
		GetDlgItem(pnButtons[0][k])->MoveWindow( waverect[k].left-dx/2, waverect[k].top,       dx/2, sy);
		GetDlgItem(pnButtons[1][k])->MoveWindow( waverect[k].left-dx/2, waverect[k].bottom-sy, dx/2, sy);
	    GetDlgItem(pnButtons[2][k])->MoveWindow( waverect[k].left-dx/2, waverect[k].top+sy,    dx/2, sy);
	    GetDlgItem(pnButtons[3][k])->MoveWindow( waverect[k].left-dx/2, waverect[k].top+2*sy,    dx/2, sy);
	    titles[k]->MoveWindow(waverect[k].left,waverect[k].top-dy/2,dx,dy/2);
		titles[k]->SetWindowText(set.titles[k]);
	}
	
	for(    k = end; k < 8; k++)
	{
		GetDlgItem(pnButtons[0][k])->MoveWindow(-1,-1,-1,-1);
		GetDlgItem(pnButtons[1][k])->MoveWindow(-1,-1,-1,-1);
	    GetDlgItem(pnButtons[2][k])->MoveWindow(-1,-1,-1,-1);
		GetDlgItem(pnButtons[3][k])->MoveWindow(-1,-1,-1,-1);
		titles[k]->MoveWindow(-1,-1,-1,-1);
	}
    Invalidate();
}
/*
 *	显示参数设置，设置显示的块数量
 */
void MainDlg::OnButtonShowset() 
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
   	 ShowSet dlg;
	switch(g->getShowNum())
	{
	case WaveShowNum_EIGHT: dlg.m_ishowset = 0;
		break;
	case WaveShowNum_SEVEN:  dlg.m_ishowset = 1;
		break;
	case WaveShowNum_SIX:   dlg.m_ishowset = 2;
		break;
	case WaveShowNum_FIVE:   dlg.m_ishowset = 3;
		break;
	case WaveShowNum_FOUR:   dlg.m_ishowset = 4;
		break;
	case WaveShowNum_THREE:   dlg.m_ishowset = 5;
		break;
	case WaveShowNum_TWO:   dlg.m_ishowset = 6;
		break;
	case WaveShowNum_ONE:   dlg.m_ishowset = 7;
		break;
	}
	
	for(int i = 0; i < 8; i++)
	{
//		memcpy(dlg.DItitles[i],set.DItitles[i],sizeof(set.DItitles[i]));
		memcpy(dlg.DOtitles[i],set.DOtitles[i],sizeof(set.DOtitles[i]));
		memcpy(dlg.titles[i],set.titles[i],sizeof(dlg.titles[i]));
		dlg.alertlines[i] = waveshow[i]->getAlertLine();
		dlg.alertlines2[i] = waveshow[i]->getAlertLine2();
		dlg.alertlines3[i] = waveshow[i]->getAlertLine3();

		dlg.differ[i] = waveshow[i]->getDiffer();
		dlg.differadjust[i] = waveshow[i]->getDifferAdjust();


		dlg.showcompress[i] = waveshow[i]->getShowCompress();
		dlg.timelapes[i] = waveshow[i]->getTimeLapes();
	}
	memcpy(dlg.steps,set.steps,sizeof(set.steps));
	memcpy(dlg.alertlines,set.alertline,sizeof(set.alertline));
	memcpy(dlg.alertlines2,set.alertline2,sizeof(set.alertline2));
	memcpy(dlg.alertlines3,set.alertline3,sizeof(set.alertline3));
    memcpy(dlg.restrain,set.restrain,sizeof(set.restrain));
	memcpy(dlg.halfs,set.halfs,sizeof(dlg.halfs));

	if(dataOpenMode == 0)
		g->getShowCHSfromFile();

	if(dlg.DoModal() == IDOK)
	{
         switch(dlg.m_ishowset) 
		 {
         	case 0: g->setShowNum(WaveShowNum_EIGHT);
			 break;
		 case 1: g->setShowNum(WaveShowNum_SEVEN);
			 break;
		 case 2: g->setShowNum(WaveShowNum_SIX);
			 break;
		 case 3: g->setShowNum(WaveShowNum_FIVE);
			 break;
		 case 4: g->setShowNum(WaveShowNum_FOUR);
			 break;
		 case 5: g->setShowNum(WaveShowNum_THREE);
			 break;
		 case 6: g->setShowNum(WaveShowNum_TWO);
			 break;
		 case 7: g->setShowNum(WaveShowNum_ONE);
				 break;
         }
		 for(int i = 0; i < 8; i++)
		 {
			 waveshow[i]->setShowCompress(dlg.showcompress[i]);
			 waveshow[i]->setStep(dlg.steps[i]);
			 waveshow[i]->setAlertLine(dlg.alertlines[i]);
			 waveshow[i]->setAlertLine2(dlg.alertlines2[i]);
			 waveshow[i]->setAlertLine3(dlg.alertlines3[i]);
			 waveshow[i]->setRestrainY(dlg.restrain[i]);
			 waveshow[i]->setShowCompress(dlg.showcompress[i]);
			 waveshow[i]->setTimeLapes(dlg.timelapes[i]);
			 waveshow[i]->setDifferAdjust(dlg.differadjust[i]);
			 waveshow[i]->setDiffer(dlg.differ[i]); 
             		waveshow[i]->setHalfShow(dlg.halfs[i]);
			 memcpy(set.titles[i],dlg.titles[i],sizeof(set.titles[i]));
			 memcpy(set.DOtitles[i],dlg.DOtitles[i],sizeof(set.DOtitles[i]));
			 
		 }
		 memcpy(set.timelapes,dlg.timelapes,(sizeof(set.timelapes)));
		 memcpy(set.differadjust,dlg.differadjust,(sizeof(set.differadjust)));
		 memcpy(set.differ,dlg.differ,(sizeof(set.differ)));
		 memcpy(set.showcompress,dlg.showcompress,(sizeof(set.showcompress)));
		 memcpy(set.steps,dlg.steps,sizeof(set.steps));
		 memcpy(set.alertline,dlg.alertlines,sizeof(set.alertline));
		 memcpy(set.alertline2,dlg.alertlines2,sizeof(set.alertline2));
		 memcpy(set.alertline3,dlg.alertlines3,sizeof(set.alertline3));
		 memcpy(set.restrain,dlg.restrain,sizeof(set.restrain));
		 memcpy(set.halfs,dlg.halfs,sizeof(dlg.halfs));

		 set.showNum = g->getShowNum();
		 g->setAutoSet(set);
		 g->setAutoSetToFile();
	}
	ChangeShowBlock();
}

void MainDlg::myInit()
{
	GobalData* g = GobalData::getGobalData();
    
	DeletePtr(TestSampleControl::cardPtr);
	USB8221par& p = g->getUsb8221Par();
    	TestSampleControl::cardPtr = new RbhUsb20(this->m_hWnd, p.samplespeed, p.channelnum, p.block);
	
	g->Dlghandle = this->m_hWnd;
	dataOpenMode = 0;
	setStatus(Status_STOP);
}

void MainDlg::OnButtonStart() 
{
	GobalData* g = GobalData::getGobalData();
	ChooseFileDlg dlg;
	dlg.IsOpen = TRUE;  //打开文件采集
	DataSaveFactory f;
	DataSaveStyle* s = f.getDataSaveStyle(g->getSaveStyle());
	if(s == NULL)
	{
		AfxMessageBox("文件存储格式未定义");
		return;
	}
	dlg.suffix = s->getSuffix();   //文件名后缀
	dlg.m_strFileName = g->getFileName();
	DATAHEAD dHead = g->dataHead;
	dlg.m_strSteel =dHead.steel;
	dlg.m_strGuige =dHead.guige;
	dlg.m_strPly=dHead.ply;
	dlg.m_strMan=dHead.Uoperator;
	DeletePtr(s);
	CString lastName = dlg.m_strFileName;
	if(dlg.DoModal() == IDOK)      //文件名选择对话框
	{
		CString str;
		str.Format("%s.%s",dlg.m_strFileName,dlg.suffix);
		dataOpenMode = dlg.m_dataOpenMode;
		g->setWholeFileName(str);  //设置选定的文件名
		g->setSid(dlg.m_iSid);
		m_bSaveToFile = dlg.m_bSaveToFile;
		if(lastName != dlg.m_strFileName && m_bSaveToFile == FALSE)
			g->blockHead.id = 0;
	}
	else
	{
		return;
	}
	DataBuf* d = g->getDataBuf();
	d->resetDataLen();   //数据清空
	reSetPage();         //显示块回置
	autoControl = TRUE;
	setStatus(Status_START);
//   g->saveDataToFile(g->getWholeFileName());  
	if( (TestSampleControl::cardPtr)->Inital() == FALSE)   //采集卡初始化
	{
		AfxMessageBox("采集卡初始化失败");
		setStatus(Status_STOP);
		return;
	}
	if( (TestSampleControl::cardPtr)->Start() == FALSE)    //开始采集
	{
		AfxMessageBox("采集卡启动失败!");
		setStatus(Status_STOP);
		return;
	}
	g->goodflag = TRUE;         //重设好坏标志
	g->goodflag2 = TRUE; 
	g->wgoodflag = TRUE;         //重设好坏标志
	g->wgoodflag2 = TRUE; 
	showFileHead(TRUE , FALSE);
	
	Invalidate();
	m_conBstop.SetFocus();
}

void MainDlg::OnButtonCardset() 
{
	CARDSET dlg;
	dlg.cardWnd = this->m_hWnd;
	dlg.DoModal();
}

/*
 *	编码器触发响应
 */
LRESULT MainDlg::SampleMsg(WPARAM wParam, LPARAM lParam)
{
	RbhUsb20* usbcard = (RbhUsb20*)TestSampleControl::cardPtr;
	usbcard->setDIsingal(TRUE);
	return 0;
}

void MainDlg::OnButtonStop() 
{
	GobalData* g = GobalData::getGobalData();
	(TestSampleControl::cardPtr)->Stop();
	DataBuf* buf = g->getDataBuf();
		int len0 = buf->getdataLens(11);

	switch(g->getStatus()) 
	{
	case Status_DEMORATE:                            //标定状态
		{
			(TestSampleControl::cardPtr)->Stop();
             		DataBuf* d = g->getDataBuf();
			 d->democrateChs(0,d->getChannelNum()*2);  //基准标定
			 setStatus(Status_STOP);
			 m_conBdemocrate.SetFocus();
		}
		break;
	case Status_START:                               //采集状态
		{
			(TestSampleControl::cardPtr)->Stop();
			AUTOSET& set = g->getAutoSet();
			for(int i = 0; i < 8; i++)
			{
				waveshow[i]->setxMax(100000);
				waveshow[i]->setStep(set.steps[i]);
				InvalidateRect(waverect[i]);
			}	 
			 if(autoControl == TRUE && len0 >0 )
			 {
				 if(g->saveDataToFile(g->getWholeFileName()) == FALSE)   //保存数据文件
				 {
					 setStatus(Status_STOP);
					 AfxMessageBox("数据保存失败");
				 }
				 updateFileMsg();
			//	 UpdateMinPly();
				 autoControl = FALSE;
			 }
			 setStatus(Status_STOP);
			 m_conBstart.SetFocus();
		}
		break;
	case Status_CH_REVIEW:
		{
			AUTOSET& set = g->getAutoSet();
			for(int i = 0; i < 8; i++)
			{
				waveshow[i]->setxMax(100000);
				waveshow[i]->setStep(set.steps[i]);
				InvalidateRect(waverect[i]);
			}
			setStatus(oldstatus);
		}
		break;
	case Status_REVIEW:
		{
            g->CloseFile();
			g->getAutoSetFromFile();
			updataWaveShow();
			g->getShowCHSfromFile();
		    (g->getDataBuf())->loadIndexParsFromFile();
			(g->getDataBuf())->loadStdFromFile();
			for(int i = 0; i < 8; i++)
			{
				InvalidateRect(waverect[i]);
			}
			showFileHead(FALSE , TRUE);
			setStatus(Status_STOP);
		}
		break;
	}
	
}

void MainDlg::OnButtonDemocrate() 
{
	GobalData* g = GobalData::getGobalData();
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSaveStyle());  //获得显示风格
	g->setSuffix(style->getSuffix());
	int index = g->getSaveStyle();
	if (index==0)
	{	
		DataBuf* d = g->getDataBuf();
		d->resetDataLen();
		reSetPage();
		setStatus(Status_DEMORATE);
		dataOpenMode = 0;
		if( (TestSampleControl::cardPtr)->Inital() == FALSE)
		{
			AfxMessageBox("采集卡初始化失败");
			setStatus(Status_STOP);
			return;
		}
		if( (TestSampleControl::cardPtr)->Start() == FALSE)    //开始采集
		{
			AfxMessageBox("采集卡启动失败!");
			setStatus(Status_STOP);
			return;
		}
		Invalidate();
		m_bSaveToFile = FALSE;
		m_conBstop.SetFocus();
		showLengthRule = FALSE;
	}
}

void MainDlg::OnButtonParset() 
{
	PARSET dlg;
	dlg.analysis = FALSE;
	dlg.DoModal();
}

void MainDlg::setStatus(Status s)
{
	GobalData* g = GobalData::getGobalData();
	g->setStatus(s);
	
	CString str[8];
	str[Status_STOP]       = "欢迎使用";
	str[Status_START]      = "数据采集中……";
	str[Status_REVIEW]     = "历史数据显示";
	str[Status_CH_REVIEW]  = "通道回放中……";
	str[Status_DEMORATE]   = "通道标定中……";

	int dlgs[] = {
		IDC_BUTTON_START      ,/*0*/
		IDC_BUTTON_STOP       ,/*1*/ 
		IDC_BUTTON_DEMOCRATE  ,/*2*/  
		IDC_BUTTON_PARSET     ,/*3*/
		IDC_BUTTON_DATABASE   ,/*4*/ 
		IDC_BUTTON_CARDSET    ,/*5*/ 
		IDC_BUTTON_REPORT     ,/*6*/ 
		IDC_BUTTON_SHOWSET    ,/*7*/
		IDC_BUTTON_OPEN       ,/*8*/ 
		IDC_BUTTON_ANALYSIS   ,/*9*/
		IDC_BUTTON_RESHOW     ,/*10*/
		IDC_BUTTON_DATASAVESET,/*11*/
		IDC_BUTTON_IOSTATUS   ,/*12*/
	};
	BOOL enable[100]; memset(enable,TRUE,100);
    switch(s) 
	{
    case Status_STOP:
		{
			EnableWaveButtons(TRUE);
			EnableBlockButtons(FALSE);
			 enable[9] = FALSE; /*enable[10] = FALSE*/;
			m_conEhelp.SetWindowText(str[s]);
		}
		break;
    case Status_START:
		{
			EnableWaveButtons(FALSE);
			EnableBlockButtons(FALSE);
			enable[0] = FALSE; enable[2] = FALSE; enable[3] = FALSE; enable[4] = FALSE; 
			enable[5] = FALSE; enable[7] = FALSE;  enable[8] = FALSE; 
			enable[9] = FALSE; /*enable[10] = FALSE;*/ enable[11] = FALSE;
		}
		break;
	case Status_REVIEW:
		{
			EnableWaveButtons(TRUE);
			EnableBlockButtons(TRUE);
			enable[0] = FALSE; enable[2] = FALSE; enable[3] = FALSE;
			 enable[11] = FALSE;
		}
		break;
    case Status_CH_REVIEW:
		{
             EnableWaveButtons(FALSE);
             EnableBlockButtons(TRUE);
			 enable[0] = FALSE; enable[2] = FALSE; enable[3] = FALSE; enable[4] = FALSE; 
			 enable[5] = FALSE; enable[7] = FALSE; enable[8] = FALSE; 
			 enable[9] = FALSE; enable[10] = FALSE; enable[11] = FALSE;
		}
		break;
	case Status_DEMORATE:
		{
			EnableWaveButtons(FALSE);
			EnableBlockButtons(FALSE);
			enable[0] = FALSE; enable[2] = FALSE; enable[3] = FALSE; enable[4] = FALSE; 
			enable[5] = FALSE; enable[7] = FALSE; enable[8] = FALSE; 
			enable[9] = FALSE; enable[10] = FALSE; enable[11] = FALSE;
		}
		break;
    default:
		;
    }
	for(int i = 0; i < sizeof(dlgs)/sizeof(dlgs[0]); i++)
	{
        GetDlgItem(dlgs[i])->EnableWindow(enable[i]);
	}
//	
	//Invalidate();
}

void MainDlg::RefreshWave()
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	int i = g->getShowNum();

	static int n[8]={0,0,0,0,0,0,0,0};
	for(int k = 0; k < i; k++)
	{
		int ch = g->showCHS[0][k]-1;                                    //通道
		int len = buf->getdataLens(ch);                               //数据长度
		int pageN = len/(waveshow[k]->getxMax()/waveshow[k]->getStep())+1;
		int xNow = len%(waveshow[k]->getxMax()/waveshow[k]->getStep());
		if(pageN > waveshow[k]->getScreenPage())  //翻屏
		{
			if(k < g->getShowNum() && g->getStatus() == Status_DEMORATE)
			    showAverageData(k,waveshow[k]->getScreenPage());
           		waveshow[k]->nextScreen();
			InvalidateRect(waverect[k]);
		}
		else
		{
			if(n[k] >= 20 )
			{
				int dx = waverect[k].right - waverect[k].left;
				float position = xNow*waveshow[k]->getStep()/float(waveshow[k]->getxMax());
				int x1 = waverect[k].left + int(position*dx);
				int x2 = x1  + dx*waveshow[k]->getStep()/waveshow[k]->getxMax()+1;
				int y1 = waverect[k].top;
				int y2 = waverect[k].bottom;
				InvalidateRect(CRect(x1,y1,x2,y2),FALSE);
				n[k] = 0;
			}
			else
				n[k]++;
		}
	}
}

void MainDlg::OnDestroy() 
{
	GobalData* g = GobalData::getGobalData();
	g->CloseFile();
    
	CDialog::OnDestroy();

}

void MainDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{    
	extern int  Ready_Only;
	GobalData *g = GobalData::getGobalData();
	if ( Ready_Only == 1 )
	return;

	try
    {
		Status s = g->getStatus();
		switch(s)
		{
		case Status_START:
		case Status_DEMORATE:
			break;
		default:
			{
				CMenu menuPopup;
				CMenu* rMenu;
				BOOL ro = FALSE;
				for(int i = 0; i < 8; i++)
				{
					if(waverect[i].PtInRect(point))
					{
						int item =waveshow[i]->getWaveShowStyle();
						menuPopup.LoadMenu(IDR_ENVIROMENT_MENU);	
						rMenu = menuPopup.GetSubMenu(0);
						rMenu->GetSubMenu(4)->CheckMenuItem(ID_SIMPLE+item,MF_CHECKED);	
						rMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);
						pointInWave = i;
						ro = TRUE;
					}
				}
				if(ro == FALSE)
				{
					throw new CException();
				}
			}
		}
    }
	catch (CException e) 
	{
		AfxMessageBox("环境选项设置异常");
		return;
	}
	catch(...)
	{
       //AfxMessageBox("环境选项设置异常");
		return;
	}

}



/*
 *	环境菜单 第一屏
 */
void MainDlg::OnMenuitemFirstc() 
{
	waveshow[pointInWave]->resetScreen();
	InvalidateRect(waverect[pointInWave]);
}

/*
 *	环境菜单 下一屏
 */
void MainDlg::OnMenuitemNextc() 
{
	waveshow[pointInWave]->nextScreen();
	InvalidateRect(waverect[pointInWave]);
}

/*
 *	环境菜单 前一屏
 */
void MainDlg::OnMenuitemPrec() 
{
	waveshow[pointInWave]->preScreen();
	InvalidateRect(waverect[pointInWave]);
}

void MainDlg::OnButtonDatasaveset() 
{
	DataSetDlg dlg;
	dlg.DoModal();
}

void MainDlg::OnButtonOpen() 
{
	Rbh_SpecialFun(51,0,0,0,0,0);
	GobalData* g = GobalData::getGobalData();
	ChooseFileDlg dlg;
	dlg.IsOpen = FALSE;            //打开历史文件
	if(dlg.DoModal() == IDOK)      //文件名选择对话框
	{
		try
		{
			g->setWholeFileName(dlg.m_strFileName);  //设置选定的文件名
			//从历史选择对话框中得到的文件名是全名
			dataOpenMode = dlg.m_dataOpenMode;
			if(g->loadDataFromFile(g->getWholeFileName(),g->getFilePtr()) == FALSE)
				return;
			updateFileMsg();
		//	UpdateMinPly();
			updataWaveShow();
			reSetPage();
			ChangeShowBlock();
			showFileHead(FALSE ,FALSE);
			showLengthRule = TRUE;
		}
		catch(...) 
		{
			AfxMessageBox("数据打开异常");
			return;
		}
	}
	else
		return;

	setStatus(Status_REVIEW);
	
}

void MainDlg::reSetPage()
{
	for(int i = 0; i < 8; i++)
	{
		waveshow[i]->resetScreen();
	}
}

void MainDlg::OnBUTTON1p() 
{
	pageButton(0,ButtonFlag_UP);
}

void MainDlg::OnBUTTON1n() 
{
	pageButton(0,ButtonFlag_DOWN);
}

void MainDlg::OnBUTTON2p() 
{
	pageButton(1,ButtonFlag_UP);
}

void MainDlg::OnBUTTON2n() 
{
	pageButton(1,ButtonFlag_DOWN);
}

void MainDlg::OnBUTTON3p() 
{
	pageButton(2,ButtonFlag_UP);
}

void MainDlg::OnBUTTON3n() 
{
	pageButton(2,ButtonFlag_DOWN);
}

void MainDlg::OnBUTTON4p() 
{
	pageButton(3,ButtonFlag_UP);
}

void MainDlg::OnBUTTON4n() 
{
	pageButton(3,ButtonFlag_DOWN);
}

void MainDlg::OnBUTTON5p() 
{
	pageButton(4,ButtonFlag_UP);
}

void MainDlg::OnBUTTON5n() 
{
	pageButton(4,ButtonFlag_DOWN);
}

void MainDlg::OnBUTTON6p() 
{
	pageButton(5,ButtonFlag_UP);
}

void MainDlg::OnBUTTON6n() 
{
	pageButton(5,ButtonFlag_DOWN);
}

void MainDlg::OnBUTTON7p() 
{
	pageButton(6,ButtonFlag_UP);
}

void MainDlg::OnBUTTON7n() 
{
	pageButton(6,ButtonFlag_DOWN);
}

void MainDlg::OnBUTTON8p() 
{
	pageButton(7,ButtonFlag_UP);
}

void MainDlg::OnBUTTON8n() 
{
	pageButton(7,ButtonFlag_DOWN);
}

void MainDlg::pageButton(int num,ButtonFlag flag)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();		
	int ch = g->showCHS[0][num];                                    //通道
	int len = buf->getdataLens(ch);                               //数据长度
	int page = len/(waveshow[num]->getxMax()/waveshow[num]->getStep()) + 1;
	int CurrentPage = waveshow[num]->getScreenPage();
	switch(flag) 
	{
	case ButtonFlag_UP:  
		{
			if(CurrentPage > 1)
			{
			    waveshow[num]->preScreen();
				InvalidateRect(waverect[num]);
			}
		}
		break;
	case ButtonFlag_DOWN:
		{
			if(CurrentPage < page)
			{
			    waveshow[num]->nextScreen();
				InvalidateRect(waverect[num]);
			}
		}
		break;
	case ButtonFlag_BACK: 
		{
			if(CurrentPage != 1)
			{
				waveshow[num]->resetScreen();
				InvalidateRect(waverect[num]);
			}
		}
		break;
	case ButtonFlag_LAST:
		{
			if(CurrentPage != page)
			{
			    waveshow[num]->setPage(page);
				InvalidateRect(waverect[num]);
			}
		}
	}
}

void MainDlg::EnableWaveButtons(BOOL n)
{
	for(int i = 0; i < 8; i++)
	{
		GetDlgItem(pnButtons[0][i])->EnableWindow(n);
		GetDlgItem(pnButtons[1][i])->EnableWindow(n);
		GetDlgItem(pnButtons[2][i])->EnableWindow(n);
		GetDlgItem(pnButtons[3][i])->EnableWindow(n);
	}

	for(    i = 0; i < sizeof(AllWaveButton)/sizeof(AllWaveButton[0]); i++)
	{
        GetDlgItem(AllWaveButton[i])->EnableWindow(n);
	}
}

void MainDlg::OnBUTTONpp1() 
{
    pageButton(0,ButtonFlag_BACK);
}

void MainDlg::OnBUTTONpp2() 
{
    pageButton(1,ButtonFlag_BACK);
}

void MainDlg::OnBUTTONpp3() 
{
    pageButton(2,ButtonFlag_BACK);
}

void MainDlg::OnBUTTONpp4() 
{
    pageButton(3,ButtonFlag_BACK);	
}

void MainDlg::OnBUTTONpp5() 
{
	pageButton(4,ButtonFlag_BACK);
}

void MainDlg::OnBUTTONpp6() 
{
	pageButton(5,ButtonFlag_BACK);
}

void MainDlg::OnBUTTONpp7() 
{
	pageButton(6,ButtonFlag_BACK);
}

void MainDlg::OnBUTTONpp8() 
{
    pageButton(7,ButtonFlag_BACK);	
}

void MainDlg::OnBUTTONallpp() 
{
	GobalData* g =GobalData::getGobalData();
	if(g->seekDataToNum(1,g->getFilePtr()) == TRUE)
	    updateFileMsg();
//	UpdateMinPly();
}

void MainDlg::OnBUTTONallp() 
{
	GobalData* g =GobalData::getGobalData();
	if(g->seekDataToNum((g->blockHead).id-1,g->getFilePtr()) == TRUE)
	    updateFileMsg();
//	UpdateMinPly();
}

void MainDlg::OnButtonGonum() 
{
	UpdateData();
    GobalData* g =GobalData::getGobalData();
	if(g->seekDataToNum(m_iCurrentNum,g->getFilePtr()) == TRUE)
	    updateFileMsg();
//	UpdateMinPly();
}

void MainDlg::OnBUTTONalln() 
{
	GobalData* g =GobalData::getGobalData();
	if(g->seekDataToNum((g->blockHead).id+1,g->getFilePtr()) == TRUE)
	    updateFileMsg();
//	UpdateMinPly();
}

void MainDlg::OnBUTTONallnn() 
{
	GobalData* g =GobalData::getGobalData();
	if(g->seekDataToNum((g->dataHead).blocksum,g->getFilePtr()) == TRUE)
	    updateFileMsg();
//	UpdateMinPly();
}

/*
 *	显示当前数据文件整体和单块的信息
 */
void MainDlg::updateFileMsg()
{
	GobalData* g = GobalData::getGobalData();
	CString str,str1;
//	char inStatus[4];
	CTime t = CTime::GetCurrentTime();

	if( m_bSaveToFile == TRUE )
		str.Format("/%d(%02d:%02d)h%d,v%d",(g->dataHead).blocksum,(g->blockHead).hour,(g->blockHead).min,(g->blockHead).HendPt,(g->blockHead).VendPt);
    else
		str.Format("/%d(%02d:%02d)h%d,v%d",(g->dataHead).blocksum,t.GetHour(),t.GetMinute(),g->blockHead.xlength,g->blockHead.ylength);
    m_conSgonum.SetWindowText(str);
	m_iCurrentNum = (g->blockHead).id;
	for(int i = 0; i < 8; i++)
	{
		InvalidateRect(waverect[i]);
	}
//	GetNetIoStatus(inStatus);
	str1.Format("h:%d(%d %d %d %d %d %d)%d\r\nv:%d(%d %d %d %d %d %d)%d",g->blockHead.weldNum,g->blockHead.XPt[0],g->blockHead.XPt[1],g->blockHead.XPt[2],g->blockHead.XPt[3],g->blockHead.XPt[4],g->blockHead.XPt[5],g->blockHead.xlength,g->blockHead.weldNum2,g->blockHead.YPt[0],g->blockHead.YPt[1],g->blockHead.YPt[2],g->blockHead.YPt[3],g->blockHead.YPt[4],g->blockHead.YPt[5],g->blockHead.ylength);
	m_conEhelp.SetWindowText(str1);	
	UpdateData(FALSE);
//	if(g->reportdlg != NULL)
//		g->reportdlg->reFreshReport();
}

void MainDlg::OnButtonReshow() 
{
	GobalData* g = GobalData::getGobalData();
	oldstatus = g->getStatus();
	DataBuf* buf = g->getDataBuf();
    for(int i = 0; i < g->getShowNum(); i++)
	{
	        int ch = g->showCHS[0][i];
	        int max = buf->getdataLens(ch);
		if(0 == max ||max < 1000 )
			continue;
		waveshow[i]->setPage(1);
        	waveshow[i]->setxMax(max);
		waveshow[i]->setStep(1);
		InvalidateRect(waverect[i]);
	}
	showLengthRule = TRUE;
//	Statistic();
	setStatus(Status_CH_REVIEW);
	
}

void MainDlg::OnBUTTONwavepp() 
{
	OnBUTTONpp1(); OnBUTTONpp2();
	OnBUTTONpp3(); OnBUTTONpp4();
	OnBUTTONpp5(); OnBUTTONpp6();
	OnBUTTONpp7(); OnBUTTONpp8();
}

void MainDlg::OnBUTTONwavep() 
{
	OnBUTTON1p(); OnBUTTON2p();
	OnBUTTON3p(); OnBUTTON4p();
	OnBUTTON5p(); OnBUTTON6p();
	OnBUTTON7p(); OnBUTTON8p();
}

void MainDlg::OnBUTTONwaven() 
{
	OnBUTTON1n(); OnBUTTON2n();
	OnBUTTON3n(); OnBUTTON4n();
	OnBUTTON5n(); OnBUTTON6n();
	OnBUTTON7n(); OnBUTTON8n();
}

void MainDlg::OnBUTTONwavenn() 
{
	OnBUTTONnn1(); OnBUTTONnn2();
	OnBUTTONnn3(); OnBUTTONnn4();
	OnBUTTONnn5(); OnBUTTONnn6();
	OnBUTTONnn7(); OnBUTTONnn8();
}
static int locTimer = 0;
void MainDlg::OnTimer(UINT nIDEvent) 
{
	//OnMyNotify(NULL,NULL);
	if( SaveBmptoFile1 == TRUE )
	{
			locTimer++;
			if( locTimer > 2 )
		{
					save_screen_to_jpeg();
					locTimer =  0;
					SaveBmptoFile1 = FALSE;
					SaveBmptoFile=FALSE;
	    	}
		}	
	CDialog::OnTimer(nIDEvent);
}

BOOL MainDlg::OnEraseBkgnd(CDC* pDC) 
{	
	return CDialog::OnEraseBkgnd(pDC);
}

void MainDlg::OnBUTTONnn1() 
{
	pageButton(0,ButtonFlag_LAST);
}

void MainDlg::OnBUTTONnn2() 
{
	pageButton(1,ButtonFlag_LAST);
}

void MainDlg::OnBUTTONnn3() 
{
	pageButton(2,ButtonFlag_LAST);
}

void MainDlg::OnBUTTONnn4() 
{
	pageButton(3,ButtonFlag_LAST);
}

void MainDlg::OnBUTTONnn5() 
{
	pageButton(4,ButtonFlag_LAST);
}

void MainDlg::OnBUTTONnn6() 
{
	pageButton(5,ButtonFlag_LAST);
}

void MainDlg::OnBUTTONnn7() 
{
	pageButton(6,ButtonFlag_LAST);
}

void MainDlg::OnBUTTONnn8() 
{
	pageButton(7,ButtonFlag_LAST);
}

void MainDlg::EnableBlockButtons(BOOL n)
{
    for(int i = 0; i < sizeof(DlgAllButton)/sizeof(DlgAllButton[0]); i++)
	{
        GetDlgItem(DlgAllButton[i])->EnableWindow(n);
	}
}

void MainDlg::doGetWholeData()
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();
	switch(g->getStatus()) 
	{
	case Status_DEMORATE:
		{
			databuf->resetDataLen();
			for(int i = 0; i < 8; i++)
			{
				waveshow[i]->resetScreen();
			}
		}
		break;
	case Status_START: 
		{
			OnButtonStop();
			MsgDlg dlg;
			dlg.m_strMsg = "数据缓存已满，请修改采集频率";
			dlg.DoModal();
		}
		break;
	}
    
}
// 融合显示
void MainDlg::OnCombine() 
{
    waveshow[pointInWave]->setWaveStyle(WaveShowStyle_Combine);
	InvalidateRect(waverect[pointInWave]);
    saveWaveStye(WaveShowStyle_Combine,pointInWave);
}

void MainDlg::OnSimple()
{
	waveshow[pointInWave]->setWaveStyle(WaveShowStyle_SimpleShow);
	InvalidateRect(waverect[pointInWave]);
	saveWaveStye(WaveShowStyle_SimpleShow,pointInWave);
}

void MainDlg::OnFault() 
{
	waveshow[pointInWave]->setWaveStyle(WaveShowStyle_Fault);
	InvalidateRect(waverect[pointInWave]);
	saveWaveStye(WaveShowStyle_Fault,pointInWave);
}
// 二阶显示
void MainDlg::OnDiffer() 
{
	waveshow[pointInWave]->setWaveStyle(WaveShowStyle_Differ);
	InvalidateRect(waverect[pointInWave]);
	saveWaveStye(WaveShowStyle_Differ,pointInWave);
}

void MainDlg::OnPhase() 
{
	waveshow[pointInWave]->setWaveStyle(WaveShowStyle_Phase);
	InvalidateRect(waverect[pointInWave]);
	saveWaveStye(WaveShowStyle_Phase,pointInWave);
}

void MainDlg::OnPly() 
{
	waveshow[pointInWave]->setWaveStyle(WaveShowStyle_Ply);
	InvalidateRect(waverect[pointInWave]);
	saveWaveStye(WaveShowStyle_Ply,pointInWave);
}

//原始融合，447处理表面热凹的钢管。
void MainDlg::OnDifference() 
{
	if( pointInWave  > 1 ){
		waveshow[pointInWave]->setWaveStyle(WaveShowStyle_Difference);
		InvalidateRect(waverect[pointInWave]);
		saveWaveStye(WaveShowStyle_Difference,pointInWave);
	}
}
void MainDlg::OnThickPipe() 
{
	// TODO: Add your command handler code here
//	waveshow[pointInWave]->setWaveStyle(WaveShowStyle_ThickPipe);
//	InvalidateRect(waverect[pointInWave]);
//	saveWaveStye(WaveShowStyle_ThickPipe,pointInWave);
	
}


void MainDlg::ChangeShowBlock()
{
    int ix = 0; int iy = 0; int ex = 2*dx; int ey = 2*dy;
	ix = 2*dx; iy = dy/2; ex = 8*dx+dx/2; ey = 4*dy + dy/2;
	
	showWaveBlock(ix, iy, ex, ey);
}

void MainDlg::OnButtonAnalysis() 
{
    PARSET dlg;
	dlg.analysis = TRUE;
	if(dlg.DoModal() == IDOK)
	{
		for(int i = 0; i < 8; i++)
		{
            InvalidateRect(waverect[i]);
		}
	}
}

/*
 *	显示标定翻屏时的平均值
 */
void MainDlg::showAverageData(int id, int page)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	WORD** data = buf->getDataPtr();
   	int chstart = g->showCHS[0][id]-1;
	int chend   = g->showCHS[1][id]-1;
	int step = waveshow[id]->getStep();
	int xMax = waveshow[id]->getxMax();
	int start = (page - 1) * xMax / step;
	int end   = page * xMax / step;
	
	CString avText = "";
	int i=0;
//	float VZero=0 ,VMax=0 ;
//	char DrvName[32];
//	ConfigInfo(DrvName,&i,&i,&i,&i,&VZero,&VMax,&i);
	for( i = chstart; i<= chend; i++)
	{
		long sum = 0;
		for(int j = start; j < end; j++)
		{
			sum += (data[i][j]);
		}
		int average =sum/(end - start);
	//	 average = 	average*4096/(35250*2);
		if( average < 0 )
		{
			average=0;
		}	
		CString str; 
		str.Format("  %d |  ",average);
		avText += str;
	}
//  实验 给地取12位是2047,5v是4095;
//  5v  4095
//  取16位 ，地是39847，挂空是31910, 5v=7024，
//接-5V时采集结果是0，接地时是2047，接5V是4095

	CDC* pDC = GetDC();
	pDC->DrawText(avText,CRect(waverect[id].left-dx,waverect[id].top-dy/2,waverect[id].right+dx,waverect[id].top),DT_CENTER);
}

void MainDlg::updataWaveShow()
{
    GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	for(int i = 0; i < g->getShowNum(); i++)
	{
		waveshow[i]->setRestrainY(set.restrain[i]);
		waveshow[i]->setWaveStyle(set.showstyle[i]);
		waveshow[i]->setAlertLine(set.alertline[i]);
		waveshow[i]->setAlertLine2(set.alertline2[i]);
		waveshow[i]->setAlertLine3(set.alertline3[i]);
		waveshow[i]->setStep(set.steps[i]);
	}
}

void MainDlg::saveWaveStye(WaveShowStyle s, int id)
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	set.showstyle[id] = s;
	g->setAutoSet(set);
	g->setAutoSetToFile();
}

void MainDlg::showFileHead(BOOL isStart ,BOOL clear)
{
	CTime t = CTime::GetCurrentTime();
	GobalData* g = GobalData::getGobalData();
	DATAHEAD dHead = g->dataHead;
    m_conEmsg.ResetContent();
	if(clear == FALSE && isStart == FALSE)
	{
		CString strMsg;
		strMsg.Format("文件名:%s",g->getWholeFileName());
        m_conEmsg.AddString(strMsg);
		strMsg.Format("总根数:%d  时间:%4d-%02d-%02d",dHead.blocksum,dHead.year,dHead.month,dHead.day);
		m_conEmsg.AddString(strMsg);
		strMsg.Format("钢级:%s  壁厚:%s  规格:%s",dHead.steel,dHead.ply,dHead.guige);
		m_conEmsg.AddString(strMsg);
		strMsg.Format("操作员:%s",dHead.Uoperator);
		m_conEmsg.AddString(strMsg);
	}
    else if(clear == FALSE && isStart == TRUE)
	{
		CString strMsg;
		strMsg.Format("文件名:%s",g->getWholeFileName());
		m_conEmsg.AddString(strMsg);
		strMsg.Format("时间:%4d-%02d-%02d",t.GetYear(),t.GetMonth(),t.GetDay());
		m_conEmsg.AddString(strMsg);
		strMsg.Format("钢级:%s  壁厚:%s  规格:%s",dHead.steel,dHead.ply,dHead.guige);
		m_conEmsg.AddString(strMsg);
		strMsg.Format("操作员:%s",dHead.Uoperator);
		m_conEmsg.AddString(strMsg);
	}
	UpdateData(FALSE);
}

void MainDlg::OnButtonIostatus() 
{
//	Rbh_SpecialFun(51,0,0,0,0,0);
	GobalData* g = GobalData::getGobalData();
	if(g->IoStatusDlg == NULL)
	     g->IoStatusDlg = new CIOStatusDlg(this);
}

void MainDlg::OnButtonReport() 
{
#if 0
	GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	if( addOrDel == FALSE)
	{
		addOrDel = TRUE;
		set.thickPipeMode = TRUE;
	}
	else
	{
		addOrDel = FALSE;
		set.thickPipeMode = FALSE;
	}
	g->setAutoSet(set);
#endif
#if 0
 extern int recordXPt[10];
extern  int recordYPt[10];
 extern int  lastXpt[5];
extern int lastYpt[5];
if( addOrDel == TRUE )
	addOrDel = FALSE;
else 
	{
		addOrDel = TRUE;
		lastXpt[0] = recordXPt[0];lastXpt[1] = recordXPt[1];lastXpt[2] = recordXPt[2];
		lastYpt[0] = recordYPt[0];lastYpt[1] = recordYPt[1];lastYpt[2] = recordYPt[2];
	}
#endif
}

void MainDlg::OnButtonDatabase() 
{
	try
	{
		GobalData* g = GobalData::getGobalData();
		DataSaveFactory factory;
		DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());
		style->DoDataBase();
		DeletePtr(style);
	}
	catch (CException e) 
	{
        AfxMessageBox("数据库操作失败");
		return;
	}
	
}

LRESULT MainDlg::DlgNewMsg(WPARAM wParam,LPARAM lParam)
{
	GobalData* g = GobalData::getGobalData();
	switch(wParam) 
	{
	case COMPLETE_THIS: 
		{
			(TestSampleControl::cardPtr)->Stop();			
          	g->gstyle->endSampleData();
      	    OnButtonReshow();
			setStatus(oldstatus);
			showLengthRule = TRUE;
			
			if(g->getStatus() == Status_START&& autoControl == TRUE)
			{
				int sum = (g->dataHead).blocksum ;
				autoControl = FALSE; //当前采集已经结束 等待下次触发
			if( m_bSaveToFile == TRUE )
				{
					SaveBmptoFile = FALSE;
				if(g->saveDataToFile(g->getWholeFileName()) == FALSE)   //保存数据文件
				{
					setStatus(Status_STOP);
					AfxMessageBox("数据保存失败");
					return -1;
				}
				updateFileMsg();
		//			if(sum > 200 )
					showFileHead(TRUE , FALSE);
			    }
			else
				{
					
					SaveBmptoFile = TRUE;
					g->blockHead.id++;
					updateFileMsg();
				}		

				if( (TestSampleControl::cardPtr)->Inital() == FALSE)   //采集卡初始化
				{
					AfxMessageBox("采集卡初始化失败");
					setStatus(Status_STOP);
					return -1;
				}
				
				if( (TestSampleControl::cardPtr)->Start() == FALSE)    //开始采集
				{
					AfxMessageBox("采集卡启动失败!");
					setStatus(Status_STOP);
					return -1;
				}
			
			}
			//Sleep(10);			
		//	Invalidate();
/*
			DataBuf* buf = g->getDataBuf();
			for(int i = 0; i < 4; i++)
			{
				int ch = g->showCHS[0][i]-1;
				int max = buf->getdataLens(ch);
				if(0 == max ||max < 1000 )
					continue;
				waveshow[i]->setPage(1);
		       	waveshow[i]->setxMax(max);
				waveshow[i]->setStep(1);
				InvalidateRect(waverect[i]);
			}
			Invalidate();*/
		}
		break;
	case NEWONE_NEXT:
		{
			AUTOSET& set = g->getAutoSet();
			for(int i = 0; i < 4; i++)
			{
				waveshow[i]->setxMax(100000);
				waveshow[i]->setStep(set.steps[i]);
				InvalidateRect(waverect[i]);
			}			
			KillTimer(1);
			autoControl = TRUE;   //在新的采集中  
			DataBuf* d = g->getDataBuf();
			d->resetDataLen();   //数据清空
			reSetPage();         //显示块回置
		//	Invalidate();
			g->goodflag = TRUE;         //重设好坏标志
			g->goodflag2 = TRUE;
			g->wgoodflag = TRUE;         //重设好坏标志
			g->wgoodflag2 = TRUE;
			showLengthRule = FALSE;
			if( (TestSampleControl::cardPtr)->SampleStart() == FALSE)    //开始采集
			{
					AfxMessageBox("采集卡启动失败!");
					setStatus(Status_STOP);
					return -1;
			}
		//	MsgDlg msgdlg;
		//	msgdlg.timespace = 200;
		//	msgdlg.m_strMsg = "新的采集开始!";
		//	msgdlg.DoModal();
		}
		break;
	}
	return 0;
}

BOOL MainDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
	{
		GobalData* g = GobalData::getGobalData();
		switch(pMsg->wParam) 
		{
		case VK_LEFT: 
			{
				if( GetDlgItem(IDC_BUTTON_wavep)->IsWindowEnabled() )
				{
					OnBUTTONwavep();
				}
			}
			return TRUE;    
		case VK_RIGHT: 
			{
				if( GetDlgItem(IDC_BUTTON_waven)->IsWindowEnabled() )
				{
					OnBUTTONwaven();
				}
			}
			return TRUE;
			/*
		case  VK_SPACE:
			{
                switch(g->getStatus())
				{
				case Status_START:
				case Status_DEMORATE:
					{
						OnButtonStop();
					}
				}
			}
			return TRUE;
			*/
		case VK_UP: 
			{
				if( GetDlgItem(IDC_BUTTON_allp)->IsWindowEnabled() )
				{
					OnBUTTONallp();
				}
			}
			return TRUE; 
			case VK_DOWN: 
			{
				if( GetDlgItem(IDC_BUTTON_alln)->IsWindowEnabled() )
				{
					OnBUTTONalln();
				}
			}
			return TRUE; 
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL MainDlg::DestroyWindow() 
{
    OnButtonStop();
	for(int i = 0; i < 8; i++)
	{
		DeletePtr(waveshow[i]);
	}
	return CDialog::DestroyWindow();
}

BOOL MainDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
//	GobalData* g = GobalData::getGobalData();
//	if(g->getStatus() == Status_START)
//		return FALSE;
//	DataBuf* databuf = g->getDataBuf();
//	short** data = databuf->getDataPtr();
//	switch(pCopyDataStruct->dwData) 
//	{
//	case PROCESSMSG_SELNUM:
//		{
//			g->setSaveStyle(Floordata);
//			char* b = (char*)pCopyDataStruct->lpData;
//			int len = *(int*)b;
//            char* fname = new char[len+1];
//			memcpy(fname,(&b[sizeof(int)]),len);
//            fname[len] = '\0';
//			int selnum = *(int*)(&b[len+sizeof(int)]);
//			selnumforFloordata = selnum;
//			CString str;
//			str.Format("%s_%d.flr",fname,selnum);
//            g->setWholeFileName(str);
//
//			if(SetForegroundWindow() == 0)
//				AfxMessageBox("窗口无法置于最前端");
//			delete[] fname;
//		}
//		break;
//	case PROCESSMSG_VIEWNUM:
//		{
//			g->setSaveStyle(Floordata);
//			char* b = (char*)pCopyDataStruct->lpData;
//			int flen = *(int*)b;
//            char* fname = new char[flen+1];
//			memcpy(fname,(&b[sizeof(int)]),flen);
//            fname[flen] = '\0';
//			int selnum = *(int*)(&b[flen+sizeof(int)]);
//			selnumforFloordata = selnum;
//			CString str;
//			str.Format("%s_%d.flr",fname,selnum);
//            g->setWholeFileName(str);
//			
//			if(SetForegroundWindow() == 0)
//				AfxMessageBox("窗口无法置于最前端");
//			delete[] fname;
//
//            int len = *(int*)(&b[flen+2*sizeof(int)]);
//			int index = flen+3*sizeof(int);
//			for(int i = 0; i < 16; i++)
//			{
//                databuf->setDataLens(i,0);
//				if(len <= g->getDataLen())
//				{
//				     memcpy(data[i],&b[index],len*sizeof(short));
//				     index += len*sizeof(short);
//					 databuf->setDataLens(i,len);
//				}
//				else
//				{
//					AfxMessageBox("数据拷贝失败");
//					return FALSE;
//				}
//			}
//		}
//		break;
//	case PROCESSMSG_PARNEED:
//		{
//			COPYDATASTRUCT cds;
//			memset(&cds, 0, sizeof(cds));
//			cds.dwData = PROCESSMSG_PARSAVE; //保存数据
//			cds.cbData = 16*sizeof(short)*2;
//			short b[32];
//			memcpy(b,databuf->getParPtr(),16*sizeof(short));
//			memcpy(b+16,databuf->getStdPtr(),16*sizeof(short));
//            cds.lpData = LPVOID(b);
//			sendCommand(cds);
//		}
//		break;
//	case PROCESSMSG_UPDATE:
//		{
//            char* b = (char*)pCopyDataStruct->lpData;
//			memcpy(databuf->getParPtr(),b,16*sizeof(short));
//			memcpy(databuf->getStdPtr(),b+16*sizeof(short),16*sizeof(short));
//		}
//		break;
//	default:
//		AfxMessageBox("错误消息指令");
//	}
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

BOOL MainDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style &= ~(FWS_ADDTOTITLE);
	
	return CDialog::PreCreateWindow(cs);
}

BOOL MainDlg::CheckforOtherProcess()
{
//    GobalData* g = GobalData::getGobalData();
//	DataBuf* databuf = g->getDataBuf();
//	short** data = databuf->getDataPtr();
//	if(g->getSaveStyle() == Floordata)  //为储罐底板程序设置数据传递
//	{
//		COPYDATASTRUCT cds;
//		memset(&cds, 0, sizeof(cds));
//		cds.dwData = PROCESSMSG_SAVEDATA; //保存数据
//        cds.cbData = sizeof(int) + sizeof(int);
//		for(int i = 0; i < 16; i++)
//		{
//			cds.cbData += databuf->getdataLens(i)*sizeof(short);
//		}
//		char* bs = new char[cds.cbData];
//        *(int*)bs = selnumforFloordata;  //单块编号
//		int index = sizeof(int);
//
//		*(int*)(&bs[index]) = databuf->getdataLens(0);  //第i通道的数据长度
//		index += sizeof(int);
//
//        for(    i = 0; i < 16; i++)
//        {
//			memcpy(&bs[index],data[i],databuf->getdataLens(i)*sizeof(short));
//			index += databuf->getdataLens(i)*sizeof(short);
//		}
//		ASSERT(index == (int)cds.cbData);
//		cds.lpData = (LPVOID)bs;
//		sendCommand(cds);
//
//		delete[] bs;
//		return TRUE;
//	}
	return FALSE;
}

BOOL MainDlg::sendCommand(COPYDATASTRUCT &cds)
{
    CWnd *pDisplayWnd = CWnd::FindWindow(NULL, "储罐设计");
	if(pDisplayWnd)
	{
		pDisplayWnd->SendMessage(WM_COPYDATA,
			(WPARAM)GetSafeHwnd(), (LPARAM)&cds);
	}
	else
	{
		AfxMessageBox("储罐设计程序未打开");
		return FALSE;
	}
	return TRUE;
}

void MainDlg::OnButtonSprent() 
{
	HBITMAP hBitmap;
	CDC dc;
	dc.CreateDC("DISPLAY",NULL,NULL,NULL);
	int Width=GetSystemMetrics(SM_CXSCREEN);
	int Height=GetSystemMetrics(SM_CYSCREEN);
	//	bm.CreateCompatibleBitmap(&dc,picW,picH);
	hBitmap = GetSrcBit(dc,Width,Height);	
	CDC sdc;
	CPrintDialog printDlg(FALSE);          //生成打印机设备环境
	if(printDlg.DoModal()==IDCANCEL)       //让用户选择打印纸张
		return;
	short printQuality;
	
	printDlg.GetDefaults();
	DEVMODE *dm = printDlg.GetDevMode();
	dm->dmOrientation = DMORIENT_LANDSCAPE;
	dm->dmFields|= DM_ORIENTATION;
	printQuality = dm->dmPrintQuality;
	dm->dmPaperSize = NULL;
	dm->dmPaperLength = 290;
	dm->dmPaperWidth = 210;
	
	sdc.Attach(printDlg.CreatePrinterDC());//让HANDLE连接到dc上	
	sdc.m_bPrinting = TRUE;
	
	CString strTitle;
	strTitle.LoadString(AFX_IDS_APP_TITLE);
	
	DOCINFO di;
	::ZeroMemory(&di,sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = strTitle;
	
	if(sdc.StartDoc(&di)==-1)
	{
		MessageBox("StartDoc error");
		return;
	}
	
	int horze = sdc.GetDeviceCaps(HORZRES);
	int vertical = sdc.GetDeviceCaps(VERTRES);	
			sdc.StartPage();
			Draw(sdc,hBitmap,20, 20, 4.7,5.2,horze,vertical);
			sdc.EndPage();
	sdc.EndDoc();
}

HBITMAP MainDlg::GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight)
{
    HDC hBufDC;
	
	HBITMAP hBitmap, hBitTemp;
	
	hBufDC = CreateCompatibleDC(hDC);
	
	hBitmap = CreateCompatibleBitmap(hDC, BitWidth, BitHeight);
	
	hBitTemp = (HBITMAP) SelectObject(hBufDC, hBitmap);
	
	StretchBlt(hBufDC, 0, 0, BitWidth, BitHeight,
		
		hDC, 0, 0, BitWidth, BitHeight, SRCCOPY);
	
	hBitmap = (HBITMAP) SelectObject(hBufDC, hBitTemp);
	
	::DeleteDC(hBufDC);
	
	return hBitmap;	
}

void MainDlg::Draw(HDC hDC, HBITMAP hBmp, int iX, int iY, double dScaleX, double dScaleY, int iWidth, int iLength)
{
    HPALETTE hPal;

         BITMAP                     bm;

         BITMAPINFOHEADER         bi;

         LPBITMAPINFOHEADER          lpbi;

         DWORD                      dwLen;

         HANDLE                     hDIB;

         HANDLE                     handle;

         HDC                            hDC1;

         if(GetDeviceCaps(hDC,RASTERCAPS) & RC_PALETTE )

         {

                   UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);

                  LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

                  pLP->palVersion = 0x300;

                  pLP->palNumEntries =GetSystemPaletteEntries( hDC, 0, 255, pLP->palPalEntry );

                  hPal=CreatePalette(pLP );

                   delete[] pLP;

         }

         if (hPal==NULL)         hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

         ::GetObject(hBmp,sizeof(bm),(LPSTR)&bm);

         bi.biSize             = sizeof(BITMAPINFOHEADER);

         bi.biWidth                   = bm.bmWidth;

         bi.biHeight                    = bm.bmHeight;

         bi.biPlanes                    = 1;

         bi.biBitCount                 = bm.bmPlanes * bm.bmBitsPixel;

         bi.biCompression         = BI_RGB;

         bi.biSizeImage              = 0;

         bi.biXPelsPerMeter       = 0;

         bi.biYPelsPerMeter       = 0;

         bi.biClrUsed                   = 0;

         bi.biClrImportant = 0;

         int nColors = (1 << bi.biBitCount);

         if( nColors > 256 )

                  nColors = 0;

         dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

         hDC1 = ::GetDC(NULL);

         hPal = SelectPalette(hDC1,hPal,FALSE);

         RealizePalette(hDC1);

         hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

         if (!hDIB)

         {

                  SelectPalette(hDC1,hPal,FALSE);

                  ::ReleaseDC(NULL,hDC1);

                  DeleteObject(hPal);

                   return ;

         }

         lpbi = (LPBITMAPINFOHEADER)hDIB;

         *lpbi = bi;

         ::GetDIBits(hDC1, hBmp, 0L, (DWORD)bi.biHeight,

                  (LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

         bi = *lpbi;

         if (bi.biSizeImage == 0)

                  bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8)* bi.biHeight;

         dwLen += bi.biSizeImage;

         if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))

                   hDIB = handle;

         else

         {

                  GlobalFree(hDIB);

                  SelectPalette(hDC1,hPal,FALSE);

                  ::ReleaseDC(NULL,hDC1);

                  DeleteObject(hPal);

                   return ;

         }

         lpbi = (LPBITMAPINFOHEADER)hDIB;

         BOOL bGotBits = GetDIBits( hDC1, hBmp,0L,(DWORD)bi.biHeight,(LPBYTE)lpbi+ (bi.biSize + nColors * sizeof(RGBQUAD)),

                  (LPBITMAPINFO)lpbi,(DWORD)DIB_RGB_COLORS);

         if( !bGotBits )

         {

                  GlobalFree(hDIB);

                  SelectPalette(hDC1,hPal,FALSE);

                  ::ReleaseDC(NULL,hDC1);

                  DeleteObject(hPal);

                   return;

         }

         if(iWidth==0||iLength==0)

         {

                  iWidth=lpbi->biWidth;

                  iLength=lpbi->biHeight;

                  iWidth=(int)(dScaleX*iWidth);

                  iLength=(int)(iLength*dScaleY);

         }

         StretchDIBits(hDC,iX,iY,iWidth,iLength,0,0,lpbi->biWidth,lpbi->biHeight,(LPBYTE)lpbi                     // address for bitmap bits

                   + (bi.biSize + nColors * sizeof(RGBQUAD)),(LPBITMAPINFO)lpbi,DIB_RGB_COLORS,SRCCOPY);

         SelectPalette(hDC1,hPal,FALSE);

         ::ReleaseDC(NULL,hDC1);

         DeleteObject(hDIB);

         DeleteObject(hPal);
}



void MainDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 	CClientDC dc(this);
// 	dc.SetROP2(R2_NOTXORPEN);
// 	CGdiObject* systemPen = NULL;
// //	CGdiObject* systemBrush = NULL;
// 	CGdiObject* org = NULL;
// 	CPen blackPen;
// 	blackPen.CreatePen(PS_SOLID,1,RGB(255,0,0));
// 	systemPen = dc.SelectObject(&blackPen);

	CDialog::OnMouseMove(nFlags, point);
}

void MainDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	m_bIsCapturing = true;
	CDialog::OnLButtonDown(nFlags, point);
}

void MainDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bIsCapturing)
	{
		ReleaseCapture();
		m_bIsCapturing = FALSE; 
	}
	CDialog::OnLButtonUp(nFlags, point);
}


void MainDlg::Statistic()
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();
	WORD** data = databuf->getDataPtr();
	short* pars = databuf->getParPtr();
	short* stdline = databuf->getStdPtr();
	int k[21] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i = 0; i < 16; i++)
	{
		int alertl = waveshow[i/4]->getAlertLine();
		for(int j = 0; j<databuf->getdataLens(i);j++)
		{
			int y = abs(data[i][j] - stdline[i])*pars[i];
			if ( y >= alertl*1024*2 )
			{
				k[0]++;
			}
			else if ( (y<alertl*1024*2)&&(y>=alertl*1024*19/10))
			{
				k[1]++;
			}
			else if ( (y<alertl*1024*19/10)&&(y>=alertl*1024*18/10))
			{
				k[2]++;
			}
			else if ( (y<alertl*1024*18/10)&&(y>=alertl*1024*17/10))
			{
				k[3]++;
			}
			else if ( (y<alertl*1024*17/10)&&(y>=alertl*1024*16/10))
			{
				k[4]++;
			}
			else if ( (y<alertl*1024*16/10)&&(y>=alertl*1024*15/10))
			{
				k[5]++;
			}
			else if ( (y<alertl*1024*15/10)&&(y>=alertl*1024*14/10))
			{
				k[6]++;
			}
			else if ( (y<alertl*1024*14/10)&&(y>=alertl*1024*13/10))
			{
				k[7]++;
			}
			else if ( (y<alertl*1024*13/10)&&(y>=alertl*1024*12/10))
			{
				k[8]++;
			}
			else if ( (y<alertl*1024*12/10)&&(y>=alertl*1024*11/10))
			{
				k[9]++;
			}else if ( (y<alertl*1024*11/10)&&(y>=alertl*1024))
			{
				k[10]++;
			}
			else if ( (y<alertl*1024)&&(y>=alertl*1024*9/10))
			{
				k[11]++;
			}
			else if ( (y<alertl*1024*9/10)&&(y>=alertl*1024*8/10))
			{
				k[12]++;
			}
			else if ((y<alertl*1024*8/10)&&(y>=alertl*1024*7/10))
			{
				k[13]++;
			}
			else if ((y<alertl*1024*7/10)&&(y>=alertl*1024*6/10))
			{
				k[14]++;
			}
			else if ((y<alertl*1024*6/10)&&(y>=alertl*1024*5/10))
			{
				k[15]++;
			}
			else if ((y<alertl*1024*5/10)&&(y>=alertl*1024*4/10))
			{
				k[16]++;
			}
			else if ((y<alertl*1024*4/10)&&(y>=alertl*1024*3/10))
			{
				k[17]++;
			}
			else if ((y<alertl*1024*3/10)&&(y>=alertl*1024*2/10))
			{
				k[18]++;
			}
			else if ((y<alertl*1024*2/10)&&(y>=alertl*1024*1/10))
			{
				k[19]++;
			}
			else
			{
				k[20]++;
			}
		}
	}
	CRect rect;
	CWnd* pWnd = statisticShow->getWnd();
	pWnd->GetClientRect(&rect);
	CDC* pDC = pWnd->GetDC();

	CBitmap* pOldBmp = NULL;
	memDC.CreateCompatibleDC(NULL);
	memBitmap.CreateCompatibleBitmap(pDC,rect.right, rect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
	statisticShow->DrawBack(&memDC,k);
	pDC->BitBlt(0,0,rect.right,rect.bottom,&memDC,0,0,SRCCOPY);
	memDC.DeleteDC();
	memBitmap.DeleteObject();
    pWnd->ReleaseDC(pDC);
//	pWnd->ReleaseDC(pDC);
//	InvalidateRect(statisticrRect);
}

//DEL HBRUSH MainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
//DEL {
//DEL 	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//DEL 	
//DEL 	// TODO: Change any attributes of the DC here
//DEL 	
//DEL 	// TODO: Return a different brush if the default is not desired
//DEL 	if(pWnd->GetDlgCtrlID()==IDC_STATIC4)
//DEL 	{
//DEL 		pDC->SetBkColor(RGB(0,255,0));
//DEL //		pDC->SetBkMode(TRANSPARENT);
//DEL 		return m_brush;
//DEL 	}
//DEL 	return hbr;
//DEL }

void MainDlg::UpdateMinPly()
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	DataBuf* buf = g->getDataBuf();
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	int maxlen = buf->getdataLens(20);
	if (maxlen<= 2000)
	{
		return;
	}
	int min = -2048;
	float ply = 0;
	
	for (int j = 0; j < maxlen-7000 ; j=j+2 )
	{
// 		if((abs(data[20][j]-data[20][j-1])>50 && j>1)||(abs(data[21][j]-data[21][j-1])>50 && j>1))
// 		{
// 			data[20][j] = data[20][j-1];
// 			data[21][j] = data[21][j-1];
// 		}
		int data21 = 0,data22 = 0;
		if(data[20][j]-data[20][9000]>20)
		{
			data21 = data[20][9000]+float(data[20][j]-data[20][9000])/float(float(set.alertline2[7])/10);
		}
		else
		{
			data21 = data[20][j];
		}
		if(data[21][j]-data[21][9000]>20)
		{
			data22 = data[21][9000]+float(data[21][j]-data[21][9000])/float(float(set.alertline2[7])/10);
		}
		else
		{
			data22 = data[21][j];
		}
//		int max = 2048;
// 		for (int i = 0; i<1; i++)
// 		{
// 			if((data[20][j+i]-stdline[20])*pars[20]/100+(data[21][j+i]-stdline[21])*pars[21]/100<max)
// 			{
// 				max = (data[20][j+i]-stdline[20])*pars[20]/100+(data[21][j+i]-stdline[21])*pars[21]/100;
// 			}
// 		}
// 		if (max>min)
// 		{
// 			min = max;
// 		}
		if((data21-stdline[20])*pars[20]/100+(data22-stdline[21])*pars[21]/100>min)
		{
			min = (data21-stdline[20])*pars[20]/100+(data22-stdline[21])*pars[21]/100;
		}
	}
	ply = float(min*5.0/2048);
	CString str;
	if (ply >= 0)
	{
		str.Format("%0.2fmm",atof((g->dataHead).ply) - ply);
	}
	if (ply < 0)
	{
		str.Format("%0.2fmm",atof((g->dataHead).ply) - ply);
	}
	
    m_conMinPly.SetWindowText(str);
	//	UpdateData(TRUE);
	UpdateData(FALSE);
}


void MainDlg::ReadlvboToFile(CString strFileName)
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
int MainDlg::save_screen_to_jpeg()
  {
  //	 char* filename, 
	const	int quality =76;
	GobalData* g = GobalData::getGobalData();
  	CString name=	"data\\"+ g->getWholeFileName();
	char* filenames=	 (char*)name.GetBuffer(0);
	CString dirs1;
	
	filenames[strlen(filenames)-4] = '\0';		
	dirs1.Format("%s",filenames);

	if (!PathIsDirectory(dirs1)) 		
	{  
		CreateDirectory(dirs1, 0);//不存在则创建  
	}  
	
//	filenames = filenames+"\\";
	CTime t = CTime::GetCurrentTime();
	CString filename = dirs1+t.Format("\\%Y%m%d-%H%M%S.jpg");
     /*
     * 把屏幕内容保存为一个 HBITMAP DDB
     */
     HDC hScrnDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
     HDC hMemDC = CreateCompatibleDC(hScrnDC);
 
     // 获取屏幕分辨率
     int xScrn = GetDeviceCaps(hScrnDC, HORZRES);
     int yScrn = GetDeviceCaps(hScrnDC, VERTRES);
	if( xScrn == 1024 && yScrn >720 )
	{
		xScrn=xScrn*1.3;
		yScrn = yScrn*1.3;
	}
	else if( xScrn == 1344 && yScrn >800 )
	{
		xScrn=xScrn*1.3;
		yScrn = yScrn*1.3;
	}
	else if( xScrn == 1536 && yScrn >800 )
	{
		xScrn=xScrn*1.3;
		yScrn = yScrn*1.3;
	}
    // 创建位图,并选中
      HBITMAP hScrnBmp = CreateCompatibleBitmap(hScrnDC, xScrn, yScrn);
      SelectObject(hMemDC, hScrnBmp);
 
      // 复制屏幕内容
     BitBlt(hMemDC, 0, 0, xScrn, yScrn, hScrnDC, 0, 0, SRCCOPY);
  
      // 现在得到了一个 HBITMAP DDB - hScrnBmp
  
      /*
      * 通过 hScrnBmp DDB 取得 DIB 数据
      */
      // 获取色深 JPG 只能处理 24 位色,所以不管当前系统设置的色深是多少,我们都要求 GetDIBits 函数返回 24 位的 DIB 数据,同时也不需要调色板
      //int colorDeepBits = GetDeviceCaps(hScrnBmp, BITSPIXEL);
      //if(colorDeepBits > 24) colorDeepBits = 24;
      int colorDeepBits = 24;
  
      // 每行像素占用的字节数,每行要对齐4字节.
     int imageRowSize = (xScrn * colorDeepBits + 31) / 32 * 4; 
 
      // 分配 DIB 数组
      unsigned char* dibBuffer = new unsigned char[imageRowSize * yScrn];
//      assert(dibBuffer);
      memset(dibBuffer, 0, imageRowSize * yScrn);    // 清零是个好习惯    
  
      // 填充 BMP 信息头
      BITMAPINFO bmi = {0};
      bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bmi.bmiHeader.biWidth = xScrn;
      bmi.bmiHeader.biHeight = yScrn * -1;        // JPG 压缩需要正序的 DIB 像素流,所以要负数.
      bmi.bmiHeader.biPlanes = 1;
      bmi.bmiHeader.biBitCount = colorDeepBits;
      bmi.bmiHeader.biCompression = BI_RGB;
  
      // 获取 DIB 像素数组(DIB_RGB_COLORS 表示获取 RGB 值而不是调色板索引,当然24位位图也没有调色板)
      int gdiRet = GetDIBits(hMemDC, hScrnBmp, 0, yScrn, dibBuffer, &bmi, DIB_RGB_COLORS);
//      assert(gdiRet == yScrn);
   //   assert(bmi.bmiHeader.biSizeImage == imageRowSize * yScrn);
  
      // DIB 数据已经获取,所有的 GDI 对象可以释放了.
      DeleteDC(hScrnDC);
      DeleteDC(hMemDC);
      DeleteObject(hScrnBmp);
 
        // DIB 中颜色的存放顺序是 BGR, 而 JPG 要求的顺序是 RGB, 所以要交换 R 和 B.
      // 由于有行对齐因素,所以逐行处理
      for(int row = 0; row < yScrn; ++row)
      {
          unsigned char* rowData = dibBuffer + imageRowSize * row;
          for(int col = 0; col < xScrn * 3; col += 3)
          {
              unsigned char swap = rowData[col];
              rowData[col] = rowData[col + 2];
              rowData[col + 2] = swap;
          }
      }
  
      //把位图数据压缩为 jpeg
      struct jpeg_compress_struct cinfo;
      struct jpeg_error_mgr jerr;
      FILE * outfile;        /* target file */
      JSAMPROW row_pointer[1];    /* pointer to JSAMPLE row[s] */
      int row_stride;        /* physical row width in image buffer */
      int image_width = xScrn;
      int image_height = yScrn;
      JSAMPLE* image_buffer = dibBuffer;                    // DIB buffer
      int image_buffer_len = imageRowSize * image_height;    // DIB buffer 长度
	  outfile = fopen(filename, "w+b");
     // if(fopen( filename, "wb"))
      //if ((outfile = fopen_s(filename, "wb")) == NULL) 
  //   if( fopen(filename, "w+b"))
  //    {
  //        fprintf(stderr, "can't open %s\n", filename);
//		AfxMessageBox("can't open .\n");
 //        // assert(0);
 //     }
 //     else
     {
         /* Step 1: allocate and initialize JPEG compression object */
         cinfo.err = jpeg_std_error(&jerr);
 
         /* Now we can initialize the JPEG compression object. */
         jpeg_create_compress(&cinfo);
 
         /* Step 2: specify data destination (eg, a file) */
         /* Note: steps 2 and 3 can be done in either order. */
         jpeg_stdio_dest(&cinfo, outfile);

         /* Step 3: set parameters for compression */
 
         /* First we supply a description of the input image.
          * Four fields of the cinfo struct must be filled in:
          */
         cinfo.image_width = image_width;     /* image width and height, in pixels */
         cinfo.image_height = image_height;
         cinfo.input_components = 3;        /* # of color components per pixel */ // 因为DIB数据是24位的,所以每个像素占用3个字节
         cinfo.in_color_space = JCS_RGB;     /* colorspace of input image */
         /* Now use the library's routine to set default compression parameters.
         * (You must set at least cinfo.in_color_space before calling this,
          * since the defaults depend on the source color space.)
          */
         jpeg_set_defaults(&cinfo);
        /* Now you can set any non-default parameters you wish to.
          * Here we just illustrate the use of quality (quantization table) scaling:
         */
        jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

         /* Step 4: Start compressor */

       /* TRUE ensures that we will write a complete interchange-JPEG file.
          * Pass TRUE unless you are very sure of what you're doing.
          */
         jpeg_start_compress(&cinfo, TRUE);

         /* Step 5: while (scan lines remain to be written) */
         /*           jpeg_write_scanlines(); */
 
        /* Here we use the library's state variable cinfo.next_scanline as the
          * loop counter, so that we don't have to keep track ourselves.
          * To keep things simple, we pass one scanline per call; you can pass
         * more if you wish, though.
          */
         row_stride = imageRowSize;
         while (cinfo.next_scanline < cinfo.image_height) 
         {
            /* jpeg_write_scanlines expects an array of pointers to scanlines.
              * Here the array is only one element long, but you could pass
              * more than one scanline at a time if that's more convenient.
              */
             row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
            //row_pointer[0] = &image_buffer[image_buffer_len - (cinfo.next_scanline + 1) * row_stride];
             (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
         }
 
         /* Step 6: Finish compression */
         jpeg_finish_compress(&cinfo);
 
         /* After finish_compress, we can close the output file. */
         fclose(outfile);
         
        /* Step 7: release JPEG compression object */
         /* This is an important step since it will release a good deal of memory. */
         jpeg_destroy_compress(&cinfo);
     }

     // 释放 DIB 数组
     delete []dibBuffer;
//	 AfxMessageBox("save jpeg ok.\n");
    return 0;
 }



