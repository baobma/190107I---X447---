/* head file for adcard.h
  service dll for AD Card.
  Copyright(C) RBH, Sept.2, 1998
  */
#if !defined(AFX_AD_CARD1_H_5D8D7FD00DD9__INCLUDED_)
#define AFX_AD_CARD1_H_5D8D7FD00DD9__INCLUDED_

//for 8~16 bit AD
typedef unsigned short ADValueType;

// for high precision, >16 bit AD 
//typedef unsigned long ADValueType;

//AD Result Struct
/*
typedef struct structADResult {
  ADValueType SeqNo;
  ADValueType ADValue[1];
} ADCard_Result;
*/
//API return value
//#define ADCard_Success  1
//#define ADCard_Error  0
//#define NumNotify 4

//exported API

#ifdef __cplusplus
extern "C" {
#endif

  //Initial(): Return ADCard_Error or ADCard_Success
int __stdcall Initial_1(WORD IOBase, WORD IRQNum, DWORD PhysAddr,WORD DMAChn);

  //StartIntr(): Retur 0 or BuffSize
DWORD __stdcall StartIntr_1(WORD NumBuf, DWORD NumSamp,\
                          WORD BegChn, WORD NumChn, \
                          DWORD FrqSamp, DWORD FrqFilter,\
                          WORD AmpGain);
  //StartSnapshot(): Retur ADCard_Error or ADCard_Success
DWORD __stdcall StartSnapshot_1(WORD NumBuf, DWORD NumSamp,\
                          WORD BegChn, WORD NumChn,\
                          DWORD FrqSamp, DWORD FrqFilter,\
                          WORD AmpGain,DWORD NotifyLength);
  //RegisterNotify(): Return ADCard_Error or ADCard_Success
  // NotifyNo: 0 -- 3
int __stdcall RegisterNotify_1(UINT NotifyNo, HANDLE hWnd,UINT uMsg,\
                             UINT wParam, LONG lParam);
  //StopStr(): Return ADCard_Error or ADCard_Success
int __stdcall StopIntr_1(void);

  //QueryBuf(): Return Num of buff exist
WORD __stdcall QueryBuf_1(void);
  //ADResult(): Return ADCard_Error or ADCard_Success
int __stdcall ADResult_1(ADCard_Result * Buf);
  //ADResultRecent(): Return ADCard_Error or ADCard_Success
int __stdcall ADResultRecent_1(ADCard_Result * Buf);
  //GetSnapshot(): Return ADCard_Error or ADCard_Success
int __stdcall GetSnapshot_1(ADCard_Result * Buf, int SampPerChn, DWORD * SampPtr);


//ConfigInfo(): return ADCard config info
void __stdcall ConfigInfo_1(char * ADCard_Name,\
                          int * MaxChn,\
                          int * LowFreq,\
                          int * HighFreq,\
                          int * MinSampNum,\
                          float * VZero,\
                          float * VMax,\
                          int * MaxBinChn);
//return actual sample frequency for each channel
float __stdcall ChannelFrq_1(int NumChn,long FrqSamp);

//card dependent IOCtl interface
int __stdcall IOCtl_1(int InSize,char * InBuff,int OutSize,char * OutBuff);

//return last ADError code
int __stdcall GetLastADError_1(void);
//return ADCard Property String Size
int __stdcall GetADPropStrSize_1(void);
//return ADCard Property String itself, 
//  and size for StrBuf is specified by GetADPropStrSize
int __stdcall GetADPropString_1(char * StrBuf);


//IO tools function
void __stdcall outportb_1(WORD port, WORD value);
WORD __stdcall inportb_1(WORD port);
void __stdcall outport_1(WORD port, WORD value);
WORD __stdcall  inport_1(WORD port);
void __stdcall outportdw_1(WORD port, DWORD value);
DWORD __stdcall inportdw_1(WORD port);
int __stdcall SetMultiFreq_1(int NumVChn, int * MultiFreq);



int __stdcall Rbh_Init_1(WORD ADNumChn, WORD ADBegChn, WORD ADAmpGain);
int __stdcall Rbh_DI_1(WORD IOChn,WORD * DIValue); //standard
//按位输入的开关量
int WINAPI Rbh_DIBit_1(WORD BitNum,WORD * BitValue);//位数(如2表示开关量1,2的输入),数据结果
//int __stdcall Rbh_DI(WORD * DIValue);//only for 7200
//特殊功能函数,综合性的函数,主要的接口功能
//根据FUN的编号，实现不同的功能
//42:读取板卡名称编号,如8308
//43:读取功能号,如-3
//44:读取功能参数1,如2通道等


//51:光栅，或编码器的计数器清零功能
//52:设定脉冲检测的时间分辨率，Para1=0-3,通道号，Para2=数据
//53:读取脉冲检测的时间分辨率，Para1=0-3,通道号，函数返回值就是时间分辨率
int __stdcall Rbh_SpecialFun_1(WORD Fun,WORD Para1,WORD Para2,WORD Para3,WORD * Para4,WORD * Para5);//专用功能函数


int __stdcall Rbh_DI16_1(void);
int __stdcall Rbh_GetLastSampValue_1(WORD StartChn,WORD Num,WORD * SampValue);
 

int __stdcall WINAPI Rbh_DO_Spi_1(WORD offset,WORD Num,WORD * Value);
int __stdcall Rbh_MemRead_1(WORD Addr,WORD Num,WORD * DIValue);
int __stdcall Rbh_MemWrite_1(WORD Addr,WORD Num,WORD * DoValue);

int __stdcall Rbh_USB_Inportb_1(WORD Addr,WORD Num,WORD * DIValue);
int __stdcall Rbh_USB_Outportb_1(WORD Addr,WORD Num,WORD * DoValue);
int __stdcall Rbh_USB_Inport_1(WORD Addr,WORD Num,WORD * DIValue);
int __stdcall Rbh_USB_Outport_1(WORD Addr,WORD Num,WORD * DoValue);

int __stdcall Rbh_Readb_1(WORD Func,WORD Addr,WORD Num,WORD * DIValue);
int __stdcall Rbh_Writeb_1(WORD Func,WORD Addr,WORD Num,WORD * DoValue);


//for 8701
int WINAPI Rbh_DataPara_1(WORD ReadStart,WORD ReadLong,WORD SendInterval,WORD SendStart ,WORD SendEnd );//读取数据的参数
int WINAPI Rbh_Cycle_1(WORD CycleNum,WORD *Data);//DA输出功能
int WINAPI Rbh_Threshold_1(WORD CycleSeq,WORD Num,WORD *Data);


int __stdcall Rbh_DO_1(WORD DOChn,WORD SWDO);//开关量按字节输出功能,DOChn=0-255,SWDO=0-255
int __stdcall Rbh_DOBit_1(WORD BitChn,WORD BitValue);//开关量按位输出功能,BitChn=0-1023,BitValue=0 or 1
int __stdcall Rbh_DO_Read_1(WORD DOChn,WORD *DOValue);//读取开关量输出的字节,DOChn=0-255

int __stdcall Rbh_SetPGA_1(WORD ValuePGA);//设置增益
int __stdcall Rbh_SetPGAArr_1(WORD Chn,WORD * PGAValue);//设置各个独立通道的增益
int __stdcall Rbh_SetChn_1(WORD ValueChn);//设置通道号
int __stdcall Rbh_StartAD_1(void);//启动A/D转换
int __stdcall Rbh_ADR1_1(WORD *ValueADR);//读取上一次A/D结果
int __stdcall Rbh_ADResult_1(WORD ADChn, WORD * ADResult);//读取全部通道的采集结果
int __stdcall Rbh_DA_1(WORD DAChn,WORD DAValue);//DA输出功能
int __stdcall Rbh_CounterOut_1(WORD TC, WORD CTValueL,WORD CTValueH, WORD CTChn);
int __stdcall Rbh_2DSP_1(WORD  * Addr);//通用传输到DSP数据的功能


#ifdef __cplusplus
}
#endif

#endif
