// PrintReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "hustndt.h"
#include "PrintReportDlg.h"
#include "GobalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PrintReportDlg dialog


PrintReportDlg::PrintReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PrintReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(PrintReportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PrintReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PrintReportDlg)
	DDX_Control(pDX, IDC_BUTTON_UPPAGE, m_UpPage);
	DDX_Control(pDX, IDC_BUTTON_NEXTPAGE, m_NextPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PrintReportDlg, CDialog)
	//{{AFX_MSG_MAP(PrintReportDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_PRINTALL, OnButtonPrintall)
	ON_BN_CLICKED(IDC_BUTTON_PRINTCURRENT, OnButtonPrintcurrent)
	ON_BN_CLICKED(IDC_BUTTON_UPPAGE, OnButtonUppage)
	ON_BN_CLICKED(IDC_BUTTON_NEXTPAGE, OnButtonNextpage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PrintReportDlg message handlers

void PrintReportDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	// TODO: Add your message handler code here
	CDC *pDC;
	pDC=GetDC();

	rato=float(m_bitmapRect.right-m_bitmapRect.left)/PositionOfReport.Size.x;
	m_bitmapRect.bottom=m_bitmapRect.top+int(PositionOfReport.Size.y*rato);
	Draw(pDC,&m_bitmapRect,nCurPrintPage);
}

BOOL PrintReportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// 	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	// 	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	//	TUBEINFO.m_TubeNumber=TubeNo;
	//	TubeNumPrint=1
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	// 	if (pSysMenu != NULL)
	// 	{
	// 		CString strAboutMenu;
	// 		strAboutMenu.LoadString(IDS_ABOUTBOX);
	// 		if (!strAboutMenu.IsEmpty())
	// 		{
	// 			pSysMenu->AppendMenu(MF_SEPARATOR);
	// 			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	// 		}
	// 	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRect rect;
	GetClientRect(&rect);
	//	ScreenToClient(&rect);
	
	m_bitmapRect.left=rect.left;
	m_bitmapRect.right=rect.right;
	m_bitmapRect.top=rect.top;
	//    char strCurSamplesFileName1[300]="";
