// GobalData.cpp: implementation of the GobalData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "GobalData.h"
#include "TestSampleControl.h"
#include "TestFuc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
GobalData* GobalData::gobaldata;
//extern  int  datalencal;
//extern  caijimodel;
//DWORD time1=0;
//DWORD time2=0;
//extern	BOOL  isoffirst;
//BOOL  zaiciqidong=FALSE;
#if( CAIJICARD == 1 )	
GobalData::GobalData():MAXCHANNEL(68),VERSION(1.4f)
#else
GobalData::GobalData():MAXCHANNEL(136),VERSION(1.4f)	
#endif
{
	gstyle = NULL;
	Dlghandle = NULL;
	datalen = 8200*30;//8200*700;
    	workmodel = WorkModel_SINGLE;
// 平均每米采集点4000个，按15米长度钢管来统计最大值60000。
// 如果数据超长，修改采样频率来精简数据。
	databuf = new DataBuf(MAXCHANNEL,datalen);
	memset(showCHS,0,16*sizeof(short int));
	memset(&dataHead,0,sizeof(DATAHEAD));
	memset(&blockHead,0,sizeof(BLOCKHEAD));
	status = Status_STOP;
	savestyle = SimpleData;
	filename = new char[100];
	char* tmp = "";
//	char* tmp = "ord";
	strcpy(filename,tmp);
	suffix = new char[4];
	 tmp = "ord";
	strcpy(suffix,tmp);
	filePtr = new CFile();
	IoStatusDlg = NULL;
	reportdlg = NULL;
	goodflag = TRUE;
	goodflag2 = TRUE;
	wgoodflag = TRUE;
	wgoodflag2 = TRUE;
	ReadlvboToFile("par\\automaneofnew.par");
}

GobalData::~GobalData()
{
    DeletePtr(databuf);
	DeletePtr(gobaldata);
	DeleteArray(filename);
	DeleteArray(suffix);
	DeletePtr(filePtr);
}

AUTOSET& GobalData::getAutoSet()
{
     return autoset;
}

/*
 *	从文件中获得自动设置参数
 */
