// SimpleDataSave.cpp: implementation of the SimpleDataSave class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "SimpleDataSave.h"
#include "GobalData.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern inspect;
//extern caijimodel;
//BOOL alartyy=TRUE;
//long RC_Record1[4];
//static short maxValue,minValue;

SimpleDataSave::SimpleDataSave()
{
	compress = 1;       //压缩比为1
	suffix = "ord";
}

SimpleDataSave::~SimpleDataSave()
{

}

BOOL SimpleDataSave::savePerBlockData(CFile* file, BLOCKHEAD *bHead, int& len, CSampleCard* card, int id)
{
    GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	CTime t = CTime::GetCurrentTime();
	int ch = card->getChannelNum();
	#if( CAIJICARD == 2 )	
		ch = card->getChannelNum()*2;
	#endif
	int datasum = ch*buf->getdataLens(1)*sizeof(short) + sizeof(BLOCKHEAD) + sizeof(ch); //单块总数据量
	
	file->Write(&datasum,sizeof(int));  //写入单块总长度
	//
	bHead->hour = t.GetHour();
	bHead->min  = t.GetMinute();
	bHead->good = g->goodflag;
	bHead->blocksum = buf->getdataLens(1);
	bHead->id = id;
	bHead->xlength =  buf->getdataLens(8);
	bHead->ylength =  buf->getdataLens(88);
	file->Write(bHead,sizeof(BLOCKHEAD));
    //写单块头
	//
	file->Write(&ch,sizeof(ch));    //通道数
	//写当前风格特有信息

	//写数据
    for(int i = 0; i < ch; i++)  //从第0通道开始，根据采集卡的通道数量保存数据
	{
		WORD** data = buf->getDataPtr();
//		if (i==0) 
//		{
//			file->Write(data[i],buf->getdataLens(0)*sizeof(short));  //零通道数据长度一样
//		}
//		else
		file->Write(data[i],buf->getdataLens(1)*sizeof(short));  //各通道数据长度一样
	}
	file->Write(&datasum,sizeof(int));  //写入单块总长度
	len = datasum;                      //返回值
    return TRUE;
}

BOOL SimpleDataSave::loadPerBlockData(CFile *file, BLOCKHEAD* bHead, int& len)
{
    GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	int ch;
	int datasum;
	
	file->Read(&datasum,sizeof(int));  //读单块总长度
	
	//
	file->Read(bHead,sizeof(BLOCKHEAD));
    //读单块头
	if(bHead->xlength==0 )
		bHead->xlength = buf->getdataLens(8);
	if(bHead->ylength==0 )
		bHead->ylength = buf->getdataLens(88);

	//
	file->Read(&ch,sizeof(int));    //通道数
	//读当前风格特有信息
	
	//读数据
    for(int i = 0; i < ch; i++)  //从第0通道开始，根据通道数量读取数据
	{
		WORD** data = buf->getDataPtr();
		file->Read(data[i],bHead->blocksum * sizeof(short));  //各通道数据长度一样
		buf->setDataLens(i,bHead->blocksum);
	}
	file->Read(&datasum,sizeof(int));  //读单块总长度
	len = datasum;
	
    return TRUE;
}

void SimpleDataSave::getShowWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int& reBuf)
{	
       GobalData* g = GobalData::getGobalData();
	int max = -2048;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	if( timelapes > startNum )
		{
			reBuf = 0;
			return ;
		}
	double z = double(pars[ch])/20;
//	z = pow(10,z);
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
	//	int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
			int y = (data[ch][i]- stdline[ch])*pow(10,z)/100;
	//int y = (data[ch][i])*z/100;
		if(i == startNum)
			max = y;
		if(y > max)
			max = y;
	//	if(maxValue < data[ch][i] )  maxValue = y;
	//	if(minValue > data[ch][i] )  minValue = y;
	}

	max = max >  2048 ? 2048 : max;
	max = max <  -2048 ? -2048 : max;
	reBuf = max;
}

void SimpleDataSave::getShowWaveNum3(DataBuf *buf,int ch, int startNum, int blocklen,int &reBuf)
{
	GobalData* g = GobalData::getGobalData();
//	AUTOSET set = g->getAutoSet();
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	int sum = -4096;
	double z = double(pars[ch])/20;
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
	//	int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
		int y = (data[ch][i] - stdline[ch])*pow(10,z)/100;
/*		if(data[ch][i] > 4095)
			y = y+0;
		if(data[ch][i] < 66)
			y = y+0;*/
		if(y > sum )
			sum =  y;
	}
	reBuf = sum ;
	return;	
}

void SimpleDataSave::getShowWaveNum(DataBuf* buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int& reBuf)
{
	GobalData* g = GobalData::getGobalData();
//	AUTOSET set = g->getAutoSet();
	int max = -2048;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	if( timelapes > startNum )
		{
			reBuf = 0;
			return ;
		}
	//max = (data[startch][startNum] - stdline[startch])*pars[startch]/100;
	for(int ch = startch; ch <= startch + chnum; ch++)
		{
			double z = double(pars[ch])/20;
			for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
			{
			//	int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
				int y = (data[ch][i] - stdline[ch])*pow(10,z)/100;
				if(y > max)
					max = y;

			}
		}		

	max = max >  2048 ? 2048 : max;
	max = max <  -2048 ? -2048 : max;
	reBuf = max;
}

void SimpleDataSave::DoReport(CListCtrl& list, BOOL doexcel)
{

}

void SimpleDataSave::DoDataBase()
{

}

