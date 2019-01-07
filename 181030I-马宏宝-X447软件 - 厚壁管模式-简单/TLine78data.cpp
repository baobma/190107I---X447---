 // TLine78data.cpp: implementation of the CTLine78data class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "TLine78data.h"
#include "GobalData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL CTLine78data::alertflag = FALSE;
char CTLine78data::alertSingle = 0;

CTLine78data::CTLine78data()
{
    tl78status = TL78STATUS_STATUS0;
	suffix = "78d";
	compress = 100;
	needTrigger = TRUE;
}

CTLine78data::~CTLine78data()
{

}
/*
 *	return false为采集结束
 */
BOOL CTLine78data::getDateFromCard()
{
    GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	DataBuf* databuf = g->getDataBuf();
	WORD** data = databuf->getDataPtr();
	USB8221par usb8221par = g->getUsb8221Par();
	WORD* ADBuf = ((RbhUsb20*)(TestSampleControl::cardPtr))->getADbuf();
	
	if(databuf->getdataLens(usb8221par.startch) >= g->getDataLen())
	{
		return FALSE;		
	}
	switch(tl78status)
	{
	case TL78STATUS_STATUS0:
		return TRUE;
		break;
	case TL78STATUS_STATUS1:
		{
			for(int i = 0; i < usb8221par.block;i++)
			{
				for(int j = usb8221par.startch; 
				j < usb8221par.startch+usb8221par.channelnum; j++)
				{
					if( ( j >= 1-1 && j <= 4-1 ) || ( j >= 9-1 && j <= 16-1))
					{
						int len = databuf->getdataLens(j);
						data[j][len+i] = ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1];
					}		
				}
			}
            //打标
			int yMax = 2048;
			int y0 = 0; int yd0 = set.restrain[1]*yMax/100;
			getShowWaveNum(databuf,8,8-1,databuf->getdataLens(8),usb8221par.block,set.timelapes[1],y0);
			if( (y0-yd0 > set.alertline[1]*yMax/100))
			{
				g->goodflag = FALSE;
				CTLine78data::alertflag = TRUE;
				CTLine78data::alertSingle = 1;
			}
			for(int j = usb8221par.startch; 
			j < usb8221par.startch+usb8221par.channelnum; j++)
			{
				if( ( j >= 1-1 && j <= 4-1 ) || ( j >= 9-1 && j <= 16-1))
				{
					databuf->increaeDataLen(j,usb8221par.block);
				}
			}
		}
		break;
	case TL78STATUS_STATUS2:
	case TL78STATUS_STATUS_DEMOCRATE:
		{
            for(int i = 0; i < usb8221par.block;i++)
			{
				for(int j = usb8221par.startch; 
				j < usb8221par.startch+usb8221par.channelnum; j++)
				{
					if( ( j >= 1-1 && j <= 4-1 ) || ( j >= 9-1 && j <= 24-1))
					{
						int len = databuf->getdataLens(j);
						data[j][len+i] = ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1];
					}		
				}
			}

			int yMax = 2048;
			int y0 = 0; int yd0 = set.restrain[1]*yMax/100;
			getShowWaveNum(databuf,8,8-1,databuf->getdataLens(8),usb8221par.block,set.timelapes[1],y0);
			int y1 = 0; int yd1 = set.restrain[2]*yMax/100;
			getShowWaveNum(databuf,16,8-1,databuf->getdataLens(16),usb8221par.block,set.timelapes[2],y1);
			if( (y0-yd0 > set.alertline[1]*yMax/100))
			{
				g->goodflag = FALSE;
				CTLine78data::alertflag = TRUE;
				CTLine78data::alertSingle = 1;
			}
			if((y1-yd1 > set.alertline[2]*yMax/100))
			{
				g->goodflag = FALSE;
				CTLine78data::alertflag = TRUE;
				CTLine78data::alertSingle += 2;
			}
			for(int j = usb8221par.startch; 
			j < usb8221par.startch+usb8221par.channelnum; j++)
			{
				if( ( j >= 1-1 && j <= 4-1 ) || ( j >= 9-1 && j <= 24-1))
				{
					databuf->increaeDataLen(j,usb8221par.block);
				}
			}
		}
		break;
	case TL78STATUS_STATUS3:
		for(int i = 0; i < usb8221par.block;i++)
		{
			for(int j = usb8221par.startch; 
			j < usb8221par.startch+usb8221par.channelnum; j++)
			{
				if( j >= 17-1 && j <= 24-1 )
				{
					int len = databuf->getdataLens(j);
					data[j][len+i] = ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1];
				}		
			}
		}
		
		int yMax = 2048;
		int y0 = 0; int yd0 = set.restrain[2]*yMax/100;
		getShowWaveNum(databuf,16,8-1,databuf->getdataLens(16),usb8221par.block,set.timelapes[2],y0);
		if( (y0-yd0 > set.alertline[2]*yMax/100))
		{
			g->goodflag = FALSE;
			CTLine78data::alertflag = TRUE;
			CTLine78data::alertSingle = 2;
		}
		
		for(int j = usb8221par.startch; 
		j < usb8221par.startch+usb8221par.channelnum; j++)
		{
			if( j >= 17-1 && j <= 24-1)
			{
				databuf->increaeDataLen(j,usb8221par.block);
			}
		}
		break;
	}
	return TRUE;
}

