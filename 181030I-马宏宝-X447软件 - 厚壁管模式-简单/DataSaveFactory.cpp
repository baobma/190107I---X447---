// DataSaveFactory.cpp: implementation of the DataSaveFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "DataSaveFactory.h"
#include "SimpleDataSave.h"
#include "SimpleCompressData.h"
#include "Tline78data.h"
#include "TLineSv3.h"
#include "SRoomSample.h"
#include "StyleForFloordata.h"
#include "ScarData.h"
#include "PlyData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DataSaveFactory::DataSaveFactory()
{

}

DataSaveFactory::~DataSaveFactory()
{

}

/*
 *	根据数据保存风格标志产生数据保存格式对象
 */
DataSaveStyle* DataSaveFactory::getDataSaveStyle(SaveStyle s)
{
	switch(s) 
	{
	case SimpleData: return new SimpleDataSave();
		break;
// 	case SimpleCopData: return new SimpleCompressData();
// 		break;
//	case Testline78data: return new CTLine78data();
//		break;
//	case TestlineSv3data: return new CTlineSv3();
//		break;
//	case SRoomSampledata: return new SRoomSample();
//		break;
//	case Floordata : return new StyleForFloordata();
//		break;
 	case ExploreScarData:  return new CScarData();
 		break;
	case ExplorePlyData:   return new CPlyData();
		break;
	default: return NULL;
	}
}
/*
 *	根据后缀产生数据保存格式对象
 */
DataSaveStyle* DataSaveFactory::getDataSaveStyle(char *suffix)
{
     if(strcmp(suffix,"ord") == 0)
	 {
		 return new SimpleDataSave();
	 }
// 	 else if(strcmp(suffix,"scd") == 0)
// 	 {
// 		 return new SimpleCompressData();
// 	 }
//	 else if(strcmp(suffix,"78d") == 0)
//	 {
//		 return new CTLine78data();
//	 }
//	 else if(strcmp(suffix,"sv3") == 0)
//	 {
//		 return new CTlineSv3();
//	 }
//	 else if(strcmp(suffix,"srs") == 0)
//	 {
//		 return new SRoomSample();
//	 }
//	 else if(strcmp(suffix,"flr") == 0)
//	 {
//		 return new StyleForFloordata();
//	 }
 	 else if (strcmp(suffix,"emt") == 0)
 	 {
 		 return new CScarData();
 	 }
	 else if (strcmp(suffix,"emt") == 0)
	 {
		 return new CPlyData();
	 }
	 return NULL;
}
