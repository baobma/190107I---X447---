// ScarData.cpp: implementation of the CScarData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "hustndt.h"
#include "ScarData.h"
#include "GobalData.h"
#include "ShowSet.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL CScarData::alertflag = FALSE;
char CScarData::alertSingle1 = 0;
char CScarData::alertSingle2 = 0;
BOOL thickPipe_flag = FALSE;

int vLengthhead = 0;//纵向前端采集长度
int vLengthend = 0;//纵向尾端采集长度
int hLengthend = 0; //横向结束采集长度
int vLength = 0; //中间值，用来判断进入纵向2状态
int hendLength = 0;
// 纵向头部
//static bool vheadcut = FALSE;
//static int vheadcutStartPt = 0;
//纵向尾部
//static bool vEndCut = FALSE;
//static int vEndCutTime =0;
// 横向头部
//static bool Hheadcut = FALSE;
//static int HheadcutStartPt = 0;
//横向采集时，发生了偏移。
//static int xoffset=0,yoffset=0;
// 横向尾部
//static bool hEndCut = FALSE;
// int hEndCutTime =0;
int  hlastAlermpt = 0;
int  vlastAlermpt = 0;
int recordXPt[20];
int recordYPt[20];
char indexAlert =0;
char indexAlert2 =0;
//BOOL xLostpt=FALSE;
//BOOL YLostpt=FALSE;
//int lastXpt[5];
//int lastYpt[5];

static int bit1num = 0;
static int bit2numhead = 0;
static int bit2num = 0;  
static int end1num = 0;
static int end2num = 0;
static int end2numtail = 0;
static	int nn =0;// set.alertline3[5]+1;
static	int nnn =0;// set.alertline3[6]+1;
static int HsectionHead=0;
static int VsectionEnd=0;

CScarData::CScarData()
{
    l82ScarStatus = L82SCARSTATUS_STOP;
	suffix = "emt";
	compress = 100;
	needTrigger = FALSE;
	AlertSet();

}

CScarData::~CScarData()
{
	

}
void CScarData::AlertSet()
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	alertbyshow1 = set.showstyle[0];
	alertbyshow2 = set.showstyle[2];
	int baojingxiaxian1 = set.nserl_hacc;
	int baojingxiaxian2 = set.nserl_vacc;

	float acc1 = 1;
	float acc2 = 1;
	switch(baojingxiaxian1)
	{
	case 0:
		acc1= 1;
		break;
	case 1:
		acc1 = 1.12;
		break;
	case 2:
		acc1 = 1.26;
		break;
	case 3:
		acc1 = 1.41;
		break;
	case 4:
		acc1 = 1.58;
		break;
	default:
		acc1 = 1;
	}
	
	switch(baojingxiaxian2)
	{
	case 0:
		acc2= 1;
		break;
	case 1:
		acc2 = 1.12;
		break;
	case 2:
		acc2 = 1.26;
		break;
	case 3:
		acc2 = 1.41;
		break;
	case 4:
		acc2 = 1.58;
		break;
	default:
		acc2 = 1;
	}
	alerty1 = set.alertline[0]*2048/100;
	alerty1_xiaxian = alerty1/acc1;//报警门限下限acc1dB值
	alert1_num = set.alertline3[5];
	

	alerty2 = set.alertline[2]*2048/100;
	alerty2_xiaxian = alerty2/acc2;//报警门限2下限acc2dB值
	alert2_num = set.alertline3[6];

}
BOOL CScarData::getDateFromCard()
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	DataBuf* databuf = g->getDataBuf();
	WORD** data = databuf->getDataPtr();
	USB8221par& usb8221par = g->getUsb8221Par();
	RbhUsb20* usbcard = (RbhUsb20*)(TestSampleControl::cardPtr);
	DataBuf* buf = g->getDataBuf();
	short* stdline = buf->getStdPtr();

	WORD* ADBuf = ((RbhUsb20*)(TestSampleControl::cardPtr))->getADbuf();
	WORD* ADBuf1 = ((RbhUsb20*)(TestSampleControl::cardPtr))->getADbuf1();

	int y0 = 0;
	int y1 = 0;
	int len=0;
	int len2=0;
	if(databuf->getdataLens(6) >= g->getDataLen())
	{
		return FALSE;		
	}
