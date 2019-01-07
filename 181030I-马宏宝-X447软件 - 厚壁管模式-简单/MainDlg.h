#if !defined(AFX_MAINDLG_H__A0255CAF_EB1A_4A60_8191_9C60A57F5C39__INCLUDED_)
#define AFX_MAINDLG_H__A0255CAF_EB1A_4A60_8191_9C60A57F5C39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MainDlg dialog
#include "Waveshow.h"
#include "enmuHead.h"	// Added by ClassView
#include "StaticPic.h"
#include "adcard.h"
#define WM_MyNotify WM_USER+100

/*
 *	采集分析主对话框类
 */
class MainDlg : public CDialog
{
// Construction
public:
	float m_menxianzhi;
	void UpdateMinPly();
	void Statistic();
	void EnableBlockButtons(BOOL n);
	void updateFileMsg();
	void reSetPage();
	BOOL m_bIsCapturing;
	MainDlg(CWnd* pParent = NULL);   // standard constructor
void ReadlvboToFile(CString strFileName);
// Dialog Data
	//{{AFX_DATA(MainDlg)
	enum { IDD = IDD_DIALOG_MAIN };
	CStatic	m_staticLEN;
	CStatic	m_staticMinPly;
	CEdit	m_conMinPly;
	CStatic	m_staticPosition;
	CEdit	m_conPosition;
	CStaticPIC	m_conStatic9;
	CStatic	m_StaticPly;
	CEdit	m_conPlyValue;
	CButton	m_conPrint;
	CStaticPIC	m_conStatic8;
	CStaticPIC	m_conStatic7;
	CStaticPIC	m_conStatic6;
	CStaticPIC	m_conStatic5;
	CStaticPIC	m_conStatic4;
	CStaticPIC	m_conStatic3;
	CStaticPIC	m_conStatic2;
	CStaticPIC	m_conStatic1;
	CButton	m_conBiostatus;
	CListBox	m_conEmsg;
	CStatic	m_staticTitle8;
	CStatic	m_staticTitle7;
	CStatic	m_staticTitle6;
	CStatic	m_staticTitle5;
	CStatic	m_staticTitle4;
	CStatic	m_staticTitle3;
	CStatic	m_staticTitle2;
	CStatic	m_staticTitle1;
	CButton	m_conBwaven;
	CButton	m_conBwavepp;
	CButton	m_conBwavep;
	CButton	m_conBwavenn;
	CEdit	m_conEcurrentnum;
	CButton	m_conBallpp;
	CButton	m_conBallp;
	CButton	m_conBallnn;
	CButton	m_conBalln;
	CStatic	m_conSgonum;
	CButton	m_conBgonum;
	CButton	m_conBdataset;
	CButton	m_conBanalysis;
	CButton	m_conBreshow;
	CButton	m_conBhistorydata;
	CProgressCtrl	m_conProgress;
	CEdit	m_conEhelp;
	CButton	m_conBstop;
	CButton	m_conBstart;
	CButton	m_conBshowset;
	CButton	m_conBreport;
	CButton	m_conBdemocrate;
	CButton	m_conBparset;
	CButton	m_conBdatabase;
	CButton	m_conBcardset;
	int		m_iCurrentNum;
	CString	m_strPlyValue;
	CString	m_strPosition;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	int save_screen_to_jpeg();

