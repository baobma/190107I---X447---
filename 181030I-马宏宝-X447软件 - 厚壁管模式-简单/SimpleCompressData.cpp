// SimpleCompressData.cpp: implementation of the SimpleCompressData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "SimpleCompressData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "GobalData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SimpleCompressData::SimpleCompressData()
{
    compress = 100;
	suffix = "scd";
}

SimpleCompressData::~SimpleCompressData()
{

}

BOOL SimpleCompressData::savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len, CSampleCard* card, int id)
{
    GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	CTime t = CTime::GetCurrentTime();
	int ch = card->getChannelNum();
	int datasum = ch*buf->getdataLens(0)*sizeof(short)/compress + sizeof(BLOCKHEAD) + sizeof(ch); //单块总数据量
	
	file->Write(&datasum,sizeof(int));  //写入单块总长度
	//
	bHead->hour = t.GetHour();
	bHead->min  = t.GetMinute();
	bHead->good = g->goodflag;
	bHead->blocksum = buf->getdataLens(0)/compress;
	bHead->id = id;
	file->Write(bHead,sizeof(BLOCKHEAD));
    //写单块头

	//
	file->Write(&ch,sizeof(ch));    //通道数
	//写当前风格特有信息

	//写数据
    for(int i = 0; i < ch; i++)  //从第0通道开始，根据采集卡的通道数量保存数据
	{
		WORD** data = buf->getDataPtr();
		int len = buf->getdataLens(i);
		for(int j = 0; j < len; j += compress)
		{
			short y = getSaveNum(buf,i,j,compress);
            file->Write(&y,sizeof(short));
		}
	}
	file->Write(&datasum,sizeof(int));  //写入单块总长度
	len = datasum;                      //返回值
    return TRUE;
}

BOOL SimpleCompressData::loadPerBlockData(CFile *file, BLOCKHEAD* bHead, int& len)
{
    GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	int ch;
	int datasum;
	
	file->Read(&datasum,sizeof(int));  //读单块总长度
	
	//
	file->Read(bHead,sizeof(BLOCKHEAD));
    //读单块头
	
	//
	file->Read(&ch,sizeof(int));    //通道数
	//读当前风格特有信息
	
	//读数据
    for(int i = 0; i < ch; i++)  //从第0通道开始，根据通道数量读取数据
	{
		WORD** data = buf->getDataPtr();
		short d  = 0;
		for(int j = 0; j < bHead->blocksum * compress; j++)
		{
			if(j%compress == 0)
		        file->Read(&d,sizeof(short));
            data[i][j] = d;	 
		}

		buf->setDataLens(i,bHead->blocksum * compress);
	}
	file->Read(&datasum,sizeof(int));  //读单块总长度
	len = datasum;
	
    return TRUE;
}

void SimpleCompressData::getShowWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf)
{
	int max = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
		y = abs(y);
		if(i == startNum)
			max = y;
		if(y > max)
			max = y;
	}
    max = max >  2048 ? 2048 : max;
	max = max < 0 ? 0 : max;
    reBuf = max;
}

void SimpleCompressData::getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf)
{
    int max = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	max = (data[startch][startNum] - stdline[startch])*pars[startch]/100;
	max = abs(max);
	for(int ch = startch; ch <= startch + chnum; ch++)
	{
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
			y = abs(y);
			if(y > max)
				max = y;
		}
	}
    max = max >  2048 ? 2048 : max;
	max = max < 0 ? 0 : max;
    reBuf = max;
}

/*
 *	压缩存储
 */
short SimpleCompressData::getSaveNum(DataBuf *buf, int ch, int startNum, int blocklen)
{
	int max = 0;
	short re = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		int y = (data[ch][i] - stdline[ch]);
		y = abs(y);
		if(i == startNum)
		{
			max = y;
			re = data[ch][i];
		}
	    if(y > max)
		{
	        max = y;
			re = data[ch][i];
		}
	}
    return re;
}

void SimpleCompressData::DoReport(CListCtrl& list, BOOL doexcel)
{

}

void SimpleCompressData::DoDataBase()
{

}

BOOL SimpleCompressData::autoSampleFuc()
{
    return TRUE;
}

BOOL SimpleCompressData::getDateFromCard()
{
	GobalData* g = GobalData::getGobalData();
	RbhUsb20* usbcard = (RbhUsb20*)TestSampleControl::cardPtr;

	return g->getDataFromCard8221(usbcard->getADbuf(),usbcard->getADbuf1());
}

void SimpleCompressData::endSampleData()
{

}

void SimpleCompressData::GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void SimpleCompressData::GetWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void SimpleCompressData::GetMinWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void SimpleCompressData::GetAvgWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}