// 现场只需要分横纵向喷标
	switch(l82ScarStatus)
	{
	case L82SCARSTATUS_STOP:				
		return TRUE;
		break;
	case L82SCARSTATUS_HORIZONTAL:
		{			
			len = databuf->getdataLens(4);
			for(int i = 0; i < usb8221par.block;i++)
			{
				for(int j = 0; j < 68; j++)
				{						
				//	data[j][len+i] = abs(ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16;
					data[j][len+i] = abs(ADBuf[j + (i*usb8221par.channelnum) + 1]-32767)/8;
				}
			}
			if(alertbyshow1 == WaveShowStyle_SimpleShow)
			{	
				getShowWaveNum(databuf,4,63,len,usb8221par.block,set.timelapes[0],y0);	
				if ((y0>alerty1_xiaxian)&&(hlastAlermpt+alert1_num*usb8221par.block <len))
				{
					hlastAlermpt = len;
					g->goodflag = FALSE;
					CScarData::alertflag = TRUE;
					CScarData::alertSingle1 = 1;
				//	usbcard->SendDigitalOuput(16,TRUE);
				}

			}
		
			for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum; j++)
				{
					databuf->increaeDataLen(j,usb8221par.block);
				}
		}
		break;
		case L82SCARSTATUS_HORIZONTAL_VERTICAL1:
		{
			len = databuf->getdataLens(4);
			len2 = databuf->getdataLens(68);
			for(int i = 0; i < usb8221par.block;i++)
				{			
					//for(int j = usb8221par.startch;j < usb8221par.startch+usb8221par.channelnum; j++)
					for(int j = 0; j < 68; j++)
					{								
					//	data[j][len+i] = abs(ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16;
						data[j][len+i] = abs(ADBuf[j+(i*usb8221par.channelnum)+1]-32767)/8;
					}
					for( j = 68; j < 136; j++)
					{ 					 				        
					//	data[j][len2+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1])/16;
						
						data[j][len2+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8;
					}

					for( j = 72; j < 76; j++)
					{ 					 				        
						data[j][len2+i] =  stdline[j] ;
					}

					for( j = 80; j < 84; j++)
					{ 					 				        
						data[j][len2+i] =  stdline[j] ;
					}
					for( j = 88; j < 92; j++)
					{ 					 				        
						data[j][len2+i] =  stdline[j] ;
					}
					for( j = 96; j < 100; j++)
					{ 					 				        
						data[j][len2+i] =  stdline[j] ;
					}
					for( j = 104; j < 108; j++)
					{ 					 				        
						data[j][len2+i] =  stdline[j] ;
					}
					for( j = 112; j < 116; j++)
					{ 					 				        
						data[j][len2+i] =  stdline[j] ;
					}

					for( j = 120; j < 124; j++)
					{ 					 				        
						data[j][len2+i] =  stdline[j] ;
					}

					for( j = 128; j < 132; j++)
					{ 					 				        
						data[j][len2+i] =  stdline[j] ;
					}
					
					
					for( j = 76; j < 80; j++)
					{ 					 				        
						data[j][len2+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 84; j < 88; j++)
					{ 					 				        
						data[j][len2+i] =abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 92; j < 96; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 100; j < 104; j++)
					{ 					 				        
						data[j][len2+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 108; j < 112; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}

					for( j = 116; j < 120; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 124; j < 128; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}

					for( j = 132; j < 136; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}


				}
			if(alertbyshow1 == WaveShowStyle_SimpleShow )
			{
				getShowWaveNum(databuf,4,63,len,usb8221par.block,set.timelapes[0],y0);
				if ((y0>alerty1_xiaxian)&&(hlastAlermpt+alert1_num*usb8221par.block <len))
				{
					hlastAlermpt = len;
					g->goodflag = FALSE;
					CScarData::alertflag = TRUE;
					CScarData::alertSingle1 = 1;
				//	usbcard->SendDigitalOuput(16,TRUE);	
				}

			}
				
			if( alertbyshow2 == WaveShowStyle_SimpleShow )	
				{
					getShowWaveNum(databuf,72,63,len2,usb8221par.block,set.timelapes[2],y1);		
					if (y1>alerty2_xiaxian)
					{
						y1 = alerty2 + 5;
					}
				}
			else if( alertbyshow2 == WaveShowStyle_Difference )
				{
					for(int k = 72 ; k < 135 ;k++)
						{
							GetWaveNum(databuf,k,len2,usb8221par.block,set.timelapes[2],y1);
							if( (y1 > alerty2_xiaxian))
							{
								y1 = alerty2+5;
								break;
							}
						}
				}
			else 
				{
					GetMinWaveNum(databuf,72,63,databuf->getdataLens(74),usb8221par.block,set.timelapes[2],y1);
					if (y1>alerty2_xiaxian)
						{
							y1 = alerty2 + 5;
						}
				}	
	
			if((y1 >alerty2)&&(vlastAlermpt+alert2_num*usb8221par.block < len2))
				{
				
					
					g->goodflag = FALSE;
					CScarData::alertflag = TRUE;
					CScarData::alertSingle2 = 2;
				//	usbcard->SendDigitalOuput2(16,TRUE);
			
				}	

			for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum*2; j++)
				{
					databuf->increaeDataLen(j,usb8221par.block);
				}
			
		}
		break;
	case L82SCARSTATUS_BOTH:
	case L82SCARSTATUS_DEMARCATE:
		{
			len = databuf->getdataLens(4);
			len2 = databuf->getdataLens(68);
			for(int i = 0; i < usb8221par.block;i++)
				{			
			
					for(int j = 0; j < 68; j++)
					{								
			
						data[j][len+i] = abs(ADBuf[j+(i*usb8221par.channelnum)+1]-32767)/8;
					}
					
					for( j = 68; j < 136; j++)
					{ 					 				        
				
						data[j][len2+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8;
					}
				}
			if(alertbyshow1 == WaveShowStyle_SimpleShow )
			{
				getShowWaveNum(databuf,4,63,len,usb8221par.block,set.timelapes[0],y0);
				if (y0>alerty1_xiaxian)
				{
					y0 = alerty1 + 5;
				}

			}
	

			if( alertbyshow2 == WaveShowStyle_SimpleShow )	
			{
				getShowWaveNum(databuf,72,63,len2,usb8221par.block,set.timelapes[2],y1);
				if (y1>alerty2_xiaxian )
					{
						y1 = alerty2 + 5;
					}
			}
			
			else if( alertbyshow2 == WaveShowStyle_Difference )
				{
					for(int k = 72 ; k < 135 ;k++)
						{
							GetWaveNum(databuf,k,len2,usb8221par.block,set.timelapes[2],y1);
							if( (y1 > alerty2))
								{
									y1 = alerty2 + 5;
									break;
								}
						}
				}
			else 
				{
					GetMinWaveNum(databuf,72,63,databuf->getdataLens(74),usb8221par.block,set.timelapes[2],y1);//5-14
					if (y1>alerty2_xiaxian)
						{
							y1 = alerty2 + 5;
						}
				}
			
			if((y0>alerty1)&&(hlastAlermpt+alert1_num*usb8221par.block <len))	
				{
					hlastAlermpt = len;
					g->goodflag = FALSE;
					CScarData::alertflag = TRUE;
					CScarData::alertSingle1 = 1;
				//	usbcard->SendDigitalOuput(16,TRUE);	
				}
			if((y1 >alerty2)&&(vlastAlermpt+alert2_num*usb8221par.block<len2))
				{
					vlastAlermpt = len2;
					g->goodflag = FALSE;
					CScarData::alertflag= TRUE;
					CScarData::alertSingle2 = 1;
				//	usbcard->SendDigitalOuput2(16,TRUE);
				}	
			for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum*2; j++)
				{
					databuf->increaeDataLen(j,usb8221par.block);
				}
		}
		break;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

	case L82SCARSTATUS_VERTICAL1_VERTICAL2:
	{
		len2 = databuf->getdataLens(68);
		for(int i = 0; i < usb8221par.block;i++)
			{
				for(int j=68;j<136;j++)
				{ 
					data[j][len2+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8;
				}
			}
     
		if( alertbyshow2 == WaveShowStyle_SimpleShow )
			{
				getShowWaveNum(databuf,72,63,len2,usb8221par.block,set.timelapes[2],y1);
				if (y1>alerty2_xiaxian)
					{
						y1 = alerty2 + 5;
					}
			}
		else if( alertbyshow2 == WaveShowStyle_Difference )
			{
				for(int k = 72 ; k < 135 ;k++)
					{
						GetWaveNum(databuf,k,len2,usb8221par.block,set.timelapes[2],y1);
						if( (y1 > alerty2_xiaxian))
							{
								y1 = alerty2 + 5;
								break;
							}
					}
			}
	
		else 
			{
				GetMinWaveNum(databuf,72,63,databuf->getdataLens(74),usb8221par.block,set.timelapes[2],y1);//5-14	
				if (y1>alerty2_xiaxian)
					{
						y1 = alerty2 + 5;
					}
			}
				
		if((y1 > alerty2 )&&(vlastAlermpt+alert2_num*usb8221par.block<len2))
			{
				vlastAlermpt = len2;
				CScarData::alertflag= TRUE;
				CScarData::alertSingle2 = 1;
				usbcard->SendDigitalOuput2(16,TRUE);
				
			}			
		for(int j = 68; j < 136; j++)
			{
				databuf->increaeDataLen(j,usb8221par.block);
			}
	}	
		break;	



	case L82SCARSTATUS_VERTICAL2:
	{
		len2 = databuf->getdataLens(68);
		for(int i = 0; i < usb8221par.block;i++)
			{


					for( int j = 72; j < 76; j++)
					{ 					 				        
						data[j][len2+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}

					for( j = 80; j < 84; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 88; j < 92; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 96; j < 100; j++)
					{ 					 				        
						data[j][len2+i] = abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 104; j < 108; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					for( j = 112; j < 116; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}

					for( j = 120; j < 124; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}

					for( j = 128; j < 132; j++)
					{ 					 				        
						data[j][len2+i] =  abs(ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1]-32767)/8 ;
					}
					
					
					for( j = 76; j < 80; j++)
					{ 					 				        
						data[j][len2+i] = stdline[j];
					}
					for( j = 84; j < 88; j++)
					{ 					 				        
						data[j][len2+i] = stdline[j];
					}
					for( j = 92; j < 96; j++)
					{ 					 				        
						data[j][len2+i] = stdline[j];
					}
					for( j = 100; j < 104; j++)
					{ 					 				        
						data[j][len2+i] = stdline[j];
					}
					for( j = 108; j < 112; j++)
					{ 					 				        
						data[j][len2+i] = stdline[j];
					}

					for( j = 116; j < 120; j++)
					{ 					 				        
						data[j][len2+i] = stdline[j];
					}
					for( j = 124; j < 128; j++)
					{ 					 				        
						data[j][len2+i] = stdline[j];
					}

					for( j = 132; j < 136; j++)
					{ 					 				        
						data[j][len2+i] = stdline[j];
					}


		}

			if( alertbyshow2 == WaveShowStyle_SimpleShow )	
			{
				getShowWaveNum(databuf,72,63,len2,usb8221par.block,set.timelapes[2],y1);
					if (y1>alerty2_xiaxian)
					{
						y1 = alerty2 + 5;
					}
			}
			else if( alertbyshow2 == WaveShowStyle_Difference )
				{
					for(int k = 72 ; k < 135 ;k++)
						{
							GetWaveNum(databuf,k,len2,usb8221par.block,set.timelapes[2],y1);
							if( (y1 > alerty2_xiaxian))
							{
								y1 = alerty2 + 5;
								break;
							}
						}
				}	
			else 
				{
					GetMinWaveNum(databuf,72,63,databuf->getdataLens(74),usb8221par.block,set.timelapes[2],y1);//5-14
					if (y1>alerty2_xiaxian)
						{
							y1 = alerty2 + 5;
						}
				}
			if((y1 > alerty2)&&(vlastAlermpt+alert2_num*usb8221par.block<len2))
			{	
				vlastAlermpt = len2;
				CScarData::alertflag= TRUE;
				CScarData::alertSingle2 = 1;
				usbcard->SendDigitalOuput2(16,TRUE);
			}	
		
			for( int j = 68; j < 136; j++)
			{
				{
					databuf->increaeDataLen(j,usb8221par.block);
				}
			}
		
		
	}	
		break;	

	}

	return TRUE;
}

BOOL CScarData::autoSampleFuc()
{
	const int num = 3;//5;
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	RbhUsb20* usbcard = (RbhUsb20*)(TestSampleControl::cardPtr);
	DataBuf* databuf = g->getDataBuf();
//	WORD** data = databuf->getDataPtr();

	if(CScarData::alertflag == TRUE)
	{
		if( alertSingle1 == 1)
			usbcard->SendDigitalOuput(16,TRUE);	
		if(alertSingle2 == 1)
			usbcard->SendDigitalOuput2(16,TRUE);
		CScarData::alertflag = FALSE;
		CScarData::alertSingle1 = 0;
		CScarData::alertSingle2 = 0;
	}
	
	
	for(int i = 0; i < num; i++)
	{
	//	char DI = usbcard->GetDigitalInputByNet();
		int Bit1 = 16;//头四位给编码器使用。
		int Bit2 = 16;
		int Bit3 = 32;
		int Bit4 = 32;
		BYTE DI1 = usbcard->GetDigitalInput();
		BYTE DI2 = usbcard->GetDigitalInput1();
// 直接开关量信号
		Bit1 = Bit1&DI1;
		Bit2 = Bit2&DI2;

// 电子阀延迟信号		
		Bit3 = Bit3&DI1;
		Bit4 = Bit4&DI2;

// 任务循环15毫秒
		switch(l82ScarStatus)
		{
		case L82SCARSTATUS_STOP://横向
			{
				if(Bit3 == 0  && Bit4 == 32)  
				{
					bit1num++;	
					if(bit1num == num)
					{
						bit1num = 0;
						bit2num = 0; 
						indexAlert = 0;
						indexAlert2 = 0;
						hlastAlermpt = 0;
						vlastAlermpt = 0;
						CScarData::alertflag = FALSE;
						CScarData::alertSingle1 = 0;
						CScarData::alertSingle2 = 0;
						l82ScarStatus =L82SCARSTATUS_HORIZONTAL;
				        ::SendMessage(g->Dlghandle,WM_NEW_MSG,NEWONE_NEXT,0);
					}
				}
				else
				{
					bit1num = 0; 
				}
			
			}
			break;
		case L82SCARSTATUS_HORIZONTAL://横向纵向1
			
			{			
				if(Bit3== 0  && Bit4== 0  )     
				{
					bit2numhead++;	
					if(bit2numhead == num )    //第二个触发
					{					
						bit2numhead = 0;
						l82ScarStatus = L82SCARSTATUS_HORIZONTAL_VERTICAL1;			
					}		
				}
				else
				{
					bit2numhead = 0; 
				}
				
			}
			break;

		case L82SCARSTATUS_HORIZONTAL_VERTICAL1://横向纵向1、2
			
			{	
				if(Bit3 == 0 && Bit4 == 0)
				{
					vLengthhead =  databuf->getdataLens(72);	//实际板卡通道决定getdataLens(4)
					if (vLengthhead>=set.timelapes[4])
					{
						bit2num++;
						if (bit2num == num)
						{
							bit2num = 0;
							l82ScarStatus = L82SCARSTATUS_BOTH;	
						}
						
					}
				}		
			}
			break;

		case L82SCARSTATUS_BOTH://纵向1、2
		case L82SCARSTATUS_DEMARCATE:
			{			
		//		DataBuf* databuf = g->getDataBuf();
				hLengthend = databuf->getdataLens(67);
				if( Bit3 == 32  && hLengthend>set.timelapes[5]*100)   //第一个触发（反）
				{					
					end1num++;	
					if(end1num > num )    //第二个触发
					{					
						end1num = 0;//tck1 = 0;//	zxstart=0;
						l82ScarStatus = L82SCARSTATUS_VERTICAL1_VERTICAL2;					

					}
				}
				else
				{
					end1num= 0;
				}
				
			}
			break;


	case L82SCARSTATUS_VERTICAL1_VERTICAL2://纵向2
			{			

				if( Bit2 = 16)   //第一个触发（反）
				{					
					end2numtail++;	
					if(end2num == num )    //第二个触发
					{					
						end2numtail = 0;//tck1 = 0;//	zxstart=0;
						l82ScarStatus = L82SCARSTATUS_VERTICAL2;
					}					
				}
				else
				{
					end2numtail= 0;
				}	
			}
			break;

		case L82SCARSTATUS_VERTICAL2:
			{
			//	DataBuf* databuf = g->getDataBuf();
			
				vLengthend= databuf->getdataLens(72);
				if (vLengthend>=set.timelapes[6]*100)
				{
						end2num++;
						if (end2num == num)
						{
							end2num =0;
							l82ScarStatus = L82SCARSTATUS_STOP;
							::SendMessage(g->Dlghandle,WM_NEW_MSG,COMPLETE_THIS,0);
							return FALSE;
						}		
				}
			
			}
			break; 
		}
	}
	return FALSE;
}

void CScarData::DoReport(CListCtrl& list, BOOL doexcel)
{
	GobalData* g = GobalData::getGobalData();
// 	AUTOSET set = g->getAutoSet();
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
		
		list.InsertColumn(0,"信息  ",LVCFMT_LEFT,130,-1);
		list.InsertColumn(1,"内容  ",LVCFMT_LEFT,130,-1);
//		list.InsertColumn(2,"长度  ",LVCFMT_LEFT,80,-1);

		list.InsertItem(0,"");
		list.SetItemText(0,0,"文件名");
		
		list.InsertItem(1,"");
		list.SetItemText(1,0,"检测日期");
		
		list.InsertItem(2,"");
		list.SetItemText(2,0,"操作员");

		list.InsertItem(3,"");
		list.SetItemText(3,0,"规格");
		
		list.InsertItem(4,"");
		list.SetItemText(4,0,"钢级");

		list.InsertItem(5,"");
		list.SetItemText(5,0,"壁厚");
	
		list.InsertItem(6,"");
		list.SetItemText(6,0,"总根数");
		
		list.InsertItem(7,"");
		list.SetItemText(7,0,"一级根数");

		list.InsertItem(8,"");
		list.SetItemText(8,0,"二级根数");

		list.InsertItem(9,"");
		list.SetItemText(9,0,"报废根数");
		
		
		list.InsertItem(10,"");
		list.SetItemText(10,0,"当前杆等级");
		
		if(g->getFilePtr() != NULL)
		{
			str.Format("%s",g->getWholeFileName());
			list.SetItemText(0,1,str);

			str.Format("%4d-%02d-%02d",g->dataHead.year,g->dataHead.month,g->dataHead.day);
			list.SetItemText(1,1,str);

			str.Format("%s",g->dataHead.Uoperator);
			list.SetItemText(2,1,str);

			str.Format("%s",g->dataHead.guige);
			list.SetItemText(3,1,str);

			str.Format("%s",g->dataHead.steel);
			list.SetItemText(4,1,str);
			
			str.Format("%s",g->dataHead.ply);
			list.SetItemText(5,1,str);

			str.Format("%d",g->dataHead.blocksum);
			list.SetItemText(6,1,str);

// 			str.Format("%d",g->dataHead.blocksum);
// 			list.SetItemText(0,1,str);
//             str.Format("%0.2f m",g->dataHead.datasum*set.speed/spic);
// 			list.SetItemText(0,2,str);

			str.Format("%d",g->dataHead.goodsum2);
			list.SetItemText(7,1,str);
// 			str.Format("%0.2f m",g->dataHead.gooddatasum*set.speed/spic);
// 			list.SetItemText(1,2,str);

			str.Format("%d",g->dataHead.goodsum);
			list.SetItemText(8,1,str);


			str.Format("%d",g->dataHead.blocksum-(g->dataHead.goodsum2+g->dataHead.goodsum));
			list.SetItemText(9,1,str);
// 			str.Format("%0.2f m",(g->dataHead.datasum-g->dataHead.gooddatasum)*set.speed/spic);
// 			list.SetItemText(2,2,str);
			if((g->blockHead.good == TRUE)&&(g->blockHead.good2 == FALSE))
				str.Format("二级");
			else if(g->blockHead.good2 == TRUE)
				str.Format("一级");
			else
				str.Format("报废");
			list.SetItemText(10,1,str);
// 			str.Format("%0.2f m",g->blockHead.blocksum*set.speed/spic);
// 			list.SetItemText(8,2,str);
		}

		list.InsertItem(11,"");
		list.SetItemText(11,0,"当前杆时间");
		CString str;
		str.Format("%02d点%02d分",(g->blockHead).hour,(g->blockHead).min);
		list.SetItemText(11,1,str);

//		list.InsertItem(5,"");
//		list.SetItemText(5,0,"当前流水号");
//		str.Format("%d",g->blockHead.sid<0?0:g->blockHead.sid);
//		list.SetItemText(5,1,str);
	}
}

void CScarData::DoDataBase()
{

}
//int xneishang1,xneishang2;
//bool neishangchek= FALSE;
//bool neishangchek2= FALSE;
//char cutch[136];
void CScarData::getShowWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int max = -2048;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
#if 0	
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	int  End_maxValue =2048*set.timelapes[5]/100;
	extern BOOL showLengthRule;
#endif
	double z = double(pars[ch])/20;

	reBuf = 0;
	if( timelapes > startNum )
		{
			return ;
		}		  
	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			int y = abs(data[ch][i] - stdline[ch])*pow(10,z)/100;
			if(y > max)
				max = y;
		}
	reBuf = max >  2048 ? 2048 : max;
}

