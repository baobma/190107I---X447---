// GobalData.h: interface for the GobalData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOBALDATA_H__4B4AEA3A_BDE3_4FB6_9D22_407060F6C5B2__INCLUDED_)
#define AFX_GOBALDATA_H__4B4AEA3A_BDE3_4FB6_9D22_407060F6C5B2__INCLUDED_

#include "TestFuc.h"	// Added by ClassView
#include "enmuHead.h"
#include "DataBuf.h"
#include "SampleCard.h"
#include "DataSaveFactory.h"
#include "DataSaveStyle.h"
#include "IOStatusDlg.h"
#include "ReportDlg.h"
#include "MainDlg.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define REN_ZHENG
//#define AddYcord

/*
 *	ȫ��������
 */
class GobalData  
{
private:
	int sid;
	CFile* filePtr;       //��ǰʹ���ļ�ָ��
	char* suffix;         //��ǰʹ���ļ�����׺
	char* filename;       //��ǰʹ���ļ���
	SaveStyle savestyle;  //��ǰ���ݱ�����
	Status status;        //��ǰ����״̬
	long datalen;          //������󳤶�
	DataBuf* databuf;     //����
	static GobalData* gobaldata;  //ȫ�����ݶ���
	WorkModel workmodel;  //����ģʽ
    	AUTOSET autoset;      //�Զ�����
	USB8221par usb8221par;//8221�ɼ�������
	GobalData();
	WaveShowNum EshowNum;
public:
	void setSid(int i);
	int getSid();
	BOOL goodflag;
    	BOOL goodflag2;
	BOOL wgoodflag;
    	BOOL wgoodflag2;
	float m_menxianzhi;
	int getBlockNumFromCh(int ch);
	void setSuffix(char* s);
	DataSaveStyle* gstyle; //��ǰ���ݱ�����
	HWND Dlghandle;        //���Ի�����
	ReportDlg* reportdlg;
	CIOStatusDlg* IoStatusDlg; //״̬��ضԻ������ָ��
	void setDataHeadForDataFile(DATAHEAD& datahead);
	BOOL getDataHeadForUsing(DATAHEAD datahead);
	WaveShowNum getShowNum();
	void setShowNum(WaveShowNum n);
	void CloseFile();
	void setStatus(Status s);
	const float VERSION;  //�汾
	BOOL seekDataToNum(int num, CFile* dataFile);
	DATAHEAD dataHead;   //��ǰʹ���ļ�ͷ
	BLOCKHEAD blockHead; //��ǰʹ�õ���ͷ
	char* getFileName();
	CFile* getFilePtr();
	char* getSuffix();
	BOOL loadDataFromFile(CString filename,CFile* file);  //��ȡ�ļ�����
	Status getStatus();
	void setWholeFileName(CString name);
	CString getWholeFileName();
	void setWholeFileName(char* name);
	void setSaveStyle(SaveStyle s);
	SaveStyle getSaveStyle();
	BOOL saveDataToFile(CString filename1);
	short  showCHS[2][8]; //ͨ����ʾ��Χ
	void setShowCHStoFile();
	void getShowCHSfromFile();
	BOOL getDataFromCard8221(WORD *ADBuf, WORD *ADBuf1);
	const int MAXCHANNEL;  //���ݻ������ͨ������
	void set8221par(USB8221par par);
	USB8221par& getUsb8221Par();
	int getDataLen();
	void setDataLen(const int len);
	DataBuf* getDataBuf();
	bool isNetWork();
	void setWorkModel(WorkModel w);
	static GobalData* getGobalData();
	void setAutoSetToFile();
	void setAutoSet(AUTOSET at);
	void getAutoSetFromFile();
	void GobalData::ReadlvboToFile(CString strFileName);
	AUTOSET& getAutoSet();int ldata[32][100];
	virtual ~GobalData();
};

#endif // !defined(AFX_GOBALDATA_H__4B4AEA3A_BDE3_4FB6_9D22_407060F6C5B2__INCLUDED_)





