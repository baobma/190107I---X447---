#if !defined(AFX_PRINTREPORTDLG_H__1D434F64_52CE_4B2C_BBA2_0CE637DAB239__INCLUDED_)
#define AFX_PRINTREPORTDLG_H__1D434F64_52CE_4B2C_BBA2_0CE637DAB239__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintReportDlg.h : header file
//
typedef struct 
{
	int x;
	int y;
}REPORT_POSITION;

typedef struct 
{
	//����ĳߴ�
	REPORT_POSITION Size;
	//"����ı���"λ��
	REPORT_POSITION CaptionPos;
	//"������º���"
	REPORT_POSITION UnderLinePos;
	//"���"λ��
	REPORT_POSITION TubeSpePos;
	//"�豸�ͺ�"λ��
	REPORT_POSITION EquipmentModelPos;
	//"ִ�б�׼"λ��
	REPORT_POSITION StandardPos;
	//"�ļ���"λ��
	REPORT_POSITION DataNamPos;
	//�ּ���λ��
	REPORT_POSITION SteelGradePos;
	//��Ʊں��λ��
	REPORT_POSITION  NominalWallPos;
	//"�����ܸ���"λ��
	REPORT_POSITION TotalNumPos;
	//"�����ܸ���"λ��
	REPORT_POSITION TotalFlawPos;
	//һ������ܸ�����λ��
	REPORT_POSITION LevelOnePos;
	//��������ܸ�����λ��
	REPORT_POSITION LevelTwoPos;
	//"ȱ���͹ܵĺ���" λ��
	REPORT_POSITION FlawNumPos;
	//"���Ա"λ��
	REPORT_POSITION DetectMan;
	//"�������"λ��
	REPORT_POSITION InspectDate;
	//��˵�λ��
	REPORT_POSITION AuditingPos;
	//����֤�ŵ�λ��
	REPORT_POSITION CardNumPos;
	//��������λ��
	REPORT_POSITION AdvicePos;
	//"��ǰ�ܺ�"λ��
	REPORT_POSITION CurrentTubeNum;
	//�߿����ʼλ��
	REPORT_POSITION RectBeginPos;
	//�߿�Ľ���λ��
	REPORT_POSITION RectEndPos;
	
	//�˺ŵ�λ��
	REPORT_POSITION DrillPipeNumPos;
	//��Ʒ��ŵ�λ��
	REPORT_POSITION ProductSequenceNumPos;
	//�����λ��
	REPORT_POSITION CrossPos;
	//������λ��
	REPORT_POSITION WeightPos;
	//���������λ��
	REPORT_POSITION  LevelPos;
}POSITIONOFREPORT;
/////////////////////////////////////////////////////////////////////////////
// PrintReportDlg dialog

class PrintReportDlg : public CDialog
{
// Construction
public:
	PrintReportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PrintReportDlg)
	enum { IDD = IDD_DIALOG_PRINTREPORT };
	CButton	m_UpPage;
	CButton	m_NextPage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PrintReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void GetInfo();
	
	HICON m_hIcon;
	CRect m_bitmapRect;
	float rato;
	POSITIONOFREPORT PositionOfReport;
	int nTotalPrintPage;
	int nCurPrintPage;
	short levelOne;
	short levelTwo;
	short levelThree;
	// Generated message map functions
	//{{AFX_MSG(PrintReportDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPrintall();
	afx_msg void OnButtonPrintcurrent();
	afx_msg void OnButtonUppage();
	afx_msg void OnButtonNextpage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL Draw(CDC *pDC, CRect *bitmapRect, int Printpage);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTREPORTDLG_H__1D434F64_52CE_4B2C_BBA2_0CE637DAB239__INCLUDED_)
