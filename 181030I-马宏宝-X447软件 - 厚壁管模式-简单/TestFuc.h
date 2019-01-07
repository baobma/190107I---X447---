#include "enmuHead.h"

#ifndef TESTFUC_H
#define TESTFUC_H

#define CAIJICARD  2

#define WM_NEW_MSG WM_USER+106

void FloorMapSet(CWnd* pWnd,CDC* pdc,const int ex,const int ey);

template <typename T>
void DeletePtr(T*& ptr)
{
	if(ptr != NULL)
	{
		delete ptr;
		ptr = NULL;
	}
}



template <typename T>
void DeletePtrs(T*& ptr,int n)
{
	if(ptr != NULL)
	{
		for(int i = 0; i < n; i++)
		{
			DeletePtr(ptr[i]);
		}
		delete[] ptr;
		ptr = NULL;
	}
}



template <typename T>
void DeleteArray(T*& ptr)
{
	if(ptr != NULL)
	{
		delete[] ptr;
		ptr = NULL;
	}
}



template <typename T>
void DeleteArrays(T**& ptr,int n)
{
	if(ptr != NULL)
	{
		for(int i = 0; i < n; i++)
		{
			DeleteArray(ptr[i]);
		}
		delete[] ptr;
		ptr = NULL;
	}
}

typedef struct
{ 
    BOOL b_initalDlg;     //工作模式设置对话框  网络 单机
	WaveShowNum showNum;
	int steps[8];         //显示步长
	char titles[8][20];
	short restrain[8];
	WaveShowStyle showstyle[8];
	char etc[84];        //预留
	short showcompress[8];
	short timelapes[8];
	short alertline[8];
	SaveStyle savestyle;
	short alertline3[8];
	char DOtitles[8][20];
	float speed;            //检测速度
	short alertline2[8];
	BOOL  halfs[8];

	short differadjust[8];
	short differ[8];
	int nserl_hacc;
	int nserl_vacc;
//	bool thickPipeMode;
	//short headStart[8];
	//short Enddelay[8];
}AUTOSET;

/*
 *	RBH8221采集卡参数
 */
typedef struct
{
	int startch;       //启始通道  base: 0
    int block;         //采集块长度 推荐100
	int samplespeed;   //采样速率 所有通道总和 单位 K
	int channelnum;    //采样通道数量
	BOOL coding;       //是否使用编码器
	char etc[100];     //预留
}USB8221par;



/*
 *	数据文件头格式
 */
typedef struct 
{
	float version;              //数据版本
	long  datasum;              //数据总量
	float speed;                //单位数据长度
	int   blocksum;             //单次总量
	short  goodsum;              //好的单次总数
	short  goodsum2;				//二级单次总数
	short year;                 //时间
	short month;
	short day;
#if( CAIJICARD == 1 )	
	short std[68];             //基准
	short pars[68];            //增益
#else
	short std[128+8];             //基准
	short pars[128+8];            //增益
#endif	
	short alertline[8];         //门限
	WaveShowStyle showstyle[8]; //显示风格
	short showCHS[2][8];        //显示通道范围
	int steps[8];               //步长	
	WaveShowNum shownum;        //显示块数量
	char titles[8][20];         //标题
	short restrain[8];          //抑制比
	char  Uoperator[20];        //操作员
    	short  grade[500];            //探伤判级
	short wgrade[799];           //测厚判级
	short badNum;
	long gooddatasum;
	short alertline2[8];
	short alertline3[8];
	short differadjust[8];
	short differ[8];
	char steel[8];
	char ply[8];
	char guige[8];	
}DATAHEAD;



/*
 *  单次数据头格式
 */
#if 0
typedef struct
{
	int   id;       //编号
	long  blocksum; //单次数据量
	short hour;     //单次时间
	short min;
	BOOL  good;
	BOOL  good2;
	int HendPt ;
	int VendPt;
	int   sid;     //流水号
	int XPt[8];
	UINT xlength;	
	int YPt[8];
	UINT ylength;
	WORD weldNum;
	WORD weldNum2;
	char  etc[4]; //预留
}BLOCKHEAD;
#endif
typedef struct
{
	int   id;       //编号
	long  blocksum; //单次数据量
	short hour;     //单次时间
	short min;
	BOOL  good;
	BOOL  good2;
	int HendPt ;
	int VendPt;
	char  etc[6]; //预留
	int   sid;     //流水号
	int XPt[8];
	UINT xlength;
	char weldNum;
	int YPt[8];
	UINT ylength;
	char weldNum2;
}BLOCKHEAD;
#endif