BOOL CTLine78data::autoSampleFuc()
{
	const int num = 5;
	GobalData* g = GobalData::getGobalData();
	RbhUsb20* usbcard = (RbhUsb20*)(TestSampleControl::cardPtr);
	if(CTLine78data::alertflag == TRUE)
	{
		usbcard->SendDigitalOuput(CTLine78data::alertSingle,TRUE);
		CTLine78data::alertflag = FALSE;
		CTLine78data::alertSingle = 0;
	}

	for(int i = 0; i < num; i++)
	{
		BYTE DI = usbcard->GetDigitalInput();
		int Bit1 = 1;
		int Bit2 = 2;
		Bit1 = Bit1&DI;
		Bit2 = Bit2&DI;
		switch(tl78status)
		{
		case TL78STATUS_STATUS0:
			{
				static int bit1num = 0;
				if(Bit1 == 0)  
				{
					bit1num++;
				}
				if(bit1num == num)   //第一个触发
				{
					bit1num = 0;
                    tl78status = TL78STATUS_STATUS1;
                    ::SendMessage(g->Dlghandle,WM_NEW_MSG,NEWONE_NEXT,0);
				}
			}
			break;
		case TL78STATUS_STATUS1:   
			{
				static int bit2num = 0;
				if(Bit2 == 0)     
				{
					bit2num++;
				}
				if(bit2num == num)     //第二个触发
				{
                    bit2num = 0;
					tl78status = TL78STATUS_STATUS2;
				}
			}
			break;
		case TL78STATUS_STATUS2:
			{
				static int end1num = 0;
				if(Bit1 != 0)   //第一个触发（反）
				{
					end1num++;
				}
				if(end1num == num)
				{
					end1num = 0;
                    tl78status = TL78STATUS_STATUS3;
				}
			}
			break;
		case TL78STATUS_STATUS3:
			{
				static int end2num = 0;
				if(Bit2 != 0)   
				{
					end2num++;
				}
				if(end2num == num)  //第二个触发（反）
				{
					end2num = 0;
                    tl78status = TL78STATUS_STATUS0;
					::SendMessage(g->Dlghandle,WM_NEW_MSG,COMPLETE_THIS,0);
					return FALSE;
				}
			}
			break;
		case TL78STATUS_STATUS_DEMOCRATE:
			break;    
		}
	}

	return FALSE;
}

void CTLine78data::DoReport(CListCtrl& list, BOOL doexcel)
{
 
}

void CTLine78data::DoDataBase()
{

}