void CScarData::getShowWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int max = -2048;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();

	reBuf = 0;

	if( timelapes > startNum )
		{
			return ;
		}
	for(int ch = startch; ch <= startch + chnum; ch++)
	{
		double z = double(pars[ch])/20; 
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			int y = abs(data[ch][i] - stdline[ch])*pow(10,z)/100;
			if(y > max)	max = y;
		}	
	}
	reBuf = max >  2048 ? 2048 : max;
}

void CScarData::VendgetShowWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int max = -2048;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	reBuf = 0;

	if( timelapes > startNum )
		{
			return ;
		}
	for(int ch = startch; ch <= startch + chnum; ch++)
	{
		double z = double(pars[ch])/20; 
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			int y = abs(data[ch][i] - stdline[ch])*pow(10,z)/100;
			if(y > max)	max = y;
		}	
	}
	reBuf = max >  2048 ? 2048 : max;
}


void  CScarData::getShowWaveNum3(DataBuf *buf, int ch, int startNum, int blocklen,int &reBuf)
{
	int max = -2048;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	
	reBuf = 0;
	if( buf->getdataLens(ch) < 	2*blocklen )
		return;

	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		double z = double(pars[ch])/20; 
		int y = (data[ch][i] - stdline[ch])*pow(10,z)/100;
//历史数据分析，看原始值。
	
		if(y > max)
			max = y;
	}
	max = max >  2048 ? 2048 : max;
	max = max <  -2048 ? -2048 : max;
	reBuf = max;
}

