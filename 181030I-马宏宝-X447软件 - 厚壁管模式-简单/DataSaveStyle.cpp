// DataSaveStyle.cpp: implementation of the DataSaveStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "DataSaveStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DataSaveStyle::DataSaveStyle()
{
	needTrigger = FALSE;
}

DataSaveStyle::~DataSaveStyle()
{

}

char* DataSaveStyle::getSuffix()
{
    return suffix;
}

int DataSaveStyle::getCompress()
{
    return compress;
}

BOOL DataSaveStyle::IsNeedTrigger()
{
    return needTrigger;
}
