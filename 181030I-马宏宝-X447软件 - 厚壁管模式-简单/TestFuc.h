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
    BOOL b_initalDlg;     //����ģʽ���öԻ���  ���� ����
	WaveShowNum showNum;
	int steps[8];         //��ʾ����
	char titles[8][20];
	short restrain[8];
	WaveShowStyle showstyle[8];
	char etc[84];        //Ԥ��
	short showcompress[8];
	short timelapes[8];
	short alertline[8];
	SaveStyle savestyle;
	short alertline3[8];
	char DOtitles[8][20];
	float speed;            //����ٶ�
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
 *	RBH8221�ɼ�������
 */
typedef struct
{
	int startch;       //��ʼͨ��  base: 0
    int block;         //�ɼ��鳤�� �Ƽ�100
	int samplespeed;   //�������� ����ͨ���ܺ� ��λ K
	int channelnum;    //����ͨ������
	BOOL coding;       //�Ƿ�ʹ�ñ�����
	char etc[100];     //Ԥ��
}USB8221par;



/*
 *	�����ļ�ͷ��ʽ
 */
typedef struct 
{
	float version;              //���ݰ汾
	long  datasum;              //��������
	float speed;                //��λ���ݳ���
	int   blocksum;             //��������
	short  goodsum;              //�õĵ�������
	short  goodsum2;				//������������
	short year;                 //ʱ��
	short month;
	short day;
#if( CAIJICARD == 1 )	
	short std[68];             //��׼
	short pars[68];            //����
#else
	short std[128+8];             //��׼
	short pars[128+8];            //����
#endif	
	short alertline[8];         //����
	WaveShowStyle showstyle[8]; //��ʾ���
	short showCHS[2][8];        //��ʾͨ����Χ
	int steps[8];               //����	
	WaveShowNum shownum;        //��ʾ������
	char titles[8][20];         //����
	short restrain[8];          //���Ʊ�
	char  Uoperator[20];        //����Ա
    	short  grade[500];            //̽���м�
	short wgrade[799];           //����м�
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
 *  ��������ͷ��ʽ
 */
#if 0
typedef struct
{
	int   id;       //���
	long  blocksum; //����������
	short hour;     //����ʱ��
	short min;
	BOOL  good;
	BOOL  good2;
	int HendPt ;
	int VendPt;
	int   sid;     //��ˮ��
	int XPt[8];
	UINT xlength;	
	int YPt[8];
	UINT ylength;
	WORD weldNum;
	WORD weldNum2;
	char  etc[4]; //Ԥ��
}BLOCKHEAD;
#endif
typedef struct
{
	int   id;       //���
	long  blocksum; //����������
	short hour;     //����ʱ��
	short min;
	BOOL  good;
	BOOL  good2;
	int HendPt ;
	int VendPt;
	char  etc[6]; //Ԥ��
	int   sid;     //��ˮ��
	int XPt[8];
	UINT xlength;
	char weldNum;
	int YPt[8];
	UINT ylength;
	char weldNum2;
}BLOCKHEAD;
#endif
