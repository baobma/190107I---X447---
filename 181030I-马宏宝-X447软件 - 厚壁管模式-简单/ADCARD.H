/* head file for adcard.h
  service dll for AD Card.
  Copyright(C) RBH, Sept.2, 1998
  */
#if !defined(AFX_AD_CARD_H_5D8D7FD00DD9__INCLUDED_)
#define AFX_AD_CARD_H_5D8D7FD00DD9__INCLUDED_


//for 8~16 bit AD
typedef unsigned short ADValueType;

// for high precision, >16 bit AD 
//typedef unsigned long ADValueType;

//AD Result Struct
typedef struct structADResult {
  ADValueType SeqNo;
  ADValueType ADValue[1];
} ADCard_Result;

//API return value
#define ADCard_Success  1
#define ADCard_Error  0
#define NumNotify 4

//exported API

#ifdef __cplusplus
extern "C" {
#endif

  //Initial(): Return ADCard_Error or ADCard_Success
int __stdcall Initial(WORD IOBase, WORD IRQNum, DWORD PhysAddr,WORD DMAChn);

  //StartIntr(): Retur 0 or BuffSize
DWORD __stdcall StartIntr(WORD NumBuf, DWORD NumSamp,\
                          WORD BegChn, WORD NumChn, \
                          DWORD FrqSamp, DWORD FrqFilter,\
                          WORD AmpGain);
  //StartSnapshot(): Retur ADCard_Error or ADCard_Success
DWORD __stdcall StartSnapshot(WORD NumBuf, DWORD NumSamp,\
                          WORD BegChn, WORD NumChn,\
                          DWORD FrqSamp, DWORD FrqFilter,\
                          WORD AmpGain,DWORD NotifyLength);
  //RegisterNotify(): Return ADCard_Error or ADCard_Success
  // NotifyNo: 0 -- 3
int __stdcall RegisterNotify(UINT NotifyNo, HANDLE hWnd,UINT uMsg,\
                             UINT wParam, LONG lParam);
  //StopStr(): Return ADCard_Error or ADCard_Success
int __stdcall StopIntr(void);

  //QueryBuf(): Return Num of buff exist
WORD __stdcall QueryBuf(void);
  //ADResult(): Return ADCard_Error or ADCard_Success
int __stdcall ADResult(ADCard_Result * Buf);
  //ADResultRecent(): Return ADCard_Error or ADCard_Success
int __stdcall ADResultRecent(ADCard_Result * Buf);
//Chn:通道数
//DatMode:0:AD值,1:电压值V
//FilterMode:0不滤波,1:平均滤波
//Coe:平均滤波次数或IIR的系数
//pBuf:采集结果
int __stdcall ADResult_DV(WORD StartChn,WORD Chn,WORD DatMode,WORD FilterMode,float Coe,float * pBuf);

  //GetSnapshot(): Return ADCard_Error or ADCard_Success
int __stdcall GetSnapshot(ADCard_Result * Buf, int SampPerChn, DWORD * SampPtr);


//ConfigInfo(): return ADCard config info
void __stdcall ConfigInfo(char * ADCard_Name,\
                          int * MaxChn,\
                          int * LowFreq,\
                          int * HighFreq,\
                          int * MinSampNum,\
                          float * VZero,\
                          float * VMax,\
                          int * MaxBinChn);
//return actual sample frequency for each channel
float __stdcall ChannelFrq(int NumChn,long FrqSamp);

//card dependent IOCtl interface
int __stdcall IOCtl(int InSize,char * InBuff,int OutSize,char * OutBuff);

//return last ADError code
int __stdcall GetLastADError(void);
//return ADCard Property String Size
int __stdcall GetADPropStrSize(void);
//return ADCard Property String itself, 
//  and size for StrBuf is specified by GetADPropStrSize
int __stdcall GetADPropString(char * StrBuf);

void __stdcall  LoadDriver_CB(void);
void __stdcall  UnloadDriver_CB(void);

int __stdcall Setup_BeginChn(WORD Chn);////向硬件提供设置起始通道功能:解决多通道模式下,通道串扰问题,可以单通道采集,然后上位机切换通道

//IO tools function
void __stdcall outportb(WORD port, WORD value);
WORD __stdcall inportb(WORD port);
void __stdcall outport(WORD port, WORD value);
WORD __stdcall  inport(WORD port);
void __stdcall outportdw(WORD port, DWORD value);
DWORD __stdcall inportdw(WORD port);
//一次写出一组数据功能,通过16号功能实现
//Num:数据个数
//port:地址
//value:16位的数据
//返回:0失败,1成功
int __stdcall outport_Arr(WORD port,WORD Num, WORD *Dat);
//一次读入的数组,Num 数据字节个数,port端口, Dat[]数据
//返回值:0失败,1成功
//本函数的本质功能就是读取72对应的ARM数据
int __stdcall inportb_Arr(WORD port,WORD Num,unsigned char *Dat);
//一次读入的数组,Num 数据字节个数,port端口, Dat[]数据
//返回值:0失败,1成功
//本函数的本质功能就是读取72对应的ARM数据
int __stdcall inport_Arr(WORD port,WORD Num,WORD *Dat);

int __stdcall SetMultiFreq(int NumVChn, int * MultiFreq);
//查询采集当前的状态
//LEN:数据长度,一般为32
//Dat[]:开始输出状态数据
//Dat[0]:0->采集没有启动,1->采集已经启动
//Dat[1]:0->采集卡没有初始化,1->采集卡已经初始化
//Dat[2]:0->多缓冲区采集模式,1->当缓冲区采集模式
//Dat[3]:采集通数
//Dat[4]:起始通道
//Dat[5]:每块采样数
//Dat[6]:采样频率的低16位
//Dat[7]:采样频率的高16位
//Dat[8]:缓冲区块数
//Dat[9]:增益
//Dat[10]:模拟量通道数
//Dat[11]:用查询方式采集时,最多的平均次数,一般为50

int __stdcall WINAPI Rbh_ReadSts(WORD Len,WORD * Dat);//启动A/D转换

//-------用于查询方式读取AD结果
//MODE:输入,16,读取16位AD结果,此时LowV,HighV无效
//     32,读取32位的结果,此时LowV,HighV无效
//     1, 浮点电压值,LowV,HighV分别表示电压的最大值和最小值
//StartChn:输入,起始通道号,从0开始
//EndChn: 输入, 结束通道号,从0开始
//MeanTimes:输入,1-50,用于对AD结果是否平均
//LowV:输入,最小AD值对应的电压,输入电压,如对于-5~+5V输出的系统,应该就是-5V,对于0-10V,就是10
//HighV:输入,最大电压对应的电压,如+5V,10V
//Dat[]:输出结果
int __stdcall WINAPI Rbh_SeekAD(WORD Mode,WORD StartChn,WORD EndChn,WORD MeanTimes,float LowV,float HighV,float * Dat);



int __stdcall Rbh_Init(WORD ADNumChn, WORD ADBegChn, WORD ADAmpGain);
int __stdcall Rbh_DI(WORD IOChn,WORD * DIValue); //standard
//按位输入的开关量
int WINAPI Rbh_DIBit(WORD BitNum,WORD * BitValue);//位数(如2表示开关量1,2的输入),数据结果
//int __stdcall Rbh_DI(WORD * DIValue);//only for 7200
//特殊功能函数,综合性的函数,主要的接口功能
//根据FUN的编号，实现不同的功能
//42:读取板卡名称编号,如8308
//43:读取功能号,如-3
//44:读取功能参数1,如2通道等


//51:光栅，或编码器的计数器清零功能
//52:设定脉冲检测的时间分辨率，Para1=0-3,通道号，Para2=数据
//53:读取脉冲检测的时间分辨率，Para1=0-3,通道号，函数返回值就是时间分辨率
int __stdcall Rbh_SpecialFun(WORD Fun,WORD Para1,WORD Para2,WORD Para3,WORD * Para4,WORD * Para5);//专用功能函数
int __stdcall Rbh_Fun(WORD Fun,float Para1,float Para2,float Para3,float * Para4,float * Para5);//专用功能,双精度接口


int __stdcall Rbh_DI16(void);
int __stdcall Rbh_GetLastSampValue(WORD StartChn,WORD Num,WORD * SampValue);
 

int __stdcall WINAPI Rbh_DO_Spi(WORD offset,WORD Num,WORD * Value);
int __stdcall Rbh_MemRead(WORD Addr,WORD Num,WORD * DIValue);
int __stdcall Rbh_MemWrite(WORD Addr,WORD Num,WORD * DoValue);

 
int __stdcall Rbh_Readb(WORD Func,WORD Addr,WORD Num,WORD * DIValue);
int __stdcall Rbh_Writeb(WORD Func,WORD Addr,WORD Num,WORD * DoValue);


//for 8701
int WINAPI Rbh_DataPara(WORD ReadStart,WORD ReadLong,WORD SendInterval,WORD SendStart ,WORD SendEnd );//读取数据的参数
int WINAPI Rbh_Cycle(WORD CycleNum,WORD *Data);//DA输出功能
int WINAPI Rbh_Threshold(WORD CycleSeq,WORD Num,WORD *Data);


int __stdcall Rbh_DO(WORD DOChn,WORD SWDO);//开关量按字节输出功能,DOChn=0-255,SWDO=0-255
int __stdcall Rbh_DOBit(WORD BitChn,WORD BitValue);//开关量按位输出功能,BitChn=0-1023,BitValue=0 or 1
int __stdcall Rbh_DO_Read(WORD DOChn,WORD *DOValue);//读取开关量输出的字节,DOChn=0-255
//DA 波形输出
int __stdcall  WINAPI DAWaveFun(WORD Fun,WORD *Para);



int __stdcall Rbh_SetPGA(WORD ValuePGA);//设置增益
int __stdcall Rbh_SetPGAArr(WORD Chn,WORD * PGAValue);//设置各个独立通道的增益
int __stdcall Rbh_SetChn(WORD ValueChn);//设置通道号
int __stdcall Rbh_StartAD(void);//启动A/D转换
int __stdcall Rbh_ADR1(WORD *ValueADR);//读取上一次A/D结果
int __stdcall Rbh_ADResult(WORD ADChn, WORD * ADResult);//读取全部通道的采集结果
int __stdcall Rbh_DA(WORD DAChn,WORD DAValue);//DA输出功能
int __stdcall Rbh_Set_DA_Range(WORD DAValue,WORD DARange);//设置DA的量程

int __stdcall Rbh_2DSP(WORD  * Addr);//通用传输到DSP数据的功能

int __stdcall Rbh_SetupCan(WORD StationNum,WORD Speed,WORD Mode);//设置CAN总线的模式:站点号,速度,工作模式
int __stdcall Rbh_SendJ1939(WORD P,WORD PF,WORD PS,WORD SA,WORD LEN,WORD  * DATA);//按照J1939的格式,发送数据
int __stdcall Rbh_ReadCanStatus(WORD n,WORD  * Addr);//通用传输到DSP数据的功能
int __stdcall Rbh_ReadSnap(WORD ReadNum,WORD * LeftNum,WORD * Value);
int __stdcall Rbh_CheckStation(WORD LowStation,WORD HighStation);//站点信息查询,主要是站点类型,站点配置等信息
int __stdcall Rbh_SynStation(void); //站点同步处理
int __stdcall Rbh_SendBag(WORD LowStation,WORD HighStation,WORD DataLen,WORD *Data); //站点信息查询,主要是站点类型,站点配置等信息

int __stdcall Rbh_SetLedItem1Seq(WORD Station,WORD *Seq) ;
int __stdcall Rbh_SetLedItem0Seq(WORD Station,WORD *Seq) ;
int __stdcall Rbh_SetLedItem2(WORD Station,WORD Item1,WORD Item2) ;
int __stdcall Rbh_SetTime(WORD Station,WORD sYear,WORD sMonth,WORD sDay,WORD sWeek,WORD sHour,WORD sMinute,WORD sSecond) ;
int __stdcall Rbh_SetLeftSite(WORD Station,WORD LeftSite) ;
int __stdcall Rbh_ReadStatus(DWORD *Status) ;


int __stdcall AllStationSeek(WORD MStation);
int __stdcall SomeStationSeek(WORD MStation,WORD LowStation,WORD HighStation);
int __stdcall SynStation(WORD MStation);
int __stdcall SomeON_OFF(WORD MStation,WORD LowStation,WORD HighStation);
int __stdcall AllMute(WORD MStation);
int __stdcall SomeMute(WORD MStation,WORD LowStation,WORD HighStation);
int __stdcall SomeActive(WORD MStation,WORD LowStation,WORD HighStation);
int __stdcall Set_SpanZero(WORD MStation,WORD LowStation,WORD HighStation,WORD SpanValue,WORD ZeroValue);
int __stdcall Read_Cali(WORD MStation,WORD LowStation,WORD HighStation); 
int __stdcall Save_Cali(WORD MStation,WORD LowStation,WORD HighStation);
int __stdcall Default_Cali(WORD MStation,WORD LowStation,WORD HighStation,WORD StartChn,WORD EndChn);
int __stdcall Set_Cali(WORD MStation,WORD LowStation,WORD HighStation,WORD StartChn,WORD EndChn,WORD ZeroValue, WORD SpanValue);
int __stdcall Relay_Ctrl1(WORD MStation,WORD LowStation,WORD HighStation,WORD NumValue,WORD Ctrl);
int __stdcall SetLeft_L_R(WORD MStation,WORD Station,WORD LValue,WORD RValue);
int __stdcall SetArrow_L_R(WORD MStation,WORD Station,WORD LValue,WORD RValue);




int __stdcall SendBag_Station(WORD LowStation,WORD HighStation);
int __stdcall SendBag_Start(void);
int __stdcall SendBag_End(void);
int __stdcall SendBag_Frame1(WORD Location,WORD DataLen,WORD *Data);
//写入停车泊位数据
int __stdcall WINAPI Rbh_WriteMap(WORD Num, WORD * InSite);
 
//读出停车泊位数据
int __stdcall WINAPI Rbh_ReadMap(WORD Num, WORD * OutSite);


#ifdef __cplusplus
}
#endif

#endif
