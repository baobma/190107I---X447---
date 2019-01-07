// PlyData.h: interface for the CPlyData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLYDATA_H__2BB1076C_5E5E_49E9_BBD9_0F2E158EEA72__INCLUDED_)
#define AFX_PLYDATA_H__2BB1076C_5E5E_49E9_BBD9_0F2E158EEA72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSaveStyle.h"

enum L82PLYSTATUS
{
	L82PLYSTATUS_STOP,
	L82PLYSTATUS_START,  //
	L82PLYSTATUS_DEMARCATE
};

class CPlyData : public DataSaveStyle 
{
public:
		void GetDifferWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
	void GetAvgWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetMinWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
	void endSampleData();
	BOOL loadPerBlockData(CFile* file, BLOCKHEAD* bHead, int& len);
	BOOL savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len,CSampleCard* card, int id);
	void getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void getShowWaveNum(DataBuf* buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf);
	void getShowWaveNum3(DataBuf *buf, int ch, int startNum, int blocklen,int &reBuf);
	void DoDataBase();
	void DoReport(CListCtrl& list, BOOL doexcel);
	BOOL autoSampleFuc();
	BOOL getDateFromCard();
	static char alertSingle;
	static BOOL alertflag;
	L82PLYSTATUS l82PlyStatus;
	//	int ldata[32][100];
	CPlyData();
	virtual ~CPlyData();
private:
	short getSaveNum(DataBuf *buf, int ch, int startNum, int blocklen);
	
};

#endif // !defined(AFX_PLYDATA_H__2BB1076C_5E5E_49E9_BBD9_0F2E158EEA72__INCLUDED_)
