// SRoomSample.cpp: implementation of the SRoomSample class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "SRoomSample.h"
#include "TestSampleControl.h"
#include "GobalData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SRoomSample::SRoomSample()
{
    compress = 1;       //压缩比为1
	suffix = "srs";
}

SRoomSample::~SRoomSample()
{

}

BOOL SRoomSample::getDateFromCard()
{
    GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();
	WORD** data = databuf->getDataPtr();
	USB8221par usb8221par = g->getUsb8221Par();
	WORD* ADBuf = ((RbhUsb20*)(TestSampleControl::cardPtr))->getADbuf();
	
	if(databuf->getdataLens(usb8221par.startch) >= g->getDataLen())
	{
		return FALSE;		
	}
	int index = 0;
	static BOOL oldflag = FALSE;
	for(int i = 0; i < usb8221par.block;i++)  /*1~16通道有效数据*/
	{
		short td = ADBuf[16 + (i*usb8221par.channelnum) + 1];
		BOOL flag = FALSE;
		if(td >= 3000)
			flag = TRUE;
		if(oldflag == FALSE && flag == TRUE)
		{
			for(int j = usb8221par.startch; 
			j < usb8221par.startch+usb8221par.channelnum; j++)
			{
				
				if( ( j >= 1-1 && j <= 16-1 ))
				{
					int len = databuf->getdataLens(j);
					data[j][len+index] = ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1];
				}		
			}
			++index;
		}
		oldflag = flag;
	}
	
	for(int j = usb8221par.startch; 
	j < usb8221par.startch+usb8221par.channelnum; j++)
	{
		if( ( j >= 1-1 && j <= 16-1 ))
		{
			databuf->increaeDataLen(j,index);
		}
	}		
		
    return TRUE;
}
