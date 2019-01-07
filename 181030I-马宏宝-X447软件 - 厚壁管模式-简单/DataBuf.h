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
 *	���ݻ�����
 */
class DataBuf  
{
private:
	short int parsIndex;   //ѡ�����������
	int channel;           //ͨ����
	WORD** data;          //����
	DataBuf();
	short* pars;           //�������
	short* stdline;        //��׼����
	int* datalens;         //���ݳ���
//	short** fault;
public:
//	short** GetFaultPtr();
	void setDataLens(int i, int len);
	short* getStdPtr();
	short* getParPtr();
	BOOL loadStdFromFile();                 //��ȡ��׼
	BOOL saveStdToFile();                   //����׼���浽�ļ���
	void democrateChs(int start, int end);  //�궨��׼����ͨ��
	void checkDatas(int ch, int &index);
	void checkCh(int& n); //���Բ�����ͨ����
	void resetDataLen();
	void increaeDataLen(const int &ch, const int &iLen);
	int getdataLens(const int& n);
	WORD** getDataPtr();
	BOOL saveIndexParToFile(); //���浱ǰʹ�ò������ļ���
	int getParsIndex();
	short getpar(int index);
	int getChannelNum();
	BOOL loadIndexParsFromFile();
	void  saveDefParToFile();
	BOOL saveParToFile(int index,short a[],BOOL);  //����index����������ļ���
	BOOL loadParFromFile(int index,short a[]);     //��ȡindex�������
	DataBuf(const int channel, const int datalen);
	virtual ~DataBuf();

};

#endif // !defined(AFX_DATABUF_H__29D1F30F_840E_4FB6_8DF6_5D8D7FD00DD9__INCLUDED_)
