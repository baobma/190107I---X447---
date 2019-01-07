// DataBuf.h: interface for the DataBuf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABUF_H__29D1F30F_840E_4FB6_8DF6_5D8D7FD00DD9__INCLUDED_)
#define AFX_DATABUF_H__29D1F30F_840E_4FB6_8DF6_5D8D7FD00DD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
const int PARMAXNUM = 30;

/*
 *	数据缓存类
 */
class DataBuf  
{
private:
	short int parsIndex;   //选定参数的组号
	int channel;           //通道数
	WORD** data;          //数据
	DataBuf();
	short* pars;           //增益参数
	short* stdline;        //基准参数
	int* datalens;         //数据长度
//	short** fault;
public:
//	short** GetFaultPtr();
	void setDataLens(int i, int len);
	short* getStdPtr();
	short* getParPtr();
	BOOL loadStdFromFile();                 //读取基准
	BOOL saveStdToFile();                   //将基准保存到文件中
	void democrateChs(int start, int end);  //标定基准所有通道
	void checkDatas(int ch, int &index);
	void checkCh(int& n); //测试并修整通道号
	void resetDataLen();
	void increaeDataLen(const int &ch, const int &iLen);
	int getdataLens(const int& n);
	WORD** getDataPtr();
	BOOL saveIndexParToFile(); //保存当前使用参数到文件中
	int getParsIndex();
	short getpar(int index);
	int getChannelNum();
	BOOL loadIndexParsFromFile();
	void  saveDefParToFile();
	BOOL saveParToFile(int index,short a[],BOOL);  //保存index号组参数到文件中
	BOOL loadParFromFile(int index,short a[]);     //读取index号组参数
	DataBuf(const int channel, const int datalen);
	virtual ~DataBuf();

};

#endif // !defined(AFX_DATABUF_H__29D1F30F_840E_4FB6_8DF6_5D8D7FD00DD9__INCLUDED_)
