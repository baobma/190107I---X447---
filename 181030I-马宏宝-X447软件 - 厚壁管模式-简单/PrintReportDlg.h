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
	//报告的尺寸
	REPORT_POSITION Size;
	//"报告的标题"位置
	REPORT_POSITION CaptionPos;
	//"报告的下横线"
	REPORT_POSITION UnderLinePos;
	//"规格"位置
	REPORT_POSITION TubeSpePos;
	//"设备型号"位置
	REPORT_POSITION EquipmentModelPos;
	//"执行标准"位置
	REPORT_POSITION StandardPos;
	//"文件名"位置
	REPORT_POSITION DataNamPos;
	//钢级的位置
	REPORT_POSITION SteelGradePos;
	//标称壁厚的位置
	REPORT_POSITION  NominalWallPos;
	//"检测的总根数"位置
	REPORT_POSITION TotalNumPos;
	//"报废总根数"位置
	REPORT_POSITION TotalFlawPos;
	//一级钻杆总根数的位置
	REPORT_POSITION LevelOnePos;
	//二级钻杆总根数的位置
	REPORT_POSITION LevelTwoPos;
	//"缺陷油管的号码" 位置
	REPORT_POSITION FlawNumPos;
	//"检测员"位置
	REPORT_POSITION DetectMan;
	//"检测日期"位置
	REPORT_POSITION InspectDate;
	//审核的位置
	REPORT_POSITION AuditingPos;
	//资质证号的位置
	REPORT_POSITION CardNumPos;
	//建议栏的位置
	REPORT_POSITION AdvicePos;
	//"当前管号"位置
	REPORT_POSITION CurrentTubeNum;
	//边框的起始位置
	REPORT_POSITION RectBeginPos;
	//边框的结束位置
	REPORT_POSITION RectEndPos;
	
	//杆号的位置
	REPORT_POSITION DrillPipeNumPos;
	//产品序号的位置
	REPORT_POSITION ProductSequenceNumPos;
	//横向的位置
	REPORT_POSITION CrossPos;
	//重量的位置
	REPORT_POSITION WeightPos;
	//评定级别的位置
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
