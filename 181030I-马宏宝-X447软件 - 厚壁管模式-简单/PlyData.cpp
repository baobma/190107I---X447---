// PlyData.cpp: implementation of the CPlyData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "hustndt.h"
#include "PlyData.h"
#include "GobalData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL CPlyData::alertflag = FALSE;
char CPlyData::alertSingle = 0;
//extern inspect;
//extern  caijimodel;

long int  RC_Record[4];//4通道编码器的连续采集结果,32位的结果

CPlyData::CPlyData()
{
    l82PlyStatus = L82PLYSTATUS_STOP;
	suffix = "vmm";
	compress = 100;
	needTrigger = TRUE;
}

CPlyData::~CPlyData()
{

}

BOOL CPlyData::getDateFromCard()
{
	GobalData* g = GobalData::getGobalData();
// 	AUTOSET set = g->getAutoSet();
	DataBuf* databuf = g->getDataBuf();
	WORD** data = databuf->getDataPtr();
	USB8221par usb8221par = g->getUsb8221Par();
	WORD* ADBuf = ((RbhUsb20*)(TestSampleControl::cardPtr))->getADbuf();
	WORD* ADBuf1 = ((RbhUsb20*)(TestSampleControl::cardPtr))->getADbuf1();
	
	if(databuf->getdataLens(usb8221par.startch+4) >=  g->getDataLen())
	{
		return FALSE;		
	}
    if (l82PlyStatus == L82PLYSTATUS_DEMARCATE ||l82PlyStatus == L82PLYSTATUS_START)
	{
		for(int i = 0; i < usb8221par.block;i++)
		{
			for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum; j++)
			{ 
				int len = databuf->getdataLens(j);
				data[j][len+i] = (ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16;
			}
			for( j = 68; j < 68+68; j++)
			{ 
				int len = databuf->getdataLens(j);
				data[j][len+i] = (ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1])/16;
			}
		}
		
		for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum*2; j++)
		{
			databuf->increaeDataLen(j,usb8221par.block);
		}
		
	}
	return TRUE;
}

BOOL CPlyData::autoSampleFuc()
{
	const int num = 5;
	GobalData* g = GobalData::getGobalData();
	RbhUsb20* usbcard = (RbhUsb20*)(TestSampleControl::cardPtr);
	if(CPlyData::alertflag == TRUE)//处理完之后再进行判断分级类别
	{
		usbcard->SendDigitalOuputByNet(CPlyData::alertSingle,TRUE);
		CPlyData::alertflag = FALSE;
		CPlyData::alertSingle = 0;
	}	
	
	for(int i = 0; i < num; i++)
	{
		BYTE DI = usbcard->GetDigitalInputByNet();
		int Bit1 = 1;
		int Bit2 = 2;
		if( DI == 0x1f )
			continue;
		Bit1 = Bit1&DI;
		Bit2 = Bit2&DI;
		switch(l82PlyStatus)
		{
		case L82PLYSTATUS_STOP:
			{
				static int bit1num = 0;
				if(Bit1 == 1 )  
				{
					bit1num++;
				}
				if(bit1num >= num)   //第一个触发
				{
					bit1num = 0;
              		      l82PlyStatus = L82PLYSTATUS_START;
		                    ::SendMessage(g->Dlghandle,WM_NEW_MSG,NEWONE_NEXT,0);
				}
			}
			break;
		case L82PLYSTATUS_START:   
			{
				static int end1num = 0;
				if(Bit1 == 0)   //第一个触发（反）
				{
					end1num++;
				}
				if(end1num == num)
				{	
					end1num = 0;
              		      l82PlyStatus = L82PLYSTATUS_STOP;		

					::SendMessage(g->Dlghandle,WM_NEW_MSG,COMPLETE_THIS,0);
					return FALSE;
				}
			}
			break;
			
		case L82PLYSTATUS_DEMARCATE:
			break;    
		}
	}
	
	return FALSE;
}

void CPlyData::DoReport(CListCtrl& list, BOOL doexcel)
{

}

void CPlyData::DoDataBase()
{

}
void CPlyData::getShowWaveNum3(DataBuf *buf,int ch, int startNum, int blocklen,int &reBuf)
{
	GobalData* g = GobalData::getGobalData();
// 	AUTOSET set = g->getAutoSet();
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	int sum = 0;

	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
		sum+=abs(y);
	}
	reBuf = sum /blocklen;
	return;	
}
void CPlyData::getShowWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
    	GobalData* g = GobalData::getGobalData();
// 	AUTOSET set = g->getAutoSet();
	int max = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	reBuf = 0;
	if( buf->getdataLens(ch) < 	2*blocklen )
		return;

	if( timelapes > startNum )
		return ;
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
		if(i == startNum)
			max = y;
		if(y > max)
			max = y;
	}
	
    	max = max >  2048 ? 2048 : max;
	max = max <  -2048 ? -2048 : max;
    reBuf = max;
}

void CPlyData::getShowWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
  	GobalData* g = GobalData::getGobalData();
// 	AUTOSET set = g->getAutoSet();
	int max = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();

	max = (data[startch][startNum] - stdline[startch])*pars[startch]/100;
	reBuf = 0;
	if( buf->getdataLens(startch) < 2*blocklen )
		return;

	if( timelapes > startNum )
		return ;

	for(int ch = startch; ch <= startch + chnum; ch++)
	{
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
			if(y > max)
				max = y;
		}
	}		
 
	max = max >  2048 ? 2048 : max;
	max = max <  -2048 ? -2048 : max;
	reBuf = max;
	return ;
}

