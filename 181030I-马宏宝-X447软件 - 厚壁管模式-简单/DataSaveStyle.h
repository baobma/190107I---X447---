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
 *	数据保存风格抽象类
 */
class DataSaveStyle  
{
public:
	virtual void endSampleData() = 0;  //采集完成后数据调整
	BOOL IsNeedTrigger();
	int getCompress();
	virtual BOOL getDateFromCard() = 0;  //从采集卡数据缓存读去数据
	virtual BOOL autoSampleFuc() = 0;    //自动采集函数  true为可以退出
	virtual void DoReport(CListCtrl& list, BOOL doexcel) = 0;
	virtual void DoDataBase() = 0;
	/*
	 *	取得单显示数值
	 */
	virtual void getShowWaveNum(DataBuf* buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf) = 0;
	/*
	 *	取得单通道连续点平均值，焊缝识别
	 */
	virtual void getShowWaveNum3(DataBuf *buf, int ch, int startNum, int blocklen, int &reBuf)=0;
	
	/*
	 *	取得融合显示数值
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
	 *	保存单块数据文件
	 *  file :文件指针
	 *  len  :返回单块数据总量
	 *  card :采集卡指针
	 *  id   :单块编号
	 */
	virtual BOOL savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len,CSampleCard* card, int id) = 0;   //保存一段数据块
	/*
	 *	读取单块数据
	 *  file: 文件指针
	 *  bHead: 单块头返回指针
	 *  len  : 返回单块数据总量
	 */
	virtual BOOL loadPerBlockData(CFile* file, BLOCKHEAD* bHead, int& len) = 0;   //读取一段数据块
	virtual ~DataSaveStyle();
	DataSaveStyle();
protected:
	BOOL needTrigger;  //是否需要触发采集
	int compress;      //数据压缩比   -1为非定长压缩
	char* suffix;      //文件名后缀
	int blockNum;
};

#endif // !defined(AFX_DATASAVESTYLE_H__DB1C1F3B_4A02_4F73_BC96_002FE17D998D__INCLUDED_)