BOOL CScarData::savePerBlockData(CFile *file, BLOCKHEAD *bHead, int &len, CSampleCard *card, int id)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	CTime t = CTime::GetCurrentTime();
	int ch = card->getChannelNum();	
	int tsum = 0;

	for(int   i = 0; i <  g->MAXCHANNEL; i++)
	{
        int len = buf->getdataLens(i);
		tsum += len;
	}
	int datasum = tsum*sizeof(short) +  (g->MAXCHANNEL)*sizeof(int) + sizeof(BLOCKHEAD); //单块总数据量
    //20通道的len本身int
	file->Write(&datasum,sizeof(int));  //写入单块总长度
	//
	bHead->hour = t.GetHour();
	bHead->min  = t.GetMinute();
	bHead->good = indexAlert>0?FALSE:TRUE;
	bHead->good2 =indexAlert2>0?FALSE:TRUE;
	bHead->blocksum =0;//无意义
	bHead->id = id;
//	bHead->VendPt = vEndCutTime;
//	bHead->HendPt =hEndCutTime;
	bHead->XPt[0] = recordXPt[0];
	bHead->XPt[1] = recordXPt[1];
	bHead->XPt[2] = recordXPt[2];
	bHead->XPt[3] = recordXPt[3];
	bHead->XPt[4] = recordXPt[4];
	bHead->XPt[5] = recordXPt[5];
	bHead->XPt[6] = recordXPt[6];
	bHead->XPt[7] = recordXPt[7];
	bHead->XPt[8] = recordXPt[8];
	bHead->XPt[9] = recordXPt[9];
	bHead->weldNum=indexAlert;
	bHead->xlength =  buf->getdataLens(8);

	bHead->YPt[0] = recordYPt[0];
	bHead->YPt[1] = recordYPt[1];
	bHead->YPt[2] = recordYPt[2];
	bHead->YPt[3] = recordYPt[3];
	bHead->YPt[4] = recordYPt[4];
	bHead->YPt[5] = recordYPt[5];
	bHead->YPt[6] = recordYPt[6];
	bHead->YPt[7] = recordYPt[7];
	bHead->YPt[8] = recordYPt[8];
	bHead->YPt[9] = recordYPt[9];
	bHead->weldNum2=indexAlert2;
	bHead->ylength =  buf->getdataLens(88);
	file->Write(bHead,sizeof(BLOCKHEAD));
    //写单块头
	//写数据
   	for(     i = 0; i < g->MAXCHANNEL; i++)  //
	{
		WORD** data = buf->getDataPtr();
		int len = buf->getdataLens(i);
		file->Write(&len,sizeof(int));
		file->Write(data[i],buf->getdataLens(i)*sizeof(short));
	}

	file->Write(&datasum,sizeof(int));  //写入单块总长度
	len = datasum;                      //返回值
