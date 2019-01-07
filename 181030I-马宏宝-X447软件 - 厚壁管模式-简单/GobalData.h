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
 *	全局数据类
 */
class GobalData  
{
private:
	int sid;
	CFile* filePtr;       //当前使用文件指针
	char* suffix;         //当前使用文件名后缀
	char* filename;       //当前使用文件名
	SaveStyle savestyle;  //当前数据保存风格
	Status status;        //当前工作状态
	long datalen;          //数据最大长度
	DataBuf* databuf;     //数据
	static GobalData* gobaldata;  //全局数据对象
	WorkModel workmodel;  //工作模式
    	AUTOSET autoset;      //自动设置
	USB8221par usb8221par;//8221采集卡参数
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
	DataSaveStyle* gstyle; //当前数据保存风格
	HWND Dlghandle;        //主对话框句柄
	ReportDlg* reportdlg;
	CIOStatusDlg* IoStatusDlg; //状态监控对话框控制指针
	void setDataHeadForDataFile(DATAHEAD& datahead);
	BOOL getDataHeadForUsing(DATAHEAD datahead);
	WaveShowNum getShowNum();
	void setShowNum(WaveShowNum n);
	void CloseFile();
	void setStatus(Status s);
	const float VERSION;  //版本
	BOOL seekDataToNum(int num, CFile* dataFile);
	DATAHEAD dataHead;   //当前使用文件头
	BLOCKHEAD blockHead; //当前使用单块头
	char* getFileName();
	CFile* getFilePtr();
	char* getSuffix();
	BOOL loadDataFromFile(CString filename,CFile* file);  //读取文件数据
	Status getStatus();
	void setWholeFileName(CString name);
	CString getWholeFileName();
	void setWholeFileName(char* name);
	void setSaveStyle(SaveStyle s);
	SaveStyle getSaveStyle();
	BOOL saveDataToFile(CString filename1);
	short  showCHS[2][8]; //通道显示范围
	void setShowCHStoFile();
	void getShowCHSfromFile();
	BOOL getDataFromCard8221(WORD *ADBuf, WORD *ADBuf1);
	const int MAXCHANNEL;  //数据缓存最大通道数量
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