BOOL CPlyData::savePerBlockData(CFile *file, BLOCKHEAD *bHead, int &len, CSampleCard *card, int id)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	CTime t = CTime::GetCurrentTime();
	int ch = card->getChannelNum();
	
	int tsum = 0;
	for(int i = 0; i < g->MAXCHANNEL; i++)
	{
		int len = buf->getdataLens(i);
		tsum += len;
	}
/*	for(    i = 16; i < 68; i++)
	{
        	int len = buf->getdataLens(i);
		tsum += len;
	}*/
	int datasum = tsum*sizeof(short) + ( g->MAXCHANNEL)*sizeof(int) + sizeof(BLOCKHEAD); //单块总数据量
    //20通道的len本身int
	file->Write(&datasum,sizeof(int));  //写入单块总长度
	//
	bHead->hour = t.GetHour();
	bHead->min  = t.GetMinute();
	bHead->good = g->goodflag;
	bHead->blocksum = 0;//无意义
	bHead->id = id;
	file->Write(bHead,sizeof(BLOCKHEAD));
    //写单块头
	
	//写数据
    for(     i = 0; i < g->MAXCHANNEL; i++)  //
	{
		WORD** data = buf->getDataPtr();
		int len = buf->getdataLens(i);
		file->Write(&len,sizeof(int));
		file->Write(data[i],buf->getdataLens(i)*sizeof(WORD));
	}
	
/*	for(     i = 16; i < 68; i++) 
	{
		short** data = buf->getDataPtr();
		int len = buf->getdataLens(i);
		file->Write(&len,sizeof(int));
		file->Write(data[i],buf->getdataLens(i)*sizeof(short));
	}*/
	
	file->Write(&datasum,sizeof(int));  //写入单块总长度
	len = datasum;                      //返回值
    return TRUE;
}

BOOL CPlyData::loadPerBlockData(CFile *file, BLOCKHEAD *bHead, int &len)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	
	int datasum;	
	file->Read(&datasum,sizeof(int));  //读单块总长度
	
	//
	file->Read(bHead,sizeof(BLOCKHEAD));
    //读单块头
		
	//读数据
    for(int i = 0; i <  g->MAXCHANNEL; i++)  //从第0通道开始，根据通道数量读取数据
	{
		WORD** data = buf->getDataPtr();
		short d  = 0;
		int len = 0;
		file->Read(&len,sizeof(int));
		file->Read(data[i],len * sizeof(short));  //各通道数据长度一样
		buf->setDataLens(i,len);
	}

	file->Read(&datasum,sizeof(int));  //读单块总长度
	len = datasum;
	
    return TRUE;
}

void CPlyData::endSampleData()
{

}

short CPlyData::getSaveNum(DataBuf *buf, int ch, int startNum, int blocklen)
{
    int max = 0;
	short re = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		int y = (data[ch][i] - stdline[ch]);
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

void CPlyData::GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int max = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		int y = 0;
		y = (data[ch][i] - stdline[ch])*pars[ch]/100;
		if (i<timelapes)
		{
			y = 0;
		}
		if(i == startNum)
			max = y;// 
		if(y > max)
			max = y;
	}
//  max = max >  2048 ? 2048 : max;
// 	max = max < 0 ? 0 : max;
    reBuf = max;
}

void CPlyData::GetWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void CPlyData::GetMinWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	int max = 0;
	int y1 = 0,y2 = 0,y3 = 0;
	int y4 = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();

	reBuf = 0;
	if( buf->getdataLens(startch) < 	2*blocklen )
		return;

	if( timelapes > startNum )
		return ;

	
	for(int ch = startch; ch <= startch + chnum; ch++)
	{
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			if (ch>=4)
			{
				if (i<2*set.differ[(ch-10)/16])
				{
					max = 0;
				}
				else
				{
			//		double z = double(pars[ch])/20;
					y1 = (data[ch][i] - stdline[ch])*pars[ch]/100;
					y2 = (data[ch][i-set.differ[(ch-10)/16]] - stdline[ch])*pars[ch]/100;
					y3 = (data[ch][i-2*set.differ[(ch-10)/16]] - stdline[ch])*pars[ch]/100;		
					y4 = y1+y3-2*y2;
					y4 = abs(y4*set.differadjust[(ch-10)/16])/100;
					if(y4 > max)
						max = y4;
				}
			}
		}
	}
	max = max >  2048 ? 2048 : max;
	max = max < 0 ? 0 : max;
	reBuf = max;
}

void CPlyData::GetAvgWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int sum = 0;
	int avg = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();

	reBuf = 0;
	if( buf->getdataLens(startch) < 2*blocklen )
		return;

	if( timelapes > startNum )
		return ;

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
	avg = sum / (chnum+1);

	reBuf = avg;
}

void CPlyData::GetDifferWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	
	GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	int max = 0;
	int y1 = 0,y2 = 0,y3 = 0;
	int y4 = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();

	reBuf = 0;
	if( buf->getdataLens(ch) < 	2*blocklen )
		return;

	if( timelapes > startNum )
		return ;

	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		if (ch>=4)
		{			
			if (i<2*set.differ[ (ch-10)/16])
			{
				max = 0;
			}
			else
			{				
				y1 = (data[ch][i] - stdline[ch])*pars[ch]/100;
				y2 = (data[ch][i-set.differ[(ch-10)/16]] - stdline[ch])*pars[ch]/100;
				y3 = (data[ch][i-2*set.differ[(ch-10)/16]] - stdline[ch])*pars[ch]/100;	
				y4 = y1+y3-2*y2;
				y4 = abs(y4*set.differadjust[(ch-10)/16])/100;
				if(y4 > max)
					max = y4;
			}
		}
		
	}
	max = max >  2048 ? 2048 : max;
	max = max < 0 ? 0 : max;
	reBuf = max;
}