//	file->Flush();
//	memset(recordXPt,0,10*sizeof(int));
//	memset(recordYPt,0,10*sizeof(int));
    return TRUE;
}

BOOL CScarData::loadPerBlockData(CFile *file, BLOCKHEAD *bHead, int &len)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();

	int datasum;	
	file->Read(&datasum,sizeof(int));  //读单块总长度
	//
	file->Read(bHead,sizeof(BLOCKHEAD));
    //读单块头
	recordXPt[0] =bHead->XPt[0] ;
	recordXPt[1] =bHead->XPt[1] ;
	recordXPt[2] =bHead->XPt[2] ;
	recordXPt[3] =bHead->XPt[3] ;
	recordXPt[4] =bHead->XPt[4] ;
	
	recordYPt[0] =bHead->YPt[0] ;
	recordYPt[1] =bHead->YPt[1] ;
	recordYPt[2] =bHead->YPt[2] ;
	recordYPt[3] =bHead->YPt[3] ;
	recordYPt[4] =bHead->YPt[4] ;
	indexAlert= bHead->weldNum;
	indexAlert2= bHead->weldNum2;

//	vEndCutTime= bHead->VendPt;
//	hEndCutTime=bHead->HendPt;
	//读数据
    for(int i = 0; i < g->MAXCHANNEL; i++)  //从第0通道开始，根据通道数量读取数据
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
	if(bHead->xlength==0 )
		bHead->xlength = buf->getdataLens(8);
	if(bHead->ylength==0 )
		bHead->ylength = buf->getdataLens(88);
		
