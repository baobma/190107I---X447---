// ScarData.h: interface for the CScarData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCARDATA_H__2D8D413D_9A68_4E93_B0A8_A8EAADDF73AA__INCLUDED_)
#define AFX_SCARDATA_H__2D8D413D_9A68_4E93_B0A8_A8EAADDF73AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSaveStyle.h"

enum L82SCARSTATUS
{
	L82SCARSTATUS_STOP,
	L82SCARSTATUS_HORIZONTAL, 
	L82SCARSTATUS_BOTH,
	L82SCARSTATUS_HORIZONTAL_VERTICAL1,
	L82SCARSTATUS_VERTICAL2,
	L82SCARSTATUS_VERTICAL1_VERTICAL2,
	L82SCARSTATUS_DEMARCATE
};

class CScarData : public DataSaveStyle
{
public:
	void GetDifferWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
	void GetAvgWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetMinWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
//	void GetFaultNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int &reBuf);
	void endSampleData();
	BOOL loadPerBlockData(CFile* file, BLOCKHEAD* bHead, int& len);
	BOOL savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len,CSampleCard* card, int id);
	void getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void getShowWaveNum(DataBuf* buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf);
	void getShowWaveNum3(DataBuf *buf, int ch, int startNum, int blocklen,int &reBuf);
	void VendgetShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void DoDataBase();
	void DoReport(CListCtrl& list, BOOL doexcel);
	BOOL autoSampleFuc();
	BOOL getDateFromCard();
	void AlertSet();//报警参数设置
	static BOOL alertflag;
	static char alertSingle1;
	static char alertSingle2;
	L82SCARSTATUS l82ScarStatus;

	CScarData();
	virtual ~CScarData();
private:
	short getSaveNum(DataBuf *buf, int ch, int startNum, int blocklen);
    	 int vtck1;
	 int vtck2;
	 int htck1;
	 int htck2;
	 int alerty1;
	// int alerty1_shangxian;
	 int alerty1_xiaxian;
	 int alerty2;
	// int alerty2_shangxian;
	 int alerty2_xiaxian;
	 int alert1_num;//用来消除连续报警
	 int alert2_num;

	 WaveShowStyle alertbyshow1;
	 WaveShowStyle alertbyshow2;
};

#endif // !defined(AFX_SCARDATA_H__2D8D413D_9A68_4E93_B0A8_A8EAADDF73AA__INCLUDED_)
