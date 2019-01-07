// TlineSv3.cpp: implementation of the CTlineSv3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "TlineSv3.h"
#include "GobalData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL CTlineSv3::alertflag = FALSE;
char CTlineSv3::alertSingle = 0;
CTlineSv3::CTlineSv3()
{
    compress = 100;
	suffix = "sv3";
	needTrigger = TRUE;
	tlsv3status = TLSV3STATUS_STATUS0;
	endDataLen = 20000;
}

CTlineSv3::~CTlineSv3()
{

}

/*
 *	1-16存放A、B两组线圈  17-20放霍尔元件  21-36 放A B两组线圈前端面  41-56存放A B两组线圈后端面
 */
BOOL CTlineSv3::getDateFromCard() 
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
	switch(tlsv3status)
	{
	case TLSV3STATUS_STATUS0:
		return TRUE;
		break;
	case TLSV3STATUS_STATUS1:
		{
			if(databuf->getdataLens(21-1) < endDataLen)  //前端部 20-36通道存放
			{
				for(int i = 0; i < usb8221par.block;i++)
				{
					for(int j = usb8221par.startch; 
					j < usb8221par.startch+usb8221par.channelnum; j++)
					{
						if( ( j >= 1-1 && j <= 16-1 ))
						{
							int len = databuf->getdataLens(j+20);
							data[j+20][len+i] = ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1];
						}		
					}
				}
				//报警输出
				int yMax = 2048;
				int y0 = 0; int yd0 = set.restrain[3]*yMax/100;
				getShowWaveNum(databuf,20,8-1,databuf->getdataLens(20),usb8221par.block,set.timelapes[0],y0);
				int y1 = 0; int yd1 = set.restrain[4]*yMax/100;
				getShowWaveNum(databuf,28,8-1,databuf->getdataLens(28),usb8221par.block,set.timelapes[1],y1);
				if( (y0-yd0 > set.alertline[3]*yMax/100) ||  (y1-yd1 > set.alertline[4]*yMax/100) )
				{
					g->goodflag = FALSE;
					CTlineSv3::alertflag = TRUE;
					CTlineSv3::alertSingle = 1;
				}

				for(int j = usb8221par.startch; 
				j < usb8221par.startch+usb8221par.channelnum; j++)
				{
					if( ( j >= 1-1 && j <= 16-1 ))
					{
						databuf->increaeDataLen(j+20,usb8221par.block);
					}
				}
			}
			else
			{
				for(int i = 0; i < usb8221par.block;i++)
				{
					for(int j = usb8221par.startch; 
					j < usb8221par.startch+usb8221par.channelnum; j++)
					{
						if( ( j >= 1-1 && j <= 16-1 ))
						{
							int len = databuf->getdataLens(j);
							data[j][len+i] = ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1];
						}		
					}
				}
				for(int j = usb8221par.startch; 
				j < usb8221par.startch+usb8221par.channelnum; j++)
				{
					if( ( j >= 1-1 && j <= 16-1 ))
					{
						databuf->increaeDataLen(j,usb8221par.block);
					}
				}
				//报警输出
				int yMax = 2048;
				int y0 = 0; int yd0 = set.restrain[0]*yMax/100;
				getShowWaveNum(databuf,0,8-1,databuf->getdataLens(0),usb8221par.block,set.timelapes[0],y0);
				int y1 = 0; int yd1 = set.restrain[1]*yMax/100;
				getShowWaveNum(databuf,8,8-1,databuf->getdataLens(8),usb8221par.block,set.timelapes[1],y1);
				if( (y0-yd0 > set.alertline[0]*yMax/100) ||  (y1-yd1 > set.alertline[1]*yMax/100) )
				{
					g->goodflag = FALSE;
					CTlineSv3::alertflag = TRUE;
					CTlineSv3::alertSingle = 1;
				}
			}

			/*
			 *	壁厚
			 */
			for(int i = 0; i < usb8221par.block;i++)
			{
				for(int j = usb8221par.startch; 
				j < usb8221par.startch+usb8221par.channelnum; j++)
				{
					if( ( j >= 17-1 && j <= 20-1 ))
					{
						int len = databuf->getdataLens(j);
						data[j][len+i] = ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1];
					}		
				}
			}
			for(int j = usb8221par.startch; 
			j < usb8221par.startch+usb8221par.channelnum; j++)
			{
				if( ( j >= 17-1 && j <= 20-1 ))
				{
					databuf->increaeDataLen(j,usb8221par.block);
				}
			}
			//报警输出
			int yMax = 2048;
			int y1 = 0; int yd1 = set.restrain[2]*yMax/100;
			getShowWaveNum(databuf,16,4-1,databuf->getdataLens(16),usb8221par.block,set.timelapes[2],y1);
			if( (y1-yd1 > set.alertline[0]*yMax/100) )
			{
				g->goodflag = FALSE;
				CTlineSv3::alertflag = TRUE;
				CTlineSv3::alertSingle = 2;
			}
			
		}
		break;
	}
    return TRUE;
}