#ifdef AddYcord
	if( addOrDel )
		{
			//检查横向内伤,查看历史没记录的数据
			if(abs(recordXPt[0] -lastXpt[0])>400 )
			{
				recordXPt[0]= lastXpt[0];					
				xLostpt = TRUE;
			}
			else
				xLostpt = FALSE;
			if(abs(recordYPt[indexAlert2-1] -lastYpt[2])>400 )
			{
				recordYPt[indexAlert2]= lastYpt[2];					
				YLostpt = TRUE;indexAlert2++;
			}
			else
				YLostpt = FALSE;
		}

#endif
   return TRUE;
}

short CScarData::getSaveNum(DataBuf *buf, int ch, int startNum, int blocklen)
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

void CScarData::endSampleData()
{

}

//void CScarData::GetFaultNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int &reBuf)
//{
//		int max = 0;
//		short* pars = buf->getParPtr();
//		short* stdline = buf->getStdPtr();
//		short** fault = buf->GetFaultPtr();
//		max = (fault[startch][startNum] - stdline[startch])*pars[startch]/100;
//		for(int ch = startch; ch <= startch + chnum; ch++)
//		{
//			for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
//			{
//				int y = (fault[ch][i] - stdline[ch])*pars[ch]/100;
//				if(i<=3300 && ch <= 16)
//					y = 0;
//				if(y > max)
//					max = y;
//			}
//		}
//		max = max >  2048 ? 2048 : max;
//		max = max < -2048 ? -2048 : max;
//		reBuf = max;
//}
#if 0
void CScarData::GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int max1 = -2048;
	int max2 = -2048;
	int max = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	short** data = buf->getDataPtr();
	short level = 2048*20/100;
	
	reBuf = 0;
	if( buf->getdataLens(ch) < 	2*blocklen )
		return;

	if( timelapes > startNum )
		return ;

	if(ch == 103 || ch == 135 )
		{
			double z1 = double(pars[ch])/20; 
			for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
			{
				int y1 = (data[ch][i] - stdline[ch])*pow(10,z1)/100;
				if(y1 > max)			
					max = y1;
			}
			if(max < level)
				reBuf = max;
			else
				reBuf = 0;
			return ;
		}
	
	double z1 = double(pars[ch])/20; 
	double z2 = double(pars[ch+1])/20; 

	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		int y1 = (data[ch][i] - stdline[ch])*pow(10,z1)/100;
		int y2 = (data[ch+1][i] - stdline[ch+1])*pow(10,z2)/100;
		if(y1 > max1)
			max1 = y1;
		if(y2 > max2)
			max2 = y2;		
	}
	if(max1 >= level && max2>= level )
		{
			max = (max1+max2)/2;
		}
	else
		{
			max = max1;
		}
	max = max >  2048 ? 2048 : max;
	max = max <  -2048 ? -2048 : max;
	reBuf = max;
} 
#else
void CScarData::GetWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int max1 = -2048;
	int max2 = -2048;
	int max = 0;
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	short level =(2048*set.alertline2[2])/100;// (2048*set.alertline2[2])/100;//过滤门限
	short* pars = buf->getParPtr();
	double z = double(pars[ch])/20;