void CTLine78data::getShowWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int max = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		
		int y = (data[ch][i] - stdline[ch])*pars[ch]/100;
		if(i == startNum)
			max = y;
		if(y > max)
			max = y;
	}
    max = max >  2048 ? 2048 : max;
	max = max < -2048 ? -2048 : max;
    reBuf = max;
}

void CTLine78data::getShowWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
    if(startch == 9-1)
	{
		int max = 0;
		short* pars = buf->getParPtr();
		short* stdline = buf->getStdPtr();
		WORD** data = buf->getDataPtr();
		max = (data[startch][startNum] - stdline[startch])*pars[startch]/100;
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
		max = max < -2048 ? -2048 : max;
		reBuf = max;
	}
	else if(startch == 17-1)
	{
		int max = 0;
		short* pars = buf->getParPtr();
		short* stdline = buf->getStdPtr();
		WORD** data = buf->getDataPtr();
		max = (data[startch][startNum] - stdline[startch])*pars[startch]/100;
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
		max = max < -2048 ? -2048 : max;
		reBuf = max;
	}
	else if(startch == 1-1 && chnum == 4-1)
	{
		int sum = 0;
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
		sum = sum >  2048 ? 2048 : sum;
		sum = sum < -2048 ? -2048 : sum;
		reBuf = sum;
	}
}

BOOL CTLine78data::savePerBlockData(CFile *file, BLOCKHEAD *bHead, int &len, CSampleCard *card, int id)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	CTime t = CTime::GetCurrentTime();
	int ch = card->getChannelNum();
	
	int tsum = 0;
	for(int i = 0; i < 4; i++)
	{
		int len = buf->getdataLens(i);
		tsum += len;
	}
	for(    i = 8; i < 24; i++)
	{
        int len = buf->getdataLens(i);
		tsum += len;
	}
	int datasum = tsum*sizeof(short)/compress + 20*sizeof(int) + sizeof(BLOCKHEAD); //单块总数据量
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
    for(     i = 0; i < 4; i++)  //
	{
		WORD** data = buf->getDataPtr();
		int len = buf->getdataLens(i);
		file->Write(&len,sizeof(int));
		for(int j = 0; j < len; j += compress)
		{
			short y = getSaveNum(buf,i,j,compress);
            file->Write(&y,sizeof(short));
		}
	}

	for(     i = 8; i < 24; i++)  //
	{
		WORD** data = buf->getDataPtr();
		int len = buf->getdataLens(i);
		file->Write(&len,sizeof(int));
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

BOOL CTLine78data::loadPerBlockData(CFile *file, BLOCKHEAD *bHead, int &len)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();

	int datasum;	
	file->Read(&datasum,sizeof(int));  //读单块总长度
	
	//
	file->Read(bHead,sizeof(BLOCKHEAD));
    //读单块头
	
	
	//读数据
    for(int i = 0; i < 4; i++)  //从第0通道开始，根据通道数量读取数据
	{
		WORD** data = buf->getDataPtr();
		short d  = 0;
		int len = 0;
		file->Read(&len,sizeof(int));
		for(int j = 0; j < len; j++)
		{
			if(j%compress == 0)
				file->Read(&d,sizeof(short));
            data[i][j] = d;	 
		}
		buf->setDataLens(i,len);
	}
	for(    i = 8; i < 24; i++)  //从第0通道开始，根据通道数量读取数据
	{
		WORD** data = buf->getDataPtr();
		short d  = 0;
		int len = 0;
		file->Read(&len,sizeof(int));
		for(int j = 0; j < len; j++)
		{
			if(j%compress == 0)
				file->Read(&d,sizeof(short));
            data[i][j] = d;	 
		}
		buf->setDataLens(i,len);
	}
	file->Read(&datasum,sizeof(int));  //读单块总长度
	len = datasum;
	
    return TRUE;
}

short CTLine78data::getSaveNum(DataBuf *buf, int ch, int startNum, int blocklen)
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

void CTLine78data::endSampleData()
{

}

void CTLine78data::GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void CTLine78data::GetWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void CTLine78data::GetMinWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void CTLine78data::GetAvgWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}
