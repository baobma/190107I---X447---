// WaveShow.h: interface for the CWaveShow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVESHOW_H__1A15DEBF_BFA4_48CA_931A_D75C66ED0F56__INCLUDED_)
#define AFX_WAVESHOW_H__1A15DEBF_BFA4_48CA_931A_D75C66ED0F56__INCLUDED_

#include "enmuHead.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
 *	波形显示块类
 */
class CWaveShow  
{
public:
   	float m_menxianzhi;
	short getDiffer();
	void ReadlvboToFile(CString strFileName);
	void setDiffer(short i);
	short getDifferAdjust();
	void setDifferAdjust(short i);
	short getTimeLapes();
	void setTimeLapes(short i);
	void DrawDifference(CDC *pdc, int startch, int endch, int blocklen,int dataOpenMode);
	void DrawPly(CDC *pdc, int startch, int endch, int blocklen);
	void DrawWavePhase(CDC *pdc, int startch, int endch, int blocklen);
	void DrawDifferWave(CDC *pdc, int startch, int endch, int blocklen,int dataOpenMode);
	short getShowCompress();
	void setShowCompress(short i);
	void setHalfShow(BOOL h);
	BOOL ishalfshow();
	void DrawWaveFaultBackEx(CDC* pDC);
	void DrawWave_blockEx(CDC* pdc,int startch, int endch, int blocklen, BOOL fault,int dataOpenMode);
	void DrawBackEx(CDC* pdc,BOOL IsCombine);
	CWnd* getWnd();
	void DrawWave_combineEx(CDC *pdc,int startch, int endch, int blocklen,int dataOpenMode);
	void setAlertLine2(short a);
	short getAlertLine2();
	void setAlertLine3(short a);
	short getAlertLine3();
	void aotuToCurrentPage(int i);
	void DrawWaveFaultBack(CDC *pdc);//缺陷显示风格背景
	void setRestrainY(short r);   
	int GetAverageMaxofCHS(int startch, int endch, int blocklen, int ch,int start, int end );
    int GetAverageMaxofCHS2(int startch, int endch, int blocklen, int ch,int start, int end );
	void DrawWave_combine(int startch, int endch, int blocklen);//波形融合显示风格
	WaveShowStyle getWaveShowStyle();
	void setWaveStyle(WaveShowStyle s);
	int getScreenPage();
	void DrawWave_block(int startch, int endch, int blocklen,BOOL fault); //波形简单显示风格
	void setxMax(int xMax);
	void setPage(int p);
	void setAlertLine(short a);
	short getAlertLine();
	void setAlertyPar();

	//用于获取动态增益调整时，横向和纵向的报警上下限
	float getVertAlertyParH();
	float getVertAlertyParL();
	float getHoriAlertyParH();
	float getHoriAlertyParL();

	void resetScreen();
	void preScreen();
	void nextScreen();
	void setStep(int s);
	float getCurrentPosition(int ch);          //取得当前数据底部在窗口的位置 0~1
	int getStep();
	int getyMax();
	int getxMax();
	void DrawBack(CDC* pdc,int k[21]);
	CWaveShow(CWnd* pWnd,const int xMax, const int yMax);
	virtual ~CWaveShow();
//	BOOL  Caijiwan;
private:
		int differadjust;
	int differ;
	int timelapes;
	int blockcompress;
	 WaveShowStyle wavestyle;  //显示风格
	 int screenPage;           //屏数
	 short alertLine;          //报警线
	 short alertLine2;
	 short alertLine3;
     int step;                 //步长
	 short restrainY;  //抑制比
	 CWnd* Wndshow;    //显示块对应的窗口
	 int xMax;         //x轴逻辑点数
	 int yMax;         //y轴逻辑点数
	 BOOL half;        //半部分显示方式
// 	 int aflag;
// 	 int bflag;
	 int alerty1;
	 int alerty1_shangxian;
     int alerty1_xiaxian;
	 int alerty2;
	 int alerty2_shangxian;
	 int alerty2_xiaxian;
//	 BOOL thickPipe_flag;
};

#endif // !defined(AFX_WAVESHOW_H__1A15DEBF_BFA4_48CA_931A_D75C66ED0F56__INCLUDED_)