void GobalData::getAutoSetFromFile()
{
    CFile sFile;
	CString filename;
	filename.Format("par\\autoset.par");
	if(!sFile.Open(filename,CFile::modeRead | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:00001 文件读取失败");
		return;
	}
	sFile.Read(&autoset,sizeof(AUTOSET));
	sFile.Close();
}

/*
 *	设置自动设置参数
 */
void GobalData::setAutoSet(AUTOSET at)
{
	autoset = at;
}

/*
 *	将自动设置参数写入文件
 */
void GobalData::setAutoSetToFile()
{
    CFile sFile;
	CString filename;
	filename.Format("par\\autoset.par");
	if(!sFile.Open(filename,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:00002 文件读取失败");
		return;
	}
	sFile.Write(&autoset,sizeof(AUTOSET));
	sFile.Close();
}

/*
 *	返回全局数据对象指针
 */
GobalData* GobalData::getGobalData()
{
	if(gobaldata == NULL)
		gobaldata = new GobalData();
	return gobaldata;
}
/*
 *	设置工作模式
 */
void GobalData::setWorkModel(WorkModel w)
{
    workmodel = w;
}
/*
 *	是否为网络工作模式
 */
bool GobalData::isNetWork()
{
    if(workmodel == WorkModel_NETWORK)
		return true;
	else
		return false;
}
/*
 *	返回数据类指针
 */
DataBuf* GobalData::getDataBuf()
{
    return databuf;
}
/*
 *	设置数据内存长度
 */
void GobalData::setDataLen(const int len)
{
    if(len <= 0)
		return;
	else
	{
		datalen = len;
		DeletePtr(databuf);
		databuf = new DataBuf(MAXCHANNEL,datalen);     //重新分配数据内存
	}
}
/*
 *	返回数据内存长度
 */
int GobalData::getDataLen()
{
    return datalen;
}
/*
 *	返回8221采集卡参数
 */
USB8221par& GobalData::getUsb8221Par()
{
	CFile sFile;
	CString filename;
	filename.Format("par\\usb8221.par");
	if(!sFile.Open(filename,CFile::modeRead | CFile::typeBinary))
	{
	//	AfxMessageBox("ErrorCode:00003 文件读取失败");
		return usb8221par;
	}
	sFile.Read(&usb8221par,sizeof(USB8221par));
	sFile.Close();
    return usb8221par;
}
/*
 *	设置8221采集卡参数
 */
void GobalData::set8221par(USB8221par par)
{
	usb8221par =  par;
	
	CFile sFile;
	CString filename;
	filename.Format("par\\usb8221.par");
	if(!sFile.Open(filename,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:00004 文件读取失败");
		return;
	}
	sFile.Write(&usb8221par,sizeof(USB8221par));
	sFile.Close();
}
/*
 *	从8221采集卡中得到数据
 */
BOOL GobalData::getDataFromCard8221(WORD *ADBuf, WORD *ADBuf1)
{
	WORD** data = databuf->getDataPtr();
	short* std = databuf->getStdPtr();
	short* par = databuf->getParPtr();
	
	if(databuf->getdataLens(usb8221par.startch+4) >= datalen)
	{
		return FALSE;		
	}
 //   if (status == Status_DEMORATE)
	{
		
		for(int i = 0; i < usb8221par.block;i++)
		{
			for(int j = usb8221par.startch; j < 68; j++)
			{ 
				int len = databuf->getdataLens(j);
				data[j][len+i] = (ADBuf[(j-usb8221par.startch) + (i*usb8221par.channelnum) + 1]);
			}
			for( j = 68; j < 68+68; j++)
			{ 
				int len = databuf->getdataLens(j);
				data[j][len+i] = ADBuf1[(j-68) + (i*usb8221par.channelnum) + 1];
			}
		}
		
		for(int j = usb8221par.startch; j < usb8221par.startch+usb8221par.channelnum; j++)
		{
			databuf->increaeDataLen(j,usb8221par.block);
		}
		for( j = 68; j < 136; j++)
			databuf->increaeDataLen(j,usb8221par.block);
	}
#if 0 
	else
	{	
		
		int index=0;
		for(int i = 0; i < usb8221par.block;i++)
		{
			for(int j = usb8221par.startch+2; 
			j < usb8221par.startch+usb8221par.channelnum; j++)
			{
				ldata[j][index] = ADBuf[(j-usb8221par.startch) + (index*usb8221par.channelnum) + 1]/16;
			}
			++index;
			if (caijimodel==0)
			{
				if (i>0)
				{
					if ((((ADBuf[(0-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16
						-(ADBuf[(0-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1])/16>1300)
						&&ADBuf[(1-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1]/16<2500)
						||(((ADBuf[(0-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1])/16
						-(ADBuf[(0-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16>1300)
						&&ADBuf[(1-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1]/16>3800))
					{
						
						for(int j = usb8221par.startch; 
						j < usb8221par.startch+2; j++)
						{
							int len = databuf->getdataLens(j);
							if (len==0)
							{
								data[j][len] = 1;
								databuf->increaeDataLen(j,1);
							}
							else
							{
								data[j][len] = data[j][len-1]+1;
								databuf->increaeDataLen(j,1);
							}
						}
						
						
						for( j = usb8221par.startch+2; 
						j < usb8221par.startch+usb8221par.channelnum; j++)
						{
							int len = databuf->getdataLens(j);
							if (len<0)
							{
								databuf->increaeDataLen(j,1);
							}
							else
							{
								for (int k = 0; k<index; k++)
								{
									data[j][len+k] = ldata[j][k];
								}
								databuf->increaeDataLen(j,1);
								
							}
						}
						index = 0;
					}
					
					if ((((ADBuf[(1-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16
						-(ADBuf[(1-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1])/16>1300)
						&&ADBuf[(0-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1]/16<2500)
						||(((ADBuf[(1-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1])/16
						-(ADBuf[(1-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16>1300)
						&&ADBuf[(0-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1]/16>3800))
					{
						
						for(int j = usb8221par.startch; 
						j < usb8221par.startch+2; j++)
						{
							int len = databuf->getdataLens(j);
							if (0==len)
							{
								data[j][len] = -1;
								databuf->increaeDataLen(j,1);
							}
							else
							{
								data[j][len] = data[j][len-1]-1;
								databuf->increaeDataLen(j,1);
							}
						}
						
						
						
						for( j = usb8221par.startch+2; 
						j < usb8221par.startch+usb8221par.channelnum; j++)
						{
							int len = databuf->getdataLens(j);
							if (len<0)
							{
								databuf->increaeDataLen(j,1);
							}
							else
							{
								for (int k = 0; k<index; k++)
								{
									data[j][len+k] = ldata[j][k];
								}
								databuf->increaeDataLen(j,1);
								
							}
						}
						index = 0;
					}
				}
			}
			else if (caijimodel==1)
			{
				if (i>0)
				{
					
					if ((((ADBuf[(1-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16
						-(ADBuf[(1-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1])/16>1300)
						&&ADBuf[(0-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1]/16<2500)
						||(((ADBuf[(1-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1])/16
						-(ADBuf[(1-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16>1300)
						&&ADBuf[(0-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1]/16>3800))
						
					{
						
						for(int j = usb8221par.startch; 
						j < usb8221par.startch+2; j++)
						{
							int len = databuf->getdataLens(j);
							if (len==0)
							{
								data[j][len] = 1;
								databuf->increaeDataLen(j,1);
							}
							else
							{
								data[j][len] = data[j][len-1]+1;
								databuf->increaeDataLen(j,1);
							}
						}
						
						
						for( j = usb8221par.startch+2; 
						j < usb8221par.startch+usb8221par.channelnum; j++)
						{
							int len = databuf->getdataLens(j);
							if (len<0)
							{
								databuf->increaeDataLen(j,1);
							}
							else
							{
								for (int k = 0; k<index; k++)
								{
									data[j][len+k] = ldata[j][k];
								}
								databuf->increaeDataLen(j,1);
								
							}
						}
						index = 0;
					}
					
					if ((((ADBuf[(0-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16
						-(ADBuf[(0-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1])/16>1300)
						&&ADBuf[(1-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1]/16<2500)
						||(((ADBuf[(0-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1])/16
						-(ADBuf[(0-usb8221par.startch) + (i*usb8221par.channelnum) + 1])/16>1300)
						&&ADBuf[(1-usb8221par.startch) + ((i-1)*usb8221par.channelnum) + 1]/16>3800))
					{
						
						for(int j = usb8221par.startch; 
						j < usb8221par.startch+2; j++)
						{
							int len = databuf->getdataLens(j);
							if (0==len)
							{
								data[j][len] = -1;
								databuf->increaeDataLen(j,1);
							}
							else
							{
								data[j][len] = data[j][len-1]-1;
								databuf->increaeDataLen(j,1);
							}
						}
						for( j = usb8221par.startch+2; 
						j < usb8221par.startch+usb8221par.channelnum; j++)
						{
							int len = databuf->getdataLens(j);
							if (len<0)
							{
								databuf->increaeDataLen(j,1);
							}
							else
							{
								for (int k = 0; k<index; k++)
								{
									data[j][len+k] = ldata[j][k];
								}
								databuf->increaeDataLen(j,1);
								
							}
						}
						index = 0;
					}
				}
			}
			
			
			
		}
  
			
	}
#endif
	
    return TRUE;
}
/*
*	返回通道显示参数
*/
void GobalData::getShowCHSfromFile()
{
    CFile sFile;
	CString filename;
	filename.Format("par\\showch.par");
	if(!sFile.Open(filename,CFile::modeRead | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:00005 文件读取失败");
		return;
	}
	sFile.Read(showCHS,16*sizeof(short int));
	sFile.Close();
}
/*
 *	设置通道显示参数
 */
void GobalData::setShowCHStoFile()
{
    CFile sFile;
	CString filename;
	filename.Format("par\\showch.par");
	if(!sFile.Open(filename,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:00006 文件读取失败");
		return;
	}
	sFile.Write(showCHS,16*sizeof(short int));
	sFile.Close();
}

/*
 *	保存数据
 *  suffix:文件名后缀
 */
BOOL GobalData::saveDataToFile(CString filename1)
{
	filePtr->Abort();
	GobalData* g = GobalData::getGobalData();
	CFile dataFile;
	CString name;
	
	if(dataHead.blocksum >= 200 )
		{
			CString filename2 = filename1.Left(strlen(filename1)-4);
			CString filename3 = filename1.Right(4);
			filename1.Format("%s-1%s",filename2,filename3);
			sprintf(this->filename,"%s-1",filename2.GetBuffer(filename2.GetLength()));
		//	this->filename = filename1.GetBuffer(filename1.GetLength()-4);
		}
	name.Format("data\\%s",filename1);
	if(!dataFile.Open(name ,CFile::modeCreate | CFile::modeNoTruncate 
		| CFile::modeReadWrite | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:00007 文件读取失败");
		return FALSE;
	}
	int len = dataFile.SeekToEnd();
	dataFile.SeekToBegin();
	if(0 == len)                                             //空的新建文件
	{
        	setDataHeadForDataFile(dataHead);
		dataFile.Write(&dataHead,sizeof(DATAHEAD));
	}
	else
	{  
		dataFile.Read(&dataHead,sizeof(DATAHEAD));
		if(getDataHeadForUsing(dataHead) == FALSE)
		{
			AfxMessageBox("数据版本不匹配");
			return FALSE;
		}
		dataFile.SeekToEnd();
	}

	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSaveStyle());
	if(style == NULL)
		return FALSE;
	int blen = 0;                                            //单次数据长度
	if(style->savePerBlockData(&dataFile,&blockHead,blen,TestSampleControl::cardPtr,dataHead.blocksum + 1) == FALSE)     //保存单块数据
	{
		AfxMessageBox("ErrorCode: 文件保存失败");
		return FALSE;
	}

	/*
	 *	读文件头并做相应修改
	 */
	dataFile.SeekToBegin();
	dataFile.Read(&dataHead,sizeof(DATAHEAD));
	dataHead.datasum += blen;
	dataHead.blocksum += 1;
	if( blockHead.good == FALSE || blockHead.good2 == FALSE )
		dataHead.badNum++;
/*	if((g->goodflag == TRUE)&&(g->goodflag2 == FALSE))
	{
		dataHead.grade[dataHead.blocksum-1] = 1;   //二级
	}
	if(g->goodflag2 == TRUE)
	{
		dataHead.grade[dataHead.blocksum-1] = 2;   //一级
	}
	if ((g->goodflag == FALSE)&&(g->goodflag2 == FALSE))
	{
		dataHead.grade[dataHead.blocksum-1] = 0;   //报废
	}*/
//	if((g->wgoodflag == TRUE)&&(g->wgoodflag2 == FALSE))
//	{
///*		dataHead.gooddatasum += blen;*/
//		dataHead.wgrade[dataHead.blocksum-1] = 1;   //二级
////		dataHead.goodsum += 1;
//	}
//	if(g->wgoodflag2 == TRUE)
//	{
///*		dataHead.gooddatasum += blen;*/
//		dataHead.wgrade[dataHead.blocksum-1] = 2;   //一级
////		dataHead.goodsum2 += 1;
//	}
//	if ((g->wgoodflag == FALSE)&&(g->wgoodflag2 == FALSE))
//	{
//		dataHead.wgrade[dataHead.blocksum-1] = 0;   //报废
//	}
	dataFile.SeekToBegin();
	dataFile.Write(&dataHead,sizeof(DATAHEAD));

	dataFile.Close();
    DeletePtr(style);
    return TRUE;
}
/*
 *	返回数据保存风格
 */
SaveStyle GobalData::getSaveStyle()
{
    return autoset.savestyle;
}
/*
 *	设置数据保存风格
 */
void GobalData::setSaveStyle(SaveStyle s)
{
    autoset.savestyle = s;
    setAutoSetToFile();
}

/*
 *	设置文件名
 *  name是全名，格式为A.B其中A为任意字符串,B为3个字符组合的字符串
 */
void GobalData::setWholeFileName(char* name)
{
	 if(strlen(name) < 5 || strlen(name) > 100)   //文件名太短或太长
		 return;
     for(int i = 0; i < 3; i++)
	 {
	  	 suffix[i] = name[strlen(name)-3+i];
	 }
	 suffix[3] = '\0';
	 for(int j = 0; j < int(strlen(name)-4); j++)
	 {
		 filename[j] = name[j];
	 }
	 filename[strlen(name)-4] = '\0';
}
/*
 *	返回文件全名
 */
CString GobalData::getWholeFileName()
{
	CString str;
	str.Format("%s.%s",filename,suffix);
	return str;
}

void GobalData::setWholeFileName(CString fname)
{
	char* n = new char[fname.GetLength()+1];
	char* p = fname.GetBuffer(fname.GetLength());
	
	memcpy(n,p,fname.GetLength()*sizeof(char));
	n[fname.GetLength()] = '\0';
	setWholeFileName(n);
	DeletePtr(n);
}

Status GobalData::getStatus()
{
    return status;
}

BOOL GobalData::loadDataFromFile(CString filename, CFile* dataFile)
{
	GobalData* g = GobalData::getGobalData();
	if(dataFile != NULL)
	{
		dataFile->Abort();
	}
	CString name;
	name.Format("data\\%s",filename);
	if(!dataFile->Open(name ,CFile::modeRead | CFile::typeBinary))
	{
		AfxMessageBox("ErrorCode:00008 文件读取失败");
		return FALSE;
	}
	int len = dataFile->SeekToEnd();
	if(len == 0 || len == sizeof(DATAHEAD))
	{
        AfxMessageBox("ErrorCode:0010 无效文件或空文件");
		return FALSE;
	}
	dataFile->SeekToBegin();
	dataFile->Read(&dataHead,sizeof(DATAHEAD));
	if(getDataHeadForUsing(dataHead) == FALSE)
	{
		AfxMessageBox("数据版本不匹配");
		return FALSE;
	}
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());
	if(style == NULL)
		return FALSE;
	int blen = 0;                                        //单次数据长度
	if(style->loadPerBlockData(dataFile,&blockHead,blen) == FALSE)     //保存单块数据
	{
		AfxMessageBox("ErrorCode: 文件读取失败");
		return FALSE;
	}

	DeletePtr(style);

	if(g->reportdlg != NULL)
	    g->reportdlg->reFreshReport();
    return TRUE;
}

char* GobalData::getSuffix()
{
    return suffix;
}

CFile* GobalData::getFilePtr()
{
    return filePtr;
}

char* GobalData::getFileName()
{
    return filename;
}

BOOL GobalData::seekDataToNum(int num, CFile* dataFile)
{
	GobalData* g = GobalData::getGobalData();
    if(num <= 0 || num > dataHead.blocksum)
		return FALSE;
	if(dataFile == NULL)
		return FALSE;
	int currentnum = blockHead.id;  //当前次数
	int dnum = num - currentnum;    //需要寻找到的次数
	if(dnum  == 0)
		return FALSE;
	if(dnum < 0)        //向前搜索
	{
		for(int i = 0; i < -dnum + 1; i++)
		{
			dataFile->Seek(-long(sizeof(int)),CFile::current);
			int sum = 0;
			dataFile->Read(&sum,sizeof(int));
			dataFile->Seek(-long(sum + 2*sizeof(int)) ,CFile::current);
		}
	} 
	else              //向后搜索
	{
        for(int i = 0; i < dnum - 1; i++)
		{
			int sum = 0;
			dataFile->Read(&sum,sizeof(int));
			dataFile->Seek(long(sum + sizeof(int)),CFile::current);
		}
	}
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());
	if(style == NULL)
		return FALSE;
	int blen = 0;                                        //单次数据长度
	if(style->loadPerBlockData(dataFile,&blockHead,blen) == FALSE)     //保存单块数据
	{
		return FALSE;
	}
	DeletePtr(style);

	if(g->reportdlg != NULL)
	    g->reportdlg->reFreshReport();
	return TRUE;
	
}

void GobalData::setStatus(Status s)
{
    status = s;
}

void GobalData::CloseFile()
{
    filePtr->Abort();
	databuf->resetDataLen();
}

void GobalData::setShowNum(WaveShowNum n)
{
    EshowNum = n;
}

WaveShowNum GobalData::getShowNum()
{
    return EshowNum;
}

BOOL GobalData::getDataHeadForUsing(DATAHEAD datahead)
{
    if(dataHead.version == VERSION)
	{
        EshowNum = dataHead.shownum;
		memcpy(autoset.titles,datahead.titles,sizeof(autoset.titles));
		memcpy(autoset.steps,datahead.steps,sizeof(autoset.steps));
		memcpy(autoset.alertline,datahead.alertline,sizeof(autoset.alertline));
		memcpy(autoset.alertline2,datahead.alertline2,sizeof(autoset.alertline2));
		memcpy(autoset.alertline3,datahead.alertline3,sizeof(autoset.alertline3));
		memcpy(autoset.showstyle,datahead.showstyle,sizeof(autoset.showstyle));
		memcpy(autoset.differ,datahead.differ,sizeof(autoset.differ));
		memcpy(autoset.differadjust,datahead.differadjust,sizeof(autoset.differadjust));
		memcpy(showCHS,dataHead.showCHS,sizeof(showCHS));

		memcpy(autoset.restrain,datahead.restrain,sizeof(autoset.restrain));
		memcpy(databuf->getParPtr(),datahead.pars,MAXCHANNEL*sizeof(datahead.pars[0]));
		memcpy(databuf->getStdPtr(),datahead.std ,MAXCHANNEL*sizeof(datahead.std[0] ));
		memcpy(showCHS,dataHead.showCHS,sizeof(showCHS));
	    return TRUE;
	}
	else
	{
        return FALSE;
	}
	
}

void GobalData::setDataHeadForDataFile(DATAHEAD &datahead)  //将数据头文件内容保存到即将写入数据文件的文件头中
{
	CTime t = CTime::GetCurrentTime();
    	dataHead.version  = VERSION;
	dataHead.blocksum = 0;
	dataHead.goodsum  = 0;
	dataHead.goodsum2  = 0;
	dataHead.datasum  = 0;
	dataHead.badNum = 0;
	dataHead.gooddatasum = 0;
	dataHead.day      = t.GetDay();
	dataHead.month    = t.GetMonth();
	dataHead.year     = t.GetYear();
	dataHead.shownum  = EshowNum;
	dataHead.speed    = autoset.speed;
	memcpy(datahead.titles,autoset.titles,sizeof(autoset.titles));
	memcpy(datahead.steps,autoset.steps,sizeof(autoset.steps));
	memcpy(datahead.alertline,autoset.alertline,sizeof(autoset.alertline));
	memcpy(datahead.alertline2,autoset.alertline2,sizeof(autoset.alertline2));
	memcpy(datahead.alertline3,autoset.alertline3,sizeof(autoset.alertline3));
	memcpy(datahead.restrain ,autoset.restrain ,sizeof(autoset.restrain));
	memcpy(datahead.differ,autoset.differ,sizeof(autoset.differ));
	memcpy(datahead.differadjust,autoset.differadjust,sizeof(autoset.differadjust));
	memcpy(dataHead.showCHS,showCHS,sizeof(showCHS));
	memcpy(datahead.showstyle,autoset.showstyle,sizeof(autoset.showstyle));
	memcpy(dataHead.pars,databuf->getParPtr(),MAXCHANNEL*sizeof(dataHead.pars[0]));
	memcpy(dataHead.std, databuf->getStdPtr(),MAXCHANNEL*sizeof(dataHead.std[0] ));
}

void GobalData::setSuffix(char* s)
{
	DeleteArray(suffix);
	suffix = new char[4];
    strcpy(suffix,s);
	suffix[3] = '\0';
}

int GobalData::getBlockNumFromCh(int ch)
{
    for(int i = 0; i < 8; i++)
	{
		if(showCHS[0][i] <= ch && showCHS[1][i] >= ch)
			return i;
	}
	return -1;
}

int GobalData::getSid()
{
    return sid;
}

void GobalData::setSid(int i)
{
    sid = i;
}


void GobalData::ReadlvboToFile(CString strFileName)
{
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeRead)) 
	{
		AfxMessageBox("Read lvbo file error!");
		return;
	}
	
	CString strData;
	if (!file.ReadString(strData)) 
	{
		return;
	}
	sscanf(strData.GetBuffer(0), "%f", &m_menxianzhi);
	
	file.Close();
	
}
