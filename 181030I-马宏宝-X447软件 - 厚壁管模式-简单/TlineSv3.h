// TlineSv3.h: interface for the CTlineSv3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLINESV3_H__E1712A62_1C07_4FDE_8324_0B0C0AD72D6E__INCLUDED_)
#define AFX_TLINESV3_H__E1712A62_1C07_4FDE_8324_0B0C0AD72D6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSaveStyle.h"
#include "SimpleCompressData.h"
#include "RbhUsb20.h"

enum TLSV3STATUS
{
	TLSV3STATUS_STATUS0,    //未采集
	TLSV3STATUS_STATUS1,    //在采集
	TLSV3STATUS_STATUS2,    //采集刚结束
	TLSV3STATUS_DEMOCRATE
};
class CTlineSv3 : public SimpleCompressData  
{
public:
	void GetAvgWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetMinWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
	void getShowWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf);
	void getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
    static char alertSingle;
	static BOOL alertflag;
	TLSV3STATUS tlsv3status;
	BOOL loadPerBlockData(CFile* file, BLOCKHEAD* bHead, int& len);
	BOOL savePerBlockData(CFile* file, BLOCKHEAD* bHead, int& len,CSampleCard* card, int id);
	void DoDataBase();
	void DoReport(CListCtrl& list, BOOL doexcel);
	BOOL autoSampleFuc();
	BOOL getDateFromCard();
	CTlineSv3();
	virtual ~CTlineSv3();
    void endSampleData();
private:
	void setParsforSV3();
	int endDataLen;
};

#endif // !defined(AFX_TLINESV3_H__E1712A62_1C07_4FDE_8324_0B0C0AD72D6E__INCLUDED_)
