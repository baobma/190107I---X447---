// DataBuf.cpp: implementation of the DataBuf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "DataBuf.h"
#include "TestFuc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DataBuf::DataBuf()
{
    data = NULL;
//	fault = NULL;
}

DataBuf::DataBuf(const int channel, const int datalen)
{
    data = NULL;
//	fault = NULL;
	this->channel = channel;
	data = new WORD*[channel];
//	fault = new short*[channel];
	for(int i = 0; i < channel; i++)
	{
		data[i] = new WORD[datalen];
//		fault[i] = new short[datalen+3000];
	}
	pars = new short[channel];
	stdline = new short[channel];
	datalens = new int[channel];
	memset(datalens,0,channel*sizeof(int));
	parsIndex = 0;
	loadIndexParsFromFile();
	loadStdFromFile();
}

DataBuf::~DataBuf()
{
    DeleteArray(data);
//	DeleteArray(fault);
	DeletePtr(pars);
	DeletePtr(stdline);
	DeletePtr(datalens);
}

BOOL DataBuf::loadParFromFile(int index,short a[])
{
    CFile parfile;
	CString filename;
	int id = 0;
	filename.Format("par\\pars.par");
	if(!parfile.Open(filename,CFile::modeRead | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:0001 参数文件读取失败");
		return FALSE;
	}
	int position = sizeof(short) + (index-1)*channel*sizeof(short);
	parfile.Seek(position,CFile::begin);
	parfile.Read(a,channel*sizeof(short));
	parfile.Close();
	return TRUE;
}
/*
 *	保存增益参数 
 *  index : 新的参数组号  a: 增益参数  checked 是否保存新的参数组号
 */
BOOL DataBuf::saveParToFile(int index, short a[],BOOL checked)
{
    	CFile parfile;
	CString filename;
	filename.Format("par\\pars.par");
	if(!parfile.Open(filename,CFile::modeWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:0002 参数文件读取失败");
		return FALSE;
	}
	
	int len = parfile.SeekToEnd();
	if(len != int(PARMAXNUM*channel*sizeof(short) + sizeof(short)) )
	{
        	AfxMessageBox("ErrorCode:0003 参数文件读取失败");
		return FALSE;
	}
	parfile.SeekToBegin();
	if(checked == TRUE)
		parfile.Write(&index,sizeof(short));
	
	int position = sizeof(short) + (index-1)*channel*sizeof(short);
	parfile.Seek(position,CFile::begin);
	parfile.Write(a,channel*sizeof(short));
	parfile.Close();
	return TRUE;
}

BOOL DataBuf::loadIndexParsFromFile()
{
    	CFile parfile;
	CString filename;
	int id = 0;
	filename.Format("par\\pars.par");
	if(!parfile.Open(filename,CFile::modeReadWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:0004 参数文件读取失败");
		return FALSE;
	}

	int len = parfile.SeekToEnd();
	if(len != int(PARMAXNUM*channel*sizeof(short) + sizeof(short)))
	{
        	AfxMessageBox("ErrorCode:0005 参数文件读取失败");
		parfile.Close();
		return FALSE;
	}
	parfile.SeekToBegin();

	parfile.Read(&parsIndex,sizeof(short));
	int position = sizeof(short) + (parsIndex-1)*channel*sizeof(short);
	parfile.Seek(position,CFile::begin);
	parfile.Read(pars,channel*sizeof(short));
	parfile.Close();
	return TRUE;
}

int DataBuf::getChannelNum()
{
    return channel;
}

short DataBuf::getpar(int index)
{
    	index = (index > channel) ? channel : index;
	index = (index < 1)       ? 1       : index;
	return pars[index];
}

int DataBuf::getParsIndex()
{
    return parsIndex;
}

void DataBuf::saveDefParToFile()
{

}

BOOL DataBuf::saveIndexParToFile()
{
	int index = this->parsIndex;

    	CFile parfile;
	CString filename;
	filename.Format("par\\pars.par");
	if(!parfile.Open(filename,CFile::modeWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:0006 参数文件读取失败");
		return FALSE;
	}
	
	int len = parfile.SeekToEnd();
	if(len != int(PARMAXNUM*channel*sizeof(short) + sizeof(short)) )
	{
        	AfxMessageBox("ErrorCode:0006 参数文件读取失败");
	//	return FALSE;
	}
	parfile.SeekToBegin();
	
	parfile.Write(&index,sizeof(short));
	int position = sizeof(short) + (index-1)*channel*sizeof(short);
	parfile.Seek(position,CFile::begin);
	parfile.Write(pars,channel*sizeof(short));
	parfile.Close();
	return TRUE;
}

WORD** DataBuf::getDataPtr()
{
    return data;
}

int DataBuf::getdataLens(const int& n)
{
    return datalens[n];
}

void DataBuf::increaeDataLen(const int &ch, const int &iLen)
{
	datalens[ch] += iLen;
	
}

void DataBuf::checkCh(int &n)
{
    n = n >= channel ? (channel-1) : n;
	n = n <= 0       ?  0          : n;
}

void DataBuf::resetDataLen()
{
    memset( datalens,0,channel*sizeof(int) );
}

void DataBuf::checkDatas(int ch, int &index)
{
	index = (index > datalens[ch]) ? datalens[ch] : index;
	index = (index < 0)            ? 0            : index;
}


/*
 *	基准标定，求各个通道数据的均值
 */
void DataBuf::democrateChs(int start, int end)
{
     checkCh(start);
	 checkCh(end);
	 for(int i = start; i <= end; i++)
	 {
		 if(datalens[i] == 0)
			 continue;
		 long sum = 0;
		 for(int j = 0; j < datalens[i]; j++)
		 {
			 sum += data[i][j];
		 }
		 short average = (sum/datalens[i])&(0XFFF);
		 stdline[i] = average;
	 }
	 saveStdToFile();
}

BOOL DataBuf::saveStdToFile()
{
    CFile stdfile;
	CString filename;
	filename.Format("par\\std.par");
	if(!stdfile.Open(filename,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:0008 参数文件读取失败");
		return FALSE;
	}
	
	stdfile.Write(stdline,channel*sizeof(short));
	stdfile.Close();
	return TRUE;
}

BOOL DataBuf::loadStdFromFile()
{
    CFile parfile;
	CString filename;
	filename.Format("par\\std.par");
	if(!parfile.Open(filename,CFile::modeRead | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:0009 参数文件读取失败");
		return FALSE;
	}
	parfile.Read(stdline,channel*sizeof(short));
	parfile.Close();
	return TRUE;
}

short* DataBuf::getParPtr()
{
    return pars;
}

short* DataBuf::getStdPtr()
{
    return stdline;
}

void DataBuf::setDataLens(int ch, int len)
{
    checkCh(ch);
    datalens[ch] = len < 0 ? 0 : len;
}

//short** DataBuf::GetFaultPtr()
//{
//	return fault;
//}