//纵向两屏的最后一个通道不用重复计算。
	if( z == 0 ||ch == 103 || ch == 135 )
		{
			reBuf = 0;
			return ;
		}	
	
//	for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
	{
		GetDifferWaveNum(buf,ch,startNum,blocklen,timelapes,max1);
		GetDifferWaveNum(buf,ch+1,startNum,blocklen,timelapes,max2);
	}
	if(max1 > level && max2> level )
		{
			max = (max1+max2);
		}
	else
		{
			max =  max1 >  max2 ? max2 : max1;
		}
	max = max >  2048 ? 2048 : max;
//	max = max <  -2048 ? -2048 : max;
	reBuf = max;
#if 0
	if( ch >= 71  && vEndCutTime <startNum && vEndCutTime != 0 &&  ch % 8 > 3  )
	{
			reBuf =0;
	}
#endif

}	
#endif
void CScarData::GetWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	
}

void CScarData::GetMinWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET set = g->getAutoSet();
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	int y1 = 0,y2 = 0,y3 = 0, y4 = 0;
	int max = 0;
//	int headdelay  =  set.alertline3[2];
	
	if( timelapes > startNum )
		{
			reBuf = 0;
			return ;
		}

	for(int ch = startch; ch <= startch + chnum; ch++)
	{
#if 1
		double z = double(pars[ch])/20;
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			if (i<2*set.differ[0])
			{
				max = 0;
			}
			else
			{				
				y1 = (data[ch][i] - stdline[ch])*pow(10,z)/100;
				y2 = (data[ch][i-set.differ[ch/32]] - stdline[ch])*pow(10,z)/100;
				y3 = (data[ch][i-2*set.differ[ch/32]] - stdline[ch])*pow(10,z)/100;			
				y4 = y1+y3-2*y2;
				y4 = abs(y4*set.differadjust[ch/32])/100;
				if(y4 > max)
					max = y4;
			}
		}
