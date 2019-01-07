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
	Status_STOP,      //ֹͣ״̬
	Status_START,     //�ɼ�״̬
	Status_DEMORATE,  //�궨״̬
	Status_REVIEW,    //���ݻط�
	Status_CH_REVIEW, //ͨ���ط�
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
	WaveShowStyle_SimpleShow ,   //����ʾ
	WaveShowStyle_Combine    ,      //��ͨ���ںϣ�Ϊһ��ͨ������ʾ
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