BOOL CTlineSv3::autoSampleFuc()
{
	const int num = 5;
	GobalData* g = GobalData::getGobalData();
	RbhUsb20* usbcard = (RbhUsb20*)(TestSampleControl::cardPtr);     
	
	if(CTlineSv3::alertflag == TRUE)
	{
		usbcard->SendDigitalOuput(CTlineSv3::alertSingle,TRUE);
		CTlineSv3::alertflag = FALSE;
		CTlineSv3::alertSingle = 0;
	}
	for(int i = 0; i < num; i++)
	{
		BYTE DI = usbcard->GetDigitalInput();
		int Bit1 = 1;
		Bit1 = Bit1&DI;
		switch(tlsv3status)
		{
		case TLSV3STATUS_STATUS0:
			{
				static int bit1num = 0;
				if(Bit1 == 0)  
				{
					bit1num++;
				}
				if(bit1num == num)   //第一个触发
				{
					bit1num = 0;
					setParsforSV3();
                    tlsv3status = TLSV3STATUS_STATUS1;
                    ::SendMessage(g->Dlghandle,WM_NEW_MSG,NEWONE_NEXT,0);
				}
			}
			break;
		case TLSV3STATUS_STATUS1:
			{
				static int end1num = 0;
				if(Bit1 != 0)   
				{
					end1num++;
				}
				if(end1num == num)      //第一个触发(反)
				{
					end1num = 0;
                    tlsv3status = TLSV3STATUS_STATUS0;
					::SendMessage(g->Dlghandle,WM_NEW_MSG,COMPLETE_THIS,0);
					return FALSE;
				}
			}
			break;
		case TLSV3STATUS_DEMOCRATE:
			break;    
		}
	}
	
	return FALSE;
}

void CTlineSv3::DoReport(CListCtrl& list, BOOL doexcel)
{
    GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	float spic = 100*1000/32*60;
	CString str;
	if(doexcel == FALSE)
	{
		int nColumnCount = (list.GetHeaderCtrl())->GetItemCount();
		
		for (int i=0;i < nColumnCount;i++)
		{
			list.DeleteColumn(0);
		}
		list.DeleteAllItems();
		if(g->dataHead.blocksum < 0)
			return;
		
		list.InsertColumn(0,"信息  ",LVCFMT_LEFT,70,-1);
		list.InsertColumn(1,"内容  ",LVCFMT_LEFT,80,-1);
		list.InsertColumn(2,"长度  ",LVCFMT_LEFT,80,-1);
		list.InsertItem(0,"");
		list.SetItemText(0,0,"总根数");
		
		list.InsertItem(1,"");
		list.SetItemText(1,0,"好杆根数");
		
		list.InsertItem(2,"");
		list.SetItemText(2,0,"疑似杆根数");
		
		list.InsertItem(3,"");
		list.SetItemText(3,0,"当前杆好坏");
		
		if(g->getFilePtr() != NULL)
		{
			str.Format("%d",g->dataHead.blocksum);
			list.SetItemText(0,1,str);
            str.Format("%0.2f m",g->dataHead.datasum*set.speed/spic);
			list.SetItemText(0,2,str);

			str.Format("%d",g->dataHead.goodsum);
			list.SetItemText(1,1,str);
			str.Format("%0.2f m",g->dataHead.gooddatasum*set.speed/spic);
			list.SetItemText(1,2,str);

			str.Format("%d",g->dataHead.blocksum-g->dataHead.goodsum);
			list.SetItemText(2,1,str);
			str.Format("%0.2f m",(g->dataHead.datasum-g->dataHead.gooddatasum)*set.speed/spic);
			list.SetItemText(2,2,str);
			if(g->blockHead.good == TRUE)
				str.Format("好杆");
			else
				str.Format("疑似杆");
			list.SetItemText(3,1,str);
			str.Format("%0.2f m",g->blockHead.blocksum*set.speed/spic);
			list.SetItemText(3,2,str);
		}

		list.InsertItem(4,"");
		list.SetItemText(4,0,"当前杆时间");
		CString str;
		str.Format("%02d点%02d分",(g->blockHead).hour,(g->blockHead).min);
		list.SetItemText(4,1,str);

		list.InsertItem(5,"");
		list.SetItemText(5,0,"当前流水号");
		str.Format("%d",g->blockHead.sid<0?0:g->blockHead.sid);
		list.SetItemText(5,1,str);
	}
}

