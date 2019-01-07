// SimpleDataSave.h: interface for the SimpleDataSave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEDATASAVE_H__F32488B6_8D6E_4091_BDB2_D4B5F7F80587__INCLUDED_)
#define AFX_SIMPLEDATASAVE_H__F32488B6_8D6E_4091_BDB2_D4B5F7F80587__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSaveStyle.h"

class SimpleDataSave : public DataSaveStyle  
{
public:
	void GetDifferWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
	void GetAvgWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetMinWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
	void getShowWaveNum3(DataBuf *buf, int ch, int startNum, int blocklen,int &reBuf);
	void endSampleData();
	BOOL getDateFromCard();
	BOOL autoSampleFuc();
	void DoDataBase();
	void DoReport(CListCtrl& list, BOOL doexcel);
	void getShowWaveNum(DataBuf* buf, int startch, int endch, int blocklen, int timelapes, int& reBuf);
	void getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	BOOL loadPerBlockData(CFile* file, BLOCKHEAD *bHead, int& len);
	BOOL savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len, CSampleCard* card, int id);
	SimpleDataSave();
	virtual ~SimpleDataSave();int ldata[32][100];
};

#endif // !defined(AFX_SIMPLEDATASAVE_H__F32488B6_8D6E_4091_BDB2_D4B5F7F80587__INCLUDED_)