#endif		//DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
	//	GetWaveNum(buf,ch,startNum,blocklen,timelapes,y4);
	//	if(y4 > max)	max = y4;
	}
	max = max >  2048 ? 2048 : max;
	max = max < 0 ? 0 : max;
	reBuf = max;
#if 0
	if( ch >= 71  && vEndCutTime <( startNum/* +set.alertline3[3] */) && vEndCutTime != 0 &&  ch % 8 > 3  )
	{
			reBuf =0;
	}
#endif


}

void CScarData::GetAvgWaveNum(DataBuf *buf, int startch, int chnum, int startNum, int blocklen, int timelapes, int &reBuf)
{
	int sum = 0;
	int avg = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	
	for(int ch = startch; ch <= startch + chnum; ch++)
	{
		int sum = 0;
		for(int i = startNum; i < startNum+blocklen; i++)    //取最大值显示
		{
			double z = double(pars[ch])/20; 
			int y = abs(data[ch][i] - stdline[ch])*pow(10,z)/100;
			sum+= y;
		}
		avg += sum/blocklen;
	}
	reBuf = avg/(chnum+1);
}

void CScarData::GetDifferWaveNum(DataBuf *buf, int ch, int startNum, int blocklen, int timelapes, int &reBuf)
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	int max = 0;
	int y1 = 0,y2 = 0,y3 = 0;
	int y4 = 0;
	short* pars = buf->getParPtr();
	short* stdline = buf->getStdPtr();
	WORD** data = buf->getDataPtr();
	int y = 0;
//	int headdelay  =  set.alertline3[2];//纵向头部，后4通道

	reBuf = 0;
//	if( buf->getdataLens(ch) < 	2*blocklen )
//		return;

	if( timelapes > startNum )
		{
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
			y1 = (data[ch][i] - stdline[ch])*pow(10,z)/100;
			y2 = (data[ch][i-set.differ[ch/32]] - stdline[ch])*pow(10,z)/100;
			y3 = (data[ch][i-2*set.differ[ch/32]] - stdline[ch])*pow(10,z)/100;			
			y4 = y1+y3-2*y2;
			y4 = abs(y4*set.differadjust[ch/32])/100;
		/*	if( ch > 70 && i < 5000 && set.alertline3[2] > 0)
 			{ 	 				 
				if( abs(data[ch][i] -stdline[ch]) > 200 )
					{				
						if( i < set.alertline3[2] )
						y4 = y4/10;//+ stdline[ch];
					}
			}*/

			if(y4 > max)
				max = y4;
		}
	}
		
	max = max >  2048 ? 2048 : max;
	max = max < 0 ? 0 : max;
	reBuf = max;

#if 0
	if( ch >= 71  && (vEndCutTime+set.alertline3[3] )< startNum && vEndCutTime != 0 &&  ch % 8 > 3  )
	{
			reBuf =0;
	}
#endif

}