/*	nTotalFlawNum=0;*/
	nCurPrintPage=1;
	nTotalPrintPage=1;
	levelOne = 0;
	levelTwo = 0;
	levelThree = 0;
 	GetInfo();
	m_UpPage.EnableWindow(FALSE);
	if(nTotalPrintPage>1)
	{
		m_NextPage.EnableWindow(TRUE);
	}
	else
		m_NextPage.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL PrintReportDlg::Draw(CDC *pDC, CRect *bitmapRect, int Printpage)
{
	GobalData* g = GobalData::getGobalData();
	DATAHEAD dHead = g->dataHead;
	CFont font100,font140,font160,font200,*pOldFont;
	CPen pen1,pen2,*pOldPen;
	CRect rect;
	int i;
	CString str1,str2,str3,str4,str5;
	char str6[50];
	
	if (!pDC->IsPrinting())
	{
		pDC->SetWindowOrg(0,0);
		pDC->SetViewportOrg(bitmapRect->left,bitmapRect->top);
		
		pDC->SetBkMode(OPAQUE);//���ñ���ģʽ �� ��͸��
		pDC->SetBkColor(RGB(255,255,255));//����ɫΪ��ɫ
		//���λͼ
		pDC->FillSolidRect(0,0,bitmapRect->Width(),bitmapRect->Height(),RGB(255,255,255));
	}
	pDC->SetTextColor(RGB(0,0,0));//����������ɫ
	pen2.CreatePen(PS_SOLID,2,RGB(0,0,0));//��������
	
    //������������
	font100.CreatePointFont(110,_T("����_GB2312"),pDC);	
	font140.CreatePointFont(140,_T("����_GB2312"),pDC);
	font160.CreatePointFont(160,_T("����_GB2312"),pDC);
	font200.CreatePointFont(200,_T("����_GB2312"),pDC);
	//�������
	pen1.CreatePen(PS_SOLID,1,RGB(0,0,0));//��������
    pOldPen = pDC->SelectObject(&pen2);//ѡ�뻭��
	pDC->Rectangle(int(28*rato),int(28*rato),int(180*rato),int(267*rato));
	pDC->SelectObject(pOldPen);
	
	pOldPen = pDC->SelectObject(&pen1);//ѡ�뻭��
	
	for(i=0;i<19;i++)
	{	
		pDC->MoveTo(int(28*rato),int((40+12*i)*rato));
		pDC->LineTo(int(180*rato),int((40+12*i)*rato));
	}
	
	pDC->MoveTo(int(104*rato),int(28*rato));
	pDC->LineTo(int(104*rato),int(52*rato));
 	
	pDC->MoveTo(int(68*rato),int(52*rato));
	pDC->LineTo(int(68*rato),int(76*rato));
	
	pDC->MoveTo(int(109*rato),int(52*rato));
	pDC->LineTo(int(109*rato),int(76*rato));

	pDC->MoveTo(int(66*rato),int(76*rato));
	pDC->LineTo(int(66*rato),int(88*rato));
	
	pDC->MoveTo(int(104*rato),int(76*rato));
	pDC->LineTo(int(104*rato),int(88*rato));
	
	pDC->MoveTo(int(142*rato),int(76*rato));
	pDC->LineTo(int(142*rato),int(88*rato));
	
	pDC->MoveTo(int(66*rato),int(88*rato));
	pDC->LineTo(int(66*rato),int(267*rato));
	
	pDC->MoveTo(int(104*rato),int(88*rato));
	pDC->LineTo(int(104*rato),int(267*rato));
	
	pDC->MoveTo(int(142*rato),int(88*rato));
	pDC->LineTo(int(142*rato),int(267*rato));
	
// 	pDC->MoveTo(int(150*rato),int(88*rato));
// 	pDC->LineTo(int(150*rato),int(267*rato));
	
// 	pDC->MoveTo(int(142*rato),int(76*rato));
// 	pDC->LineTo(int(142*rato),int(88*rato));


	pDC->SelectObject(pOldPen);	
	//����
	pOldFont = pDC->SelectObject(&font200);//ѡ������
	
    pOldPen = pDC->SelectObject(&pen2);//ѡ�뻭��
	
	rect.left=int((PositionOfReport.CaptionPos.x)*rato);
	rect.top=int((PositionOfReport.CaptionPos.y)*rato);
	rect.right=int((PositionOfReport.CaptionPos.x+120)*rato);
	rect.bottom=int((PositionOfReport.CaptionPos.y+25)*rato);
	pDC->DrawText("��˵��̽�˼���񱨱�",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	
	pDC->SelectObject(pOldFont);

	//�ļ���
	pOldFont = pDC->SelectObject(&font100);//ѡ������
	rect.left=int((PositionOfReport.DataNamPos.x)*rato);
	rect.top=int((PositionOfReport.DataNamPos.y)*rato);
	rect.right=int((PositionOfReport.DataNamPos.x+27)*rato);
	rect.bottom=int((PositionOfReport.DataNamPos.y+10)*rato);
	pDC->DrawText("�ļ�����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);	
	rect.left=int((PositionOfReport.DataNamPos.x+30)*rato);
	rect.right=int((PositionOfReport.DataNamPos.x+76)*rato);
	pDC->DrawText(g->getWholeFileName(),-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//�豸�ͺ�
	rect.left=int((PositionOfReport.EquipmentModelPos.x)*rato);
	rect.top=int((PositionOfReport.EquipmentModelPos.y)*rato);
	rect.right=int((PositionOfReport.EquipmentModelPos.x+74)*rato);
	rect.bottom=int((PositionOfReport.EquipmentModelPos.y+10)*rato);
	pDC->DrawText("�豸�ͺţ�EMT-D60/140",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);	

	//ִ�б�׼
	rect.left=int((PositionOfReport.StandardPos.x)*rato);
	rect.top=int((PositionOfReport.StandardPos.y)*rato);
	rect.right=int((PositionOfReport.StandardPos.x+74)*rato);
	rect.bottom=int((PositionOfReport.StandardPos.y+10)*rato);
	pDC->DrawText("ִ�б�׼��GB/T12606-1999",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//�������
	rect.left=int((PositionOfReport.InspectDate.x)*rato);	
	rect.top=int((PositionOfReport.InspectDate.y)*rato);
	rect.right=int((PositionOfReport.InspectDate.x+35)*rato);
	rect.bottom=int((PositionOfReport.InspectDate.y+10)*rato);
	pDC->DrawText("������ڣ�",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	str1.Format("%4d��%02d��%02d��",dHead.year,dHead.month,dHead.day);
	rect.left=int((PositionOfReport.InspectDate.x+35)*rato);
	rect.right=int((PositionOfReport.InspectDate.x+75)*rato);
	pDC->DrawText(str1,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//���
	rect.left=int((PositionOfReport.TubeSpePos.x)*rato);
	rect.top=int((PositionOfReport.TubeSpePos.y)*rato);
	rect.right=int((PositionOfReport.TubeSpePos.x+20)*rato);
	rect.bottom=int((PositionOfReport.TubeSpePos.y+10)*rato);	
	pDC->DrawText("���",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	rect.left=int((PositionOfReport.TubeSpePos.x+20)*rato);
	rect.right=int((PositionOfReport.TubeSpePos.x+40)*rato);
	str1.Format("��%s",dHead.guige);
	pDC->DrawText(str1,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//�ּ�
	rect.left=int((PositionOfReport.SteelGradePos.x)*rato);
	rect.top=int((PositionOfReport.SteelGradePos.y)*rato);
	rect.right=int((PositionOfReport.SteelGradePos.x+20)*rato);
	rect.bottom=int((PositionOfReport.SteelGradePos.y+10)*rato);	
	pDC->DrawText("�ּ���",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	rect.left=int((PositionOfReport.SteelGradePos.x+20)*rato);
	rect.right=int((PositionOfReport.SteelGradePos.x+40)*rato);
	pDC->DrawText(dHead.steel,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//��Ʊں�
	rect.left=int((PositionOfReport.NominalWallPos.x)*rato);
	rect.top=int((PositionOfReport.NominalWallPos.y)*rato);
	rect.right=int((PositionOfReport.NominalWallPos.x+35)*rato);
	rect.bottom=int((PositionOfReport.NominalWallPos.y+10)*rato);	
	pDC->DrawText("��Ʊں�",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	rect.left=int((PositionOfReport.NominalWallPos.x+35)*rato);
	rect.right=int((PositionOfReport.NominalWallPos.x+70)*rato);
	str1.Format("%s mm",dHead.ply);
	pDC->DrawText(str1,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//���
	rect.left=int((PositionOfReport.AuditingPos.x)*rato);
	rect.top=int((PositionOfReport.AuditingPos.y)*rato);
	rect.right=int((PositionOfReport.AuditingPos.x+20)*rato);
	rect.bottom=int((PositionOfReport.AuditingPos.y+10)*rato);	
	pDC->DrawText("��ˣ�",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//����Ա
	rect.left=int((PositionOfReport.DetectMan.x)*rato);
	rect.top=int((PositionOfReport.DetectMan.y)*rato);
	rect.right=int((PositionOfReport.DetectMan.x+26)*rato);
	rect.bottom=int((PositionOfReport.DetectMan.y+10)*rato);	
	pDC->DrawText("����Ա��",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	rect.left=int((PositionOfReport.DetectMan.x+20)*rato);
	rect.right=int((PositionOfReport.DetectMan.x+40)*rato);
	pDC->DrawText(dHead.Uoperator,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//����֤��
	rect.left=int((PositionOfReport.CardNumPos.x)*rato);
	rect.top=int((PositionOfReport.CardNumPos.y)*rato);
	rect.right=int((PositionOfReport.CardNumPos.x+35)*rato);
	rect.bottom=int((PositionOfReport.CardNumPos.y+10)*rato);	
	pDC->DrawText("����֤�ţ�",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//����ܸ���
	rect.left=int((PositionOfReport.TotalNumPos.x)*rato);
	rect.top=int((PositionOfReport.TotalNumPos.y)*rato);
	rect.right=int((PositionOfReport.TotalNumPos.x+28)*rato);
	rect.bottom=int((PositionOfReport.TotalNumPos.y+10)*rato);	
	pDC->DrawText("�ܸ�����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	str1.Format("%d",dHead.blocksum);
	rect.left=int((PositionOfReport.TotalNumPos.x+28)*rato);
	rect.right=int((PositionOfReport.TotalNumPos.x+38)*rato);
	pDC->DrawText(str1,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//һ������	
	rect.left=int((PositionOfReport.LevelOnePos.x)*rato);
	rect.top=int((PositionOfReport.LevelOnePos.y)*rato);
	rect.right=int((PositionOfReport.LevelOnePos.x+28)*rato);
	rect.bottom=int((PositionOfReport.LevelOnePos.y+10)*rato);	
	pDC->DrawText("һ����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	str1.Format("%d",levelOne);
	rect.left=int((PositionOfReport.LevelOnePos.x+28)*rato);
	rect.right=int((PositionOfReport.LevelOnePos.x+38)*rato);
	pDC->DrawText(str1,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//��������
	rect.left=int((PositionOfReport.LevelTwoPos.x)*rato);
	rect.top=int((PositionOfReport.LevelTwoPos.y)*rato);
	rect.right=int((PositionOfReport.LevelTwoPos.x+28)*rato);
	rect.bottom=int((PositionOfReport.LevelTwoPos.y+10)*rato);	
	pDC->DrawText("������",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	str1.Format("%d",levelTwo);
	rect.left=int((PositionOfReport.LevelTwoPos.x+28)*rato);
	rect.right=int((PositionOfReport.LevelTwoPos.x+38)*rato);
	pDC->DrawText(str1,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//���ϸ���
	rect.left=int((PositionOfReport.TotalFlawPos.x)*rato);
	rect.top=int((PositionOfReport.TotalFlawPos.y)*rato);
	rect.right=int((PositionOfReport.TotalFlawPos.x+28)*rato);
	rect.bottom=int((PositionOfReport.TotalFlawPos.y+10)*rato);	
	pDC->DrawText("������",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	str1.Format("%d",levelThree);
	rect.left=int((PositionOfReport.TotalFlawPos.x+28)*rato);
	rect.right=int((PositionOfReport.TotalFlawPos.x+38)*rato);
	pDC->DrawText(str1,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//���
	rect.left=int((PositionOfReport.DrillPipeNumPos.x)*rato);
	rect.top=int((PositionOfReport.DrillPipeNumPos.y)*rato);
	rect.right=int((PositionOfReport.DrillPipeNumPos.x+38)*rato);
	rect.bottom=int((PositionOfReport.DrillPipeNumPos.y+10)*rato);	
	pDC->DrawText("���",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

// 	//��Ʒ���
// 	rect.left=int((PositionOfReport.ProductSequenceNumPos.x)*rato);
// 	rect.top=int((PositionOfReport.ProductSequenceNumPos.y)*rato);
// 	rect.right=int((PositionOfReport.ProductSequenceNumPos.x+30)*rato);
// 	rect.bottom=int((PositionOfReport.ProductSequenceNumPos.y+10)*rato);	
// 	pDC->DrawText("��Ʒ���",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//����
	rect.left=int((PositionOfReport.CrossPos.x)*rato);
	rect.top=int((PositionOfReport.CrossPos.y)*rato);
	rect.right=int((PositionOfReport.CrossPos.x+38)*rato);
	rect.bottom=int((PositionOfReport.CrossPos.y+10)*rato);	
	pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//����
	rect.left=int((PositionOfReport.WeightPos.x)*rato);
	rect.top=int((PositionOfReport.WeightPos.y)*rato);
	rect.right=int((PositionOfReport.WeightPos.x+38)*rato);
	rect.bottom=int((PositionOfReport.WeightPos.y+10)*rato);	
	pDC->DrawText("���",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//��������
	rect.left=int((PositionOfReport.LevelPos.x)*rato);
	rect.top=int((PositionOfReport.LevelPos.y)*rato);
	rect.right=int((PositionOfReport.LevelPos.x+38)*rato);
	rect.bottom=int((PositionOfReport.LevelPos.y+10)*rato);	
	pDC->DrawText("��������",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	for(i=0;i<14;i++)
	{
		if(i>dHead.blocksum-1-(Printpage-1)*14)
		{
			break;
		}
		str1.Format("%d",i+1+(Printpage-1)*14);
		rect.left=int((PositionOfReport.DrillPipeNumPos.x)*rato);
		rect.top=int((PositionOfReport.DrillPipeNumPos.y+12*i+12)*rato);
		rect.right=int((PositionOfReport.DrillPipeNumPos.x+38)*rato);
		rect.bottom=int((PositionOfReport.DrillPipeNumPos.y+10+12*i+12)*rato);
		pDC->DrawText(str1,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		
		
		rect.left=int((PositionOfReport.CrossPos.x)*rato);
		rect.top=int((PositionOfReport.CrossPos.y+12*i+12)*rato);
		rect.right=int((PositionOfReport.CrossPos.x+38)*rato);
		rect.bottom=int((PositionOfReport.CrossPos.y+10+12*i+12)*rato);
		if (dHead.grade[i+(Printpage-1)*14] == 0)
		{
			pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		}
		if (dHead.grade[i+(Printpage-1)*14] == 2)
		{
			pDC->DrawText("һ��",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		}
		if (dHead.grade[i+(Printpage-1)*14] == 1)
		{
			pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		}
		
		rect.left=int((PositionOfReport.WeightPos.x)*rato);
		rect.top=int((PositionOfReport.WeightPos.y+12*i+12)*rato);
		rect.right=int((PositionOfReport.WeightPos.x+38)*rato);
		rect.bottom=int((PositionOfReport.WeightPos.y+10+12*i+12)*rato);
		if (dHead.wgrade[i+(Printpage-1)*14] == 0)
		{
			pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		}
		if (dHead.wgrade[i+(Printpage-1)*14] == 2)
		{
			pDC->DrawText("һ��",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		}
		if (dHead.wgrade[i+(Printpage-1)*14] == 1)
		{
			pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		}

		rect.left=int((PositionOfReport.LevelPos.x)*rato);
		rect.top=int((PositionOfReport.LevelPos.y+12*i+12)*rato);
		rect.right=int((PositionOfReport.LevelPos.x+38)*rato);
		rect.bottom=int((PositionOfReport.LevelPos.y+10+12*i+12)*rato);
		if (dHead.wgrade[i+(Printpage-1)*14]>=dHead.grade[i+(Printpage-1)*14])
		{
			if (dHead.grade[i+(Printpage-1)*14] == 0)
			{
				pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
			}
			if (dHead.grade[i+(Printpage-1)*14] == 2)
			{
				pDC->DrawText("һ��",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
			}
			if (dHead.grade[i+(Printpage-1)*14] == 1)
			{
				pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
			}
		}
		if (dHead.grade[i+(Printpage-1)*14]>dHead.wgrade[i+(Printpage-1)*14])
		{
			if (dHead.wgrade[i+(Printpage-1)*14] == 0)
			{
				pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
			}
			if (dHead.wgrade[i+(Printpage-1)*14] == 2)
			{
				pDC->DrawText("һ��",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
			}
			if (dHead.wgrade[i+(Printpage-1)*14] == 1)
			{
				pDC->DrawText("����",-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
			}
		}
		
		
// 		
// 		str3.Format("%.0f",fault[1+2*i+2*(Printpage-1)*14]);
// 		rect.left=int((PositionOfReport.BrokeNumPos.x)*rato);
// 		rect.top=int((PositionOfReport.BrokeNumPos.y+12*i+12)*rato);
// 		rect.right=int((PositionOfReport.BrokeNumPos.x+38)*rato);
// 		rect.bottom=int((PositionOfReport.BrokeNumPos.y+10+12*i+12)*rato);
// 		pDC->DrawText(str3,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
// 		
// 		str4.Format("%d",nNianJuBrokeRope[i+(Printpage-1)*14]);
// 		rect.left=int((PositionOfReport.NianJuNumPos.x)*rato);
// 		rect.top=int((PositionOfReport.NianJuNumPos.y+12*i+12)*rato);
// 		rect.right=int((PositionOfReport.NianJuNumPos.x+38)*rato);
// 		rect.bottom=int((PositionOfReport.NianJuNumPos.y+10+12*i+12)*rato);
// 		pDC->DrawText(str4,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);		
	}
	
	
	rect.left=int(140*rato);	
	rect.top=int(270*rato);
	rect.right=int(180*rato);
	rect.bottom=int(280*rato);
	
	str5.Format("%d",Printpage);		
	strcpy(str6,"��");
	strcat(str6,str5);
	strcat(str6,"ҳ ��");
	str5.Format("%d",nTotalPrintPage);
	strcat(str6,str5);
	strcat(str6,"ҳ");
	
	pDC->DrawText(str6,-1,&rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	pDC->SelectObject(pOldPen);//ѡ������

	return TRUE;
}

void PrintReportDlg::GetInfo()
{

	GobalData* g = GobalData::getGobalData();
	DATAHEAD dHead = g->dataHead;
	//��������ĳߴ�290*210
	PositionOfReport.Size.x=210;
	PositionOfReport.Size.y=297;
	
	//����
	PositionOfReport.CaptionPos.x=45;
	PositionOfReport.CaptionPos.y=5;
	
	PositionOfReport.UnderLinePos.x=30;
	PositionOfReport.UnderLinePos.y=25;
// 	//�ͻ�����
// 	PositionOfReport.TubeSpePos.x=28;
// 	PositionOfReport.TubeSpePos.y=30;
	//�����ļ���
	PositionOfReport.DataNamPos.x=28;
	PositionOfReport.DataNamPos.y=30;
	//�豸�ͺ�
	PositionOfReport.EquipmentModelPos.x=104;
	PositionOfReport.EquipmentModelPos.y=30;
	//ִ�б�׼
	PositionOfReport.StandardPos.x=28;
	PositionOfReport.StandardPos.y=42;
	//�������
	PositionOfReport.InspectDate.x=104;
	PositionOfReport.InspectDate.y=42;
	//���
	PositionOfReport.TubeSpePos.x=28;
	PositionOfReport.TubeSpePos.y=54;
	//�ּ�
	PositionOfReport.SteelGradePos.x=68;
	PositionOfReport.SteelGradePos.y=54;
	//��Ʊں�
	PositionOfReport.NominalWallPos.x=108;
	PositionOfReport.NominalWallPos.y=54;
	//���
	PositionOfReport.AuditingPos.x=28;
	PositionOfReport.AuditingPos.y=66;
	//����Ա
	PositionOfReport.DetectMan.x=68;
	PositionOfReport.DetectMan.y=66;
	//����֤��
	PositionOfReport.CardNumPos.x=108;
	PositionOfReport.CardNumPos.y=66;
	//�ܸ���
	PositionOfReport.TotalNumPos.x=28;
	PositionOfReport.TotalNumPos.y=78;
	//һ������
	PositionOfReport.LevelOnePos.x=66;
	PositionOfReport.LevelOnePos.y=78;
	//��������
	PositionOfReport.LevelTwoPos.x=104;
	PositionOfReport.LevelTwoPos.y=78;
	//���ϸ���
	PositionOfReport.TotalFlawPos.x=142;
	PositionOfReport.TotalFlawPos.y=78;
	//���
	PositionOfReport.DrillPipeNumPos.x=28;
	PositionOfReport.DrillPipeNumPos.y=90;
// 	//��Ʒ���
// 	PositionOfReport.ProductSequenceNumPos.x=58;
// 	PositionOfReport.ProductSequenceNumPos.y=90;
	//����
	PositionOfReport.CrossPos.x=66;
	PositionOfReport.CrossPos.y=90;
	//����
	PositionOfReport.WeightPos.x=104;
	PositionOfReport.WeightPos.y=90;
	//��������
	PositionOfReport.LevelPos.x=142;
	PositionOfReport.LevelPos.y=90;

// 	//����ܳ���
// 	PositionOfReport.TotalNumPos.x=28;
// 	PositionOfReport.TotalNumPos.y=54;
// 	//���
// 	PositionOfReport.TotalFlawPos.x=28;
// 	PositionOfReport.TotalFlawPos.y=66;
// 	//�������
// 	PositionOfReport.FlawNumPos.x=104;
// 	PositionOfReport.FlawNumPos.y=66;
// 	//���
// 	PositionOfReport.SerNumPos.x=28;
// 	PositionOfReport.SerNumPos.y=78;
// 	//��˿λ��
// 	PositionOfReport.BrokePosPos.x=66;
// 	PositionOfReport.BrokePosPos.y=78;
// 	//����
// 	PositionOfReport.BrokeNumPos.x=104;
// 	PositionOfReport.BrokeNumPos.y=78;
// 	//����ڶ�˿����
// 	PositionOfReport.NianJuNumPos.x=142;
// 	PositionOfReport.NianJuNumPos.y=78;
	
	//	��ȡ�������������	
	nTotalPrintPage=(dHead.blocksum-1)/14+1;//ȷ����Ҫ��ӡ����ҳ��

	for (int i = 0; i<dHead.blocksum;i++)
	{
		if (dHead.grade[i]>dHead.wgrade[i])
		{
			if (dHead.wgrade[i]==0)
			{
				levelThree++;
			}
			if (dHead.wgrade[i]==1)
			{
				levelTwo++;
			}
			if (dHead.wgrade[i]==2)
			{
				levelOne++;
			}
		}
		if (dHead.wgrade[i]>=dHead.grade[i])
		{
			if (dHead.grade[i]==0)
			{
				levelThree++;
			}
			if (dHead.grade[i]==1)
			{
				levelTwo++;
			}
			if (dHead.grade[i]==2)
			{
				levelOne++;
			}
		}
	}
}

void PrintReportDlg::OnButtonPrintall() 
{
	// TODO: Add your control notification handler code here
	int PrintPageNum=1;
	CDC dc;
	CPrintDialog printDlg(FALSE);//���ɴ�ӡ���豸����
	if(printDlg.DoModal()==IDCANCEL) // ���û�ѡ���ӡֽ��
		return;
	short printQuality;
	
	printDlg.GetDefaults();
	DEVMODE *dm = printDlg.GetDevMode();
	dm->dmOrientation = DMORIENT_PORTRAIT;
	dm->dmFields|= DM_ORIENTATION;
	printQuality = dm->dmPrintQuality;
	dm->dmPaperSize = NULL;
	dm->dmPaperLength = PositionOfReport.Size.y;
	dm->dmPaperWidth = PositionOfReport.Size.x;
	
	dc.Attach(printDlg.CreatePrinterDC());//��HANDLE���ӵ�dc��
	
	dc.m_bPrinting = TRUE;
	
	CString strTitle;
	strTitle.LoadString(AFX_IDS_APP_TITLE);
	
	DOCINFO di;
	::ZeroMemory(&di,sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = strTitle;
	
	if(dc.StartDoc(&di)==-1)
	{
		MessageBox("StartDoc error");
		return;
	}
	
	int horze = dc.GetDeviceCaps(HORZRES);
	int vertical = dc.GetDeviceCaps(VERTRES);
	
	for(int i=0;i<nTotalPrintPage;i++)
	{
		dc.StartPage();
		rato = float((printQuality)/25.4);
		m_bitmapRect.bottom = m_bitmapRect.top+int(PositionOfReport.Size.y* rato);
		
		Draw(&dc,&m_bitmapRect,PrintPageNum);
		dc.EndPage();
		PrintPageNum++;
	}
	
	dc.EndDoc();
}

void PrintReportDlg::OnButtonPrintcurrent() 
{
	// TODO: Add your control notification handler code here
	CDC dc;
	CPrintDialog printDlg(FALSE);//���ɴ�ӡ���豸����
	if(printDlg.DoModal()==IDCANCEL) // ���û�ѡ���ӡֽ��
		return;
	short printQuality;
	
	printDlg.GetDefaults();
	DEVMODE *dm = printDlg.GetDevMode();
	dm->dmOrientation = DMORIENT_PORTRAIT;
	dm->dmFields|= DM_ORIENTATION;
	printQuality = dm->dmPrintQuality;
	dm->dmPaperSize = NULL;
	dm->dmPaperLength = PositionOfReport.Size.y;
	dm->dmPaperWidth = PositionOfReport.Size.x;
	
	dc.Attach(printDlg.CreatePrinterDC());//��HANDLE���ӵ�dc��
	
	dc.m_bPrinting = TRUE;
	
	CString strTitle;
	strTitle.LoadString(AFX_IDS_APP_TITLE);
	
	DOCINFO di;
	::ZeroMemory(&di,sizeof(DOCINFO));
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = strTitle;
	
	if(dc.StartDoc(&di)==-1)
	{
		MessageBox("StartDoc error");
		return;
	}
	
	int horze = dc.GetDeviceCaps(HORZRES);
	int vertical = dc.GetDeviceCaps(VERTRES);	
	
	dc.StartPage();
	rato = float((printQuality)/25.4);
	m_bitmapRect.bottom = m_bitmapRect.top+int(PositionOfReport.Size.y* rato);
	
	Draw(&dc,&m_bitmapRect,nCurPrintPage);
	dc.EndPage();
	
	dc.EndDoc();
}

void PrintReportDlg::OnButtonUppage() 
{
	// TODO: Add your control notification handler code here
	nCurPrintPage--;
	m_NextPage.EnableWindow(TRUE);
	if(nCurPrintPage==1)
	{
		m_UpPage.EnableWindow(FALSE);		
	}	
	CDC *pDC;
	pDC=GetDC();
	
	rato=float(m_bitmapRect.right-m_bitmapRect.left)/PositionOfReport.Size.x;
	m_bitmapRect.bottom=m_bitmapRect.top+int(PositionOfReport.Size.y*rato);
	
	Draw(pDC,&m_bitmapRect,nCurPrintPage);
}

void PrintReportDlg::OnButtonNextpage() 
{
	// TODO: Add your control notification handler code here
	nCurPrintPage++;
	m_UpPage.EnableWindow(TRUE);
	if(nCurPrintPage>nTotalPrintPage-1)
	{
		m_NextPage.EnableWindow(FALSE);
	}
	//	OnPaint();
	CDC *pDC;
	pDC=GetDC();
	
	rato=float(m_bitmapRect.right-m_bitmapRect.left)/PositionOfReport.Size.x;
	m_bitmapRect.bottom=m_bitmapRect.top+int(PositionOfReport.Size.y*rato);
	
	Draw(pDC,&m_bitmapRect,nCurPrintPage);
}