	// Generated message map functions
	//{{AFX_MSG(MainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonShowset();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonCardset();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonDemocrate();
	afx_msg void OnButtonParset();
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuitemFirstc();
	afx_msg void OnMenuitemNextc();
	afx_msg void OnMenuitemPrec();
	afx_msg void OnButtonDatasaveset();
	afx_msg void OnButtonOpen();
	afx_msg void OnBUTTON1p();
	afx_msg void OnBUTTON1n();
	afx_msg void OnBUTTON2p();
	afx_msg void OnBUTTON2n();
	afx_msg void OnBUTTON3p();
	afx_msg void OnBUTTON3n();
	afx_msg void OnBUTTON4p();
	afx_msg void OnBUTTON4n();
	afx_msg void OnBUTTON5p();
	afx_msg void OnBUTTON5n();
	afx_msg void OnBUTTON6p();
	afx_msg void OnBUTTON6n();
	afx_msg void OnBUTTON7p();
	afx_msg void OnBUTTON7n();
	afx_msg void OnBUTTON8p();
	afx_msg void OnBUTTON8n();
	afx_msg void OnBUTTONpp1();
	afx_msg void OnBUTTONpp2();
	afx_msg void OnBUTTONpp3();
	afx_msg void OnBUTTONpp4();
	afx_msg void OnBUTTONpp5();
	afx_msg void OnBUTTONpp6();
	afx_msg void OnBUTTONpp7();
	afx_msg void OnBUTTONpp8();
	afx_msg void OnBUTTONallpp();
	afx_msg void OnBUTTONallp();
	afx_msg void OnButtonGonum();
	afx_msg void OnBUTTONalln();
	afx_msg void OnBUTTONallnn();
	afx_msg void OnButtonReshow();
	afx_msg void OnBUTTONwavepp();
	afx_msg void OnBUTTONwavep();
	afx_msg void OnBUTTONwaven();
	afx_msg void OnBUTTONwavenn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBUTTONnn1();
	afx_msg void OnBUTTONnn2();
	afx_msg void OnBUTTONnn3();
	afx_msg void OnBUTTONnn4();
	afx_msg void OnBUTTONnn5();
	afx_msg void OnBUTTONnn6();
	afx_msg void OnBUTTONnn7();
	afx_msg void OnBUTTONnn8();
	afx_msg void OnCombine();
	afx_msg void OnSimple();
	afx_msg void OnButtonAnalysis();
	afx_msg void OnFault();
	afx_msg void OnButtonIostatus();
	afx_msg void OnButtonReport();
	afx_msg void OnButtonDatabase();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnButtonSprent();
	afx_msg void OnDiffer();
	afx_msg void OnPhase();
	afx_msg void OnPly();
	afx_msg void OnDifference();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnThickPipe();
	//}}AFX_MSG
	void OnMyNotify(WPARAM wParam, LPARAM lParam);
	LRESULT SampleMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DlgNewMsg(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void Draw(HDC hDC, HBITMAP hBmp, int iX, int iY, double dScaleX, double dScaleY, int iWidth, int iLength);
	HBITMAP GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight);
	BOOL sendCommand(COPYDATASTRUCT& cds);
	int selnumforFloordata;
	BOOL CheckforOtherProcess();
	CBitmap memBitmap;
	CDC memDC;
	BOOL autoControl;
	void showFileHead(BOOL isStart ,BOOL clear = FALSE);
	void saveWaveStye(WaveShowStyle s, int id);
	void updataWaveShow();
	void showAverageData(int id, int page);
	void ChangeShowBlock();
	void doGetWholeData();
	void EnableWaveButtons(BOOL n);
	void pageButton(int num,ButtonFlag flag);
	int pointInWave;    //0~7环境菜单位置
	void RefreshWave();
	void setStatus(Status s);
	void myInit();
	void showWaveBlock(int ix, int iy, int ex, int ey);
	int pnButtons[4][8];
	int dy;
	int dx;
	int dyanniu;
	CWaveShow* waveshow[8];
	CWaveShow* statisticShow;
	CStaticPIC* StaticShow[8];  //使用双缓存画图此处才有效
	CStatic* titles[8];
	CRect waverect[8];
	CRect statisticrRect;
	void DlgShowInit();
	int DlgAllButton[5];
	int AllWaveButton[4];
	Status oldstatus;  //辅助标志
	int dataOpenMode;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__A0255CAF_EB1A_4A60_8191_9C60A57F5C39__INCLUDED_)
