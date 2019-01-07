// DataSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "DataSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "GobalData.h"
/////////////////////////////////////////////////////////////////////////////
// DataSetDlg dialog


DataSetDlg::DataSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DataSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DataSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DataSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DataSetDlg)
	DDX_Control(pDX, IDC_COMBO_DATASET, m_conBoxDataSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DataSetDlg, CDialog)
	//{{AFX_MSG_MAP(DataSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DataSetDlg message handlers

BOOL DataSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GobalData* g = GobalData::getGobalData();
	m_conBoxDataSet.AddString("�궨����(ord)");
//	m_conBoxDataSet.AddString("��ѹ������(scd)");
//	m_conBoxDataSet.AddString("Tline78data(d78)");
//	m_conBoxDataSet.AddString("TlineSv3data(sv3)");
//	m_conBoxDataSet.AddString("ԭʼ�ȿռ�����(srs)");
//	m_conBoxDataSet.AddString("���޵װ���(flr)");
	m_conBoxDataSet.AddString("�ֹ��Զ����(emt)");
//	m_conBoxDataSet.AddString("�͹ܼ������(vmm)");
	int index = g->getSaveStyle();
	m_conBoxDataSet.SetCurSel(index);
	return TRUE;
}

void DataSetDlg::OnOK() 
{
	UpdateData();
	GobalData* g = GobalData::getGobalData();
	switch(m_conBoxDataSet.GetCurSel())
	{
	case SimpleData:     g->setSaveStyle(SimpleData);
		break;
// 	case SimpleCopData:  g->setSaveStyle(SimpleCopData);
// 		break;
//	case Testline78data:    g->setSaveStyle(Testline78data);
//		break;
//	case TestlineSv3data:   g->setSaveStyle(TestlineSv3data);
//		break;
//	case SRoomSampledata: g->setSaveStyle(SRoomSampledata);
//		break;
//	case Floordata: g->setSaveStyle(Floordata);
//		break;
 	case ExploreScarData:  g->setSaveStyle(ExploreScarData);
 		break;
//	case ExplorePlyData:   g->setSaveStyle(ExplorePlyData);
//		break;
	}
	CDialog::OnOK();
}
