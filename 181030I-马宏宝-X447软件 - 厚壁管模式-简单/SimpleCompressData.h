// SimpleCompressData.h: interface for the SimpleCompressData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLECOMPRESSDATA_H__E5EE069C_E481_483C_A887_3A5864B7FBE0__INCLUDED_)
#define AFX_SIMPLECOMPRESSDATA_H__E5EE069C_E481_483C_A887_3A5864B7FBE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSaveStyle.h"

class SimpleCompressData : public DataSaveStyle  
{
public:
	void GetAvgWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetMinWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	void GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf);
	void endSampleData();
	BOOL getDateFromCard();
	BOOL autoSampleFuc();
	void DoDataBase();
	void DoReport(CListCtrl& list, BOOL doexcel);
	short getSaveNum(DataBuf* buf,int ch, int startNum,int blockNum);
	virtual void getShowWaveNum(DataBuf* buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf);
	virtual void getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf);
	BOOL loadPerBlockData(CFile* file, BLOCKHEAD *bHead, int& len);
	BOOL savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len, CSampleCard* card, int id);
	SimpleCompressData();
	virtual ~SimpleCompressData();

};

#endif // !defined(AFX_SIMPLECOMPRESSDATA_H__E5EE069C_E481_483C_A887_3A5864B7FBE0__INCLUDED_)
