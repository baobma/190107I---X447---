// ARDSET.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "ARDSET.h"
#include "GobalData.h"
#include "TestFuc.h"
#include "TestSampleControl.h"
#include "GobalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "TestFuc.h"

/////////////////////////////////////////////////////////////////////////////
// CARDSET dialog


CARDSET::CARDSET(CWnd* pParent /*=NULL*/)
	: CDialog(CARDSET::IDD, pParent)
{
	//{{AFX_DATA_INIT(CARDSET)
	m_iBlock = 0;
	m_iChannelNum = 0;
	m_iSampleSpeed = 0;
	m_bCoding = FALSE;
	m_iStartCH = 0;
	//}}AFX_DATA_INIT
}


void CARDSET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CARDSET)
	DDX_Control(pDX, IDC_STATIC_STARTCH, m_sStartCH);
	DDX_Control(pDX, IDC_EDIT_SYSTEMSTARTCH, m_eCH);
	DDX_Control(pDX, IDC_CHECK_CODING, m_cbCoding);
	DDX_Control(pDX, IDC_STATIC_SAMPLESPEED, m_sSampleSpeed);
	DDX_Control(pDX, IDC_STATIC_CHANNELNUM, m_sChannelNum);
	DDX_Control(pDX, IDC_STATIC_BLOCK, m_sBlock);
	DDX_Control(pDX, IDC_EDIT_SAMPLESPEED, m_eSampleSpeed);
	DDX_Control(pDX, IDC_EDIT_CHANNELNUM, m_eChannelNum);
	DDX_Control(pDX, IDC_EDIT_BLOCK, m_eBlock);
	DDX_Control(pDX, IDC_COMBO_CARDCHOOSE, m_conCardChoose);
	DDX_Text(pDX, IDC_EDIT_BLOCK, m_iBlock);
	DDX_Text(pDX, IDC_EDIT_CHANNELNUM, m_iChannelNum);
	DDX_Text(pDX, IDC_EDIT_SAMPLESPEED, m_iSampleSpeed);
	DDX_Check(pDX, IDC_CHECK_CODING, m_bCoding);
	DDX_Text(pDX, IDC_EDIT_SYSTEMSTARTCH, m_iStartCH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CARDSET, CDialog)
	//{{AFX_MSG_MAP(CARDSET)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CARDSET message handlers

BOOL CARDSET::OnInitDialog() 
{
	CDialog::OnInitDialog();

	RECT Client_Size;
	GetClientRect(&Client_Size);	
	dx = Client_Size.right/20;
	dy = Client_Size.bottom/20;
    char DrvName[36];
	 int i;
	CString m_strADResult;
   //����λ���ж�ȡ�忨�����ƣ�AD�����ֵ���������
	ConfigInfo(DrvName,&i,&i,&i,&i,&VZero,&VMax,&i);
	m_strADResult.Format("��������Ϊ: %s",DrvName);// 
	
	m_conCardChoose.MoveWindow(20,20,150,20);
    m_conCardChoose.AddString(m_strADResult);
	m_conCardChoose.SetCurSel(0);

	setParDlg();
	return TRUE;
}

void CARDSET::OnPaint() 
{
// 	CPaintDC dc(this);
// 	
// 	CPen yellowPen(PS_SOLID,2,RGB(220,255,220));
// 	CBrush yellowBrush(RGB(220,255,220));
// 	CGdiObject* systemPen   = NULL;
// 	CGdiObject* systemBrush = NULL;
// 	CGdiObject* org         = NULL;
// 	systemPen = dc.SelectObject(&yellowBrush);
// 	systemBrush = dc.SelectObject(&yellowPen);
//     dc.Rectangle(7*dx,0*dy,8*dx,25*dy);
// 
// 	org = dc.SelectObject(systemPen);
// 	org->DeleteObject();
// 	org = dc.SelectObject(systemBrush);
// 	org->DeleteObject();



	// Do not call CDialog::OnPaint() for painting messages
}

/*
 *	�ɼ�����������ͼ����
 */
void CARDSET::setParDlg()
{
    UpdateData();
	switch(m_conCardChoose.GetCurSel()) 
	{
	case 0:
		{
            m_sSampleSpeed.MoveWindow(9*dx,2*dy,4*dx,2*dy);
			m_eSampleSpeed.MoveWindow(13*dx,int(1.5*dy),4*dx,2*dy);
			m_sBlock.MoveWindow(9*dx,5*dy,4*dx,2*dy);
			m_eBlock.MoveWindow(13*dx,int(4.5*dy),4*dx,2*dy);
			m_sChannelNum.MoveWindow(9*dx,8*dy,4*dx,2*dy);
			m_eChannelNum.MoveWindow(13*dx,int(7.5*dy),4*dx,2*dy);
			m_sStartCH.MoveWindow(9*dx,11*dy,4*dx,2*dy);
			m_eCH.MoveWindow(13*dx,int(10.5*dy),4*dx,2*dy);
			m_cbCoding.MoveWindow(9*dx,13*dy,4*dx,2*dy);

			GobalData* g = GobalData::getGobalData();
			USB8221par par = g->getUsb8221Par();
	        	m_iStartCH = par.startch;
			m_iChannelNum = par.channelnum;
			m_iBlock = par.block;
			m_iSampleSpeed = par.samplespeed;
			m_bCoding = par.coding;
		}
		break;
	case 1:
		{

		}
		break;
	}

	UpdateData(FALSE);

}

void CARDSET::OnOK() 
{
	UpdateData();
    switch(m_conCardChoose.GetCurSel())
	{
    case 0:  //USB8221
		{
			GobalData* g = GobalData::getGobalData();

            		USB8221par par;
			//ͨ���������ܳ���128
			par.channelnum = (m_iChannelNum > 136 ? 136 : m_iChannelNum); 
			par.block = m_iBlock;
			par.samplespeed = (m_iSampleSpeed > 500 ? 500 : m_iSampleSpeed);  //��������
			par.coding = m_bCoding;                                           //�Ƿ�ʹ�ñ����� TRUE ʹ��

			if(m_iStartCH + par.channelnum > g->MAXCHANNEL)  //��ʼͨ������С��0
				par.startch = 0;
			else
			    par.startch = m_iStartCH;
			
			g->set8221par(par);                        //���ò�����8221�ɼ�������
			USB8221par p = g->getUsb8221Par();

			DeletePtr(TestSampleControl::cardPtr);
			//����װ�زɼ�������
			TestSampleControl::cardPtr =                      
				new RbhUsb20(this->cardWnd, p.samplespeed, p.channelnum, p.block);
		}
    	break;
    case 1:
    	break;
    }	
	CDialog::OnOK();
}
