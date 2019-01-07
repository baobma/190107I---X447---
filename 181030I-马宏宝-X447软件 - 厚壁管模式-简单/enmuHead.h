#ifndef ENMU_HEAD
#define ENMU_HEAD

enum WaveShowNum
{
	WaveShowNum_ONE = 1, WaveShowNum_TWO = 2, WaveShowNum_THREE = 3,WaveShowNum_FOUR  = 4, 
	WaveShowNum_FIVE = 5, WaveShowNum_SIX = 6, WaveShowNum_SEVEN = 7, WaveShowNum_EIGHT = 8,
};

enum WorkModel
{
	WorkModel_SINGLE, WorkModel_NETWORK
};

enum DLGNEWMSG_CMD
{
	COMPLETE_THIS, NEWONE_NEXT
};

enum Status
{
	Status_STOP,      //停止状态
	Status_START,     //采集状态
	Status_DEMORATE,  //标定状态
	Status_REVIEW,    //数据回放
	Status_CH_REVIEW, //通道回放
};

enum ButtonFlag
{
	ButtonFlag_UP, ButtonFlag_DOWN, ButtonFlag_BACK, ButtonFlag_LAST
};

enum SaveStyle
{
	SimpleData, 
//	SimpleCopData,
//	Testline78data,
//	TestlineSv3data,
//	SRoomSampledata,
//	Floordata,
	ExploreScarData,
	ExplorePlyData
};

enum WaveShowStyle
{
	WaveShowStyle_SimpleShow ,   //简单显示
	WaveShowStyle_Combine    ,      //多通道融合（为一个通道）显示
	WaveShowStyle_Fault      ,
	WaveShowStyle_Differ     ,
	WaveShowStyle_Phase      ,
	WaveShowStyle_Ply        ,
	WaveShowStyle_Difference ,
//	WaveShowStyle_ThickPipe,
};

enum ProcessMsg
{
	PROCESSMSG_SELNUM, PROCESSMSG_VIEWNUM, PROCESSMSG_SAVEDATA, PROCESSMSG_PARNEED,
	PROCESSMSG_PARSAVE, PROCESSMSG_UPDATE
};
#endif