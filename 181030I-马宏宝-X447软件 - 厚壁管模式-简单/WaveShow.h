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
 *	������ʾ����
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
	void DrawWaveFaultBack(CDC *pdc);//ȱ����ʾ��񱳾�
	void setRestrainY(short r);   
	int GetAverageMaxofCHS(int startch, int endch, int blocklen, int ch,int start, int end );
    int GetAverageMaxofCHS2(int startch, int endch, int blocklen, int ch,int start, int end );
	void DrawWave_combine(int startch, int endch, int blocklen);//�����ں���ʾ���
	WaveShowStyle getWaveShowStyle();
	void setWaveStyle(WaveShowStyle s);
	int getScreenPage();
	void DrawWave_block(int startch, int endch, int blocklen,BOOL fault); //���μ���ʾ���
	void setxMax(int xMax);
	void setPage(int p);
	void setAlertLine(short a);
	short getAlertLine();
	void setAlertyPar();

	//���ڻ�ȡ��̬�������ʱ�����������ı���������
	float getVertAlertyParH();
	float getVertAlertyParL();
	float getHoriAlertyParH();
	float getHoriAlertyParL();

	void resetScreen();
	void preScreen();
	void nextScreen();
	void setStep(int s);
	float getCurrentPosition(int ch);          //ȡ�õ�ǰ���ݵײ��ڴ��ڵ�λ�� 0~1
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
	 WaveShowStyle wavestyle;  //��ʾ���
	 int screenPage;           //����
	 short alertLine;          //������
	 short alertLine2;
	 short alertLine3;
     int step;                 //����
	 short restrainY;  //���Ʊ�
	 CWnd* Wndshow;    //��ʾ���Ӧ�Ĵ���
	 int xMax;         //x���߼�����
	 int yMax;         //y���߼�����
	 BOOL half;        //�벿����ʾ��ʽ
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
