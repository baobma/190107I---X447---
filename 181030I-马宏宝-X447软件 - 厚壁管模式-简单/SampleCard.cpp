// SampleCard.cpp: implementation of the CSampleCard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SampleCard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSampleCard::CSampleCard(const int sampleSpeed,const int channelNum)
{
    setChannelNum(channelNum);
	setSampleSpeed(sampleSpeed);
}

CSampleCard::~CSampleCard()
{
    
}

int CSampleCard::getSampleSpeed()
{
    return sampleSpeed;
}

void CSampleCard::setSampleSpeed(const int speed)
{
    sampleSpeed = speed;
}

void CSampleCard::setChannelNum(const int channel)
{
    channelNum = channel;
}

int CSampleCard::getChannelNum()
{
    return channelNum;
}

