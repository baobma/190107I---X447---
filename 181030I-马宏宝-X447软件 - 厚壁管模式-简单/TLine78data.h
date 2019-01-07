// TLine78data.h: interface for the CTLine78data class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLINE78DATA_H__6020C22B_1E40_4AB2_9DF8_6F256BCF932C__INCLUDED_)
#define AFX_TLINE78DATA_H__6020C22B_1E40_4AB2_9DF8_6F256BCF932C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSaveStyle.h"
#include "RbhUsb20.h"

enum TL78STATUS
{
	    TL78STATUS_STATUS0,   //未采集
		TL78STATUS_STATUS1,   //仅横向
		TL78STATUS_STATUS2,   //横向+纵向
		TL78STATUS_STATUS3,   //仅纵向
		TL78STATUS_STATUS_DEMOCRATE  //标定
};
class CTLine78data : public DataSaveStyle  
{
public:
	void GetAvgWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetMinWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
	static char alertSingle;
	static BOOL alertflag;
	void endSampleData();
	TL78STATUS tl78status;
	BOOL loadPerBlockData(CFile* file, BLOCKHEAD* bHead, int& len);
	BOOL savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len,CSampleCard* card, int id);
	void getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void getShowWaveNum(DataBuf* buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf);
	void DoDataBase();
	void DoReport(CListCtrl& list, BOOL doexcel);
	BOOL autoSampleFuc();
	BOOL getDateFromCard();
	CTLine78data();
	virtual ~CTLine78data();

private:
	short getSaveNum(DataBuf *buf, int ch, int startNum, int blocklen);
};

#endif // !defined(AFX_TLINE78DATA_H__6020C22B_1E40_4AB2_9DF8_6F256BCF932C__INCLUDED_)