BOOL SimpleDataSave::autoSampleFuc()
{
    return TRUE;
}
// 接-5v 采集值为0
// 接地 是2047
// 接5v  是4095
// 探头供电2.5v。
// 标定数据应该是2047+ 2048/2
BOOL SimpleDataSave::getDateFromCard()
{
	GobalData* g = GobalData::getGobalData();
//	AUTOSET set = g->getAutoSet();
	DataBuf* databuf = g->getDataBuf();
	WORD** data = databuf->getDataPtr();
	USB8221par usb8221par = g->getUsb8221Par();
	WORD* ADBuf = ((RbhUsb20*)(TestSampleControl::cardPtr))->getADbuf();
	WORD* ADBuf1 = ((RbhUsb20*)(TestSampleControl::cardPtr))->getADbuf1();
	
	if(databuf->getdataLens(usb8221par.startch) >= g->getDataLen())
	{
		return FALSE;		
	}
   //	 int laolen1 = databuf->getdataLens(12);
	{
		
		for(int i = 0; i < usb8221par.block;i++)
		{
			for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum; j++)
			{ 
				int len = databuf->getdataLens(j);
			//	data[j][len+i] = (ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16;
				data[j][len+i] = abs(ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1]-32767)/8;
				
			}
#if( CAIJICARD == 2 )	
 			for( j = 68; j < 68+68; j++)
			{ 
 				int len = databuf->getdataLens(j);
 			//	data[j][len+i] = (ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1])/16;
				data[j][len+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8;
			}
#endif
		}
#if( CAIJICARD== 2 )				
		for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum*2; j++)
		{
			databuf->increaeDataLen(j,usb8221par.block);
		}
#else
		for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum; j++)
		{
			databuf->increaeDataLen(j,usb8221par.block);
		}

#endif		
	}
	
	return TRUE;

}

void SimpleDataSave::endSampleData()
{

}

void SimpleDataSave::GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int max = -2048;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	double z = double(pars[ch])/20;
	
	if( timelapes > startNum )
		{
			reBuf = 0;
			return ;
		}
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		int y = (data[ch][i] - stdline[ch])*pow(10,z)/100;
	    	if(y > max)
		    max = y;
	}
	max = max >  2048 ? 2048 : max;
	max = max <  -2048 ? -2048 : max;

	reBuf = max;
}

void SimpleDataSave::GetWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void SimpleDataSave::GetMinWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int sum = 0;
	int avg = 0;
	GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
		int y1 = 0,y2 = 0,y3 = 0;
	int y4 = 0;
	int max = 0;
	if( timelapes > startNum )
		{
			reBuf = 0;
			return ;
		}
	for(int ch = startch; ch <= startch + chnum; ch++)
	{
		double z = double(pars[ch])/20;
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			if (i<2*set.differ[0])
			{
				max = 0;
			}
			else
			{
			//	double z = double(pars[ch])/100; 
			//	y1 = (data[ch][i] - stdline[ch])*z;
			//	y2 = (data[ch][i-set.differ[ch/32]] - stdline[ch])*z;
			//	y3 = (data[ch][i-2*set.differ[ch/32]] - stdline[ch])*z;	
				y1 = (data[ch][i] - stdline[ch])*pow(10,z)/100;
				y2 = (data[ch][i-set.differ[ch/32]] - stdline[ch])*pow(10,z)/100;
				y3 = (data[ch][i-2*set.differ[ch/32]] - stdline[ch])*pow(10,z)/100;			
				y4 = y1+y3-2*y2;
				y4 = abs(y4*set.differadjust[ch/32])/100;
					
				if(y4 > max)
					max = y4;
			}
		}
	}
	max = max >  2048 ? 2048 : max;
	max = max < 0 ? 0 : max;

	reBuf = max;
}

void SimpleDataSave::GetAvgWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int sum = 0;
	int avg = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	for(int ch = startch; ch <= startch + chnum; ch++)
	{
		int max = 0;
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
			if(i == startNum)
			{
				max = y;
			}
			if(y > max)
				max = y;
		}
		sum += max;
	}
	avg = sum / chnum;
	avg = avg >  2048 ? 2048 : avg;
	avg = avg < -2048 ? -2048 : avg;
	reBuf = avg;
}

void SimpleDataSave::GetDifferWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	int max = 0;
	int y1 = 0,y2 = 0,y3 = 0;
	int y4 = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	int y = 0;

	reBuf = 0;
	if( buf->getdataLens(ch) < 	2*blocklen )
		return;

	if( timelapes > startNum )
		{
			reBuf = 0;
			return ;
		}
	double z = double(pars[ch])/20;
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		if (i<2*set.differ[0])
		{
			max = 0;
		}
		else
		{
		//	double z = double(pars[ch])/100; 
		//	y1 = (data[ch][i] - stdline[ch])*z;
		//	y2 = (data[ch][i-set.differ[ch/32]] - stdline[ch])*z;
		//	y3 = (data[ch][i-2*set.differ[ch/32]] - stdline[ch])*z;	
			y1 = (data[ch][i] - stdline[ch])*pow(10,z)/100;
			y2 = (data[ch][i-set.differ[ch/32]] - stdline[ch])*pow(10,z)/100;
			y3 = (data[ch][i-2*set.differ[ch/32]] - stdline[ch])*pow(10,z)/100;			
			y4 = y1+y3-2*y2;
			y4 = abs(y4*set.differadjust[ch/32])/100;
				
			if(y4 > max)
				max = y4;
		}
	
	}
		
	max = max >  2048 ? 2048 : max;
	max = max < 0 ? 0 : max;
	reBuf = max;
}