void CTlineSv3::DoDataBase()
{

}

BOOL CTlineSv3::savePerBlockData(CFile *file, BLOCKHEAD *bHead, int &len, CSampleCard *card, int id)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	CTime t = CTime::GetCurrentTime();
	
	len = buf->getdataLens(0)+buf->getdataLens(8)+
		buf->getdataLens(20)+buf->getdataLens(40);                   //返回值
	int tsum = 0;
	for(int i = 0; i < 60; i++)
	{
        if( (i >= 0) && i < 36 || (i >= 40 && i < 56) )
		{
            tsum += buf->getdataLens(i);
		}
	}
	int datasum = tsum*sizeof(short)/compress + sizeof(BLOCKHEAD) + 52*sizeof(int); //单块总数据量
	
	file->Write(&datasum,sizeof(int));  //写入单块总长度
	//
	bHead->hour = t.GetHour();
	bHead->min  = t.GetMinute();
	bHead->blocksum = len;
	bHead->id = id;
	bHead->sid = g->getSid();
	g->setSid(bHead->sid+1);
	bHead->good = g->goodflag;
	file->Write(bHead,sizeof(BLOCKHEAD));
    //写单块头
	
	//写数据
    for(    i = 0; i < 60; i++)
	{
		if( (i >= 0) && i < 36 || (i >= 40 && i < 56) )
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
	}
	file->Write(&datasum,sizeof(int));  //写入单块总长度
    return TRUE;
}

BOOL CTlineSv3::loadPerBlockData(CFile *file, BLOCKHEAD *bHead, int &len)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	int datasum;
	
	file->Read(&datasum,sizeof(int));  //读单块总长度
	
	//
	file->Read(bHead,sizeof(BLOCKHEAD));
	g->goodflag = bHead->good;
    //读单块头
	
	//读数据
    for(int i = 0; i < 60; i++)  //从第0通道开始，根据通道数量读取数据
	{
		if( (i >= 0) && i < 36 || (i >= 40 && i < 56) )
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
	}
	file->Read(&datasum,sizeof(int));  //读单块总长度
	len = datasum;
	
    return TRUE;
}

void CTlineSv3::setParsforSV3()
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();
    short* std = databuf->getStdPtr();
	short* par = databuf->getParPtr();

    for(int i = 1-1; i <= 16-1; i++)
	{
		par[20+i] = par[i];  par[40+i] = par[i];
	    std[20+i] = std[i];  std[40+i] = std[i];	
	}
}

void CTlineSv3::endSampleData()
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();
    int movelen = endDataLen;
	int len = databuf->getdataLens(1-1);
	if(len < endDataLen)
		movelen = len;
	
	WORD** data = databuf->getDataPtr();
	
	for(int i = 0; i < 16; i++)
	{
		memmove(data[i+40],(short*)(data[i]+len-movelen),movelen*sizeof(short));
		databuf->increaeDataLen(i,-movelen);
		databuf->increaeDataLen(40+i,movelen);
	}
	tlsv3status = TLSV3STATUS_STATUS0;
	CTlineSv3::alertflag = FALSE;
}

void CTlineSv3::getShowWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
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
	max = max <  0 ? 0 : max;
    reBuf = max;
}

void CTlineSv3::getShowWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
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
	max = max <  0 ? 0 : max;
    reBuf = max;
}

void CTlineSv3::GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void CTlineSv3::GetWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void CTlineSv3::GetMinWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}

void CTlineSv3::GetAvgWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{

}
