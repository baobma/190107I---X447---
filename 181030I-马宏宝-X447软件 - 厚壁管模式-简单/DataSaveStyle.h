// DataSaveStyle.h: interface for the DataSaveStyle class.
//
//////////////////////////////////////////////////////////////////////
#include "SampleCard.h"
#include "TestFuc.h"
#include "DataBuf.h"
#include "RbhUsb20.h"
#include "TestSampleControl.h"

#if !defined(AFX_DATASAVESTYLE_H__DB1C1F3B_4A02_4F73_BC96_002FE17D998D__INCLUDED_)
#define AFX_DATASAVESTYLE_H__DB1C1F3B_4A02_4F73_BC96_002FE17D998D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
 *	���ݱ����������
 */
class DataSaveStyle  
{
public:
	virtual void endSampleData() = 0;  //�ɼ���ɺ����ݵ���
	BOOL IsNeedTrigger();
	int getCompress();
	virtual BOOL getDateFromCard() = 0;  //�Ӳɼ������ݻ����ȥ����
	virtual BOOL autoSampleFuc() = 0;    //�Զ��ɼ�����  trueΪ�����˳�
	virtual void DoReport(CListCtrl& list, BOOL doexcel) = 0;
	virtual void DoDataBase() = 0;
	/*
	 *	ȡ�õ���ʾ��ֵ
	 */
	virtual void getShowWaveNum(DataBuf* buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf) = 0;
	/*
	 *	ȡ�õ�ͨ��������ƽ��ֵ������ʶ��
	 */
	virtual void getShowWaveNum3(DataBuf *buf, int ch, int startNum, int blocklen, int &reBuf)=0;
	
	/*
	 *	ȡ���ں���ʾ��ֵ
	 */
	virtual void getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf) = 0;
		virtual void GetDifferWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf) = 0;
	virtual void GetMinWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf) = 0;
	virtual void GetAvgWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf) = 0;
	
	virtual void GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf) = 0;

	virtual void GetWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf) = 0;
	//virtual void GetThickPipeNum()

	virtual char* getSuffix();
	/*
	 *	���浥�������ļ�
	 *  file :�ļ�ָ��
	 *  len  :���ص�����������
	 *  card :�ɼ���ָ��
	 *  id   :������
	 */
	virtual BOOL savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len,CSampleCard* card, int id) = 0;   //����һ�����ݿ�
	/*
	 *	��ȡ��������
	 *  file: �ļ�ָ��
	 *  bHead: ����ͷ����ָ��
	 *  len  : ���ص�����������
	 */
	virtual BOOL loadPerBlockData(CFile* file, BLOCKHEAD* bHead, int& len) = 0;   //��ȡһ�����ݿ�
	virtual ~DataSaveStyle();
	DataSaveStyle();
protected:
	BOOL needTrigger;  //�Ƿ���Ҫ�����ɼ�
	int compress;      //����ѹ����   -1Ϊ�Ƕ���ѹ��
	char* suffix;      //�ļ�����׺
	int blockNum;
};

#endif // !defined(AFX_DATASAVESTYLE_H__DB1C1F3B_4A02_4F73_BC96_002FE17D998D__INCLUDED_)
