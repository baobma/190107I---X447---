// RbhUsb20.cpp: implementation of the RbhUsb20 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RbhUsb20.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "TestSampleControl.h"
#include "GobalData.h"

#define WM_MyNotify  WM_USER+100
#define WM_SampleMsg WM_USER+101
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
UINT SampleThread(LPVOID lpParam);
UINT AutoSampleThread(LPVOID lpParam);
//UINT   RecvProc(LPVOID lpParameter);
UINT   RecvProc2(LPVOID lpParameter);

struct RECVPARAM  
{  
 SOCKET sock;  
 HWND hwnd;  
};  
static   RECVPARAM *pRecvParam= NULL;

RbhUsb20::RbhUsb20(HWND hwnd,const int sampleSpeed,const int channelNum,const int iBlockLen):CSampleCard(sampleSpeed,channelNum)
{
	setWnd(hwnd);
	flagOfCard = FLAGCARD_STOP;
    	ADBuf = NULL;
	ADBuf1 = NULL;
	DIsingal = FALSE;
	this->iBlockLen = iBlockLen;
	this->channelNum = channelNum;
	m_socket = 0;
}

RbhUsb20::~RbhUsb20()
{
       DeleteArray(ADBuf);
	DeleteArray(ADBuf1);
//	closesocket(pRecvParam->sock);    
//	WSACleanup();  
//	delete pRecvParam;
}
static SOCKET ConnectSocket;
BOOL RbhUsb20::Inital()
{
    	DeleteArray(ADBuf);
	DeleteArray(ADBuf1);
	int len = channelNum * iBlockLen;
	ADBuf = (WORD*) malloc( (len+1)*sizeof(WORD) ); //给采集卡分配内存
	ADBuf1 = (WORD*) malloc( (len+1)*sizeof(WORD) ); //给采集卡分配内存

	flagOfCard = FLAGCARD_STOP;
	if(ADBuf == NULL|| ADBuf1 == NULL) 
	{
		return FALSE;
	}	
	if(wndHandle == NULL)
	{
        	return FALSE;
	}
	StopIntr();
    	if(Initial(IOBase,IRQNum,PhysAddr,DMAChn) == ADCard_Error) 
	{
		return FALSE;
  	}
	StopIntr_1();	
	if(Initial_1(IOBase,IRQNum,PhysAddr,DMAChn) == ADCard_Error) 
	{
		return FALSE;
   	}
#if 0	
	RegisterNotify(0,wndHandle,WM_MyNotify,48,0);
#endif
	RegisterNotify_1(0,wndHandle,WM_MyNotify,49,0);
//	AfxMessageBox("init ok");
	return TRUE;
}

//创建sockaddr_in结构体变量
//struct sockaddr_in serv_addr;
//memset(&serv_addr, 0, sizeof(serv_addr)); //每个字节都用0填充
//serv_addr.sin_family = AF_INET; //使用IPv4地址
//serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //具体的IP地址
//serv_addr.sin_port = htons(1234); //端口


void RbhUsb20::workwithPlc()
{
#if 1

	WSACleanup();  
	if( pRecvParam != NULL )
	delete pRecvParam;

		AfxSocketInit();
		m_socket=socket(AF_INET,SOCK_STREAM,0);//基于tcp IPPROTO_TCP
		if(INVALID_SOCKET==m_socket)  
		{  
			AfxMessageBox("请检查计算机网卡");  
			closesocket(m_socket);  
			return ;  
		}  
		SOCKADDR_IN addrSock;  

		memset(&addrSock, 0, sizeof(SOCKADDR_IN));
		addrSock.sin_family=AF_INET;  
#if 0 	//x460
		addrSock.sin_port=htons(3000);  
		addrSock.sin_addr.s_addr = inet_addr("192.168.2.106");
#else 	
	//	 x447
		addrSock.sin_port=htons(2000);
		addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);  // inet_addr("192.168.2.106");
#endif	
	 //	char flag=1;
	//	setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(char));
		BOOL rettime = FALSE;// 强制立即关闭socket
		setsockopt(m_socket,SOL_SOCKET,SO_DONTLINGER,(const char*)&rettime,sizeof(BOOL));	
		//设置收发时限
		int nettimeout = 10;
		setsockopt(m_socket,SOL_SOCKET,SO_SNDTIMEO,(const char*)&rettime,sizeof(int));	
		setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,(const char*)&rettime,sizeof(int));	
		// 不经历系统缓存直接拷贝SOCKET缓存区。
		int nzero = 0;
		setsockopt(m_socket,SOL_SOCKET,SO_SNDBUF,(const char*)&nzero,sizeof(int));
		setsockopt(m_socket,SOL_SOCKET,SO_RCVBUF,(const char*)&nzero,sizeof(int));

		int retval;  
		retval=bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));  
		if(SOCKET_ERROR==retval)  
		{  
		    closesocket(m_socket);  
		    AfxMessageBox("PLC网络连接异常");  
		    return ;  
	    	}  
		if(listen(m_socket,3) == SOCKET_ERROR)  
		{  
			//监听客户端，如果是基于UDP的，则不需要listen  
			AfxMessageBox("PLC网络连接异常3");  
	        	return ;  
		}   
#endif		

  // LPDWORD lpThreadID ;
    //创建一线程监听  
 //   RECVPARAM *pRecvParam=new RECVPARAM;  
	pRecvParam=new RECVPARAM;  
	pRecvParam->sock=m_socket;  
	pRecvParam->hwnd=wndHandle;  
	//	int len=sizeof(SOCKADDR);
	//SOCKET 
	//ConnectSocket = accept(m_socket,(sockaddr*)&addrSock,&len); 
//   HANDLE hThread=CreateThread(NULL,0,RecvProc,(LPVOID)pRecvParam,0,lpThreadID);
//	AfxBeginThread(RecvProc2,wndHandle,THREAD_PRIORITY_BELOW_NORMAL);	
//AfxBeginThread(AutoSampleThread,wndHandle,THREAD_PRIORITY_BELOW_NORMAL);		
//    CloseHandle(hThread);  
}

static   char recvBuf[6]={0};//获取客户端发送的消息  
static char dabiao =0;
static char weldcount = 0;

void SendNetCmd()
{
	SOCKET sock=   pRecvParam->sock;
	HWND hwnd= pRecvParam->hwnd;
	char sendbuf[8];

	memset(sendbuf,0,8*sizeof(char));
	sendbuf[0] = 0x12 ; sendbuf[1] = 0x34 ;sendbuf[2] = 0x43 ;sendbuf[3] = 0x21 ;
//	if(listen(sock,3) == SOCKET_ERROR)  
//	{  
//		//监听客户端，如果是基于UDP的，则不需要listen  
//		AfxMessageBox("PLC网络连接异常3");  
//        	return ;  
//	}   
//	delete pRecvParam;
	//	AfxMessageBox("PLC网络连接请求");  
	SOCKADDR_IN addrFrom;  
	int len=sizeof(SOCKADDR);
	ConnectSocket = accept(sock,(sockaddr*)&addrFrom,&len); 
	if( dabiao & 1 )
		{
			sendbuf[4] = 0x31;//横外
		//	sendbuf[5] = 0x41;//横内
		//	sendbuf[6] = 0x51;//纵外
		//	sendbuf[7] = 0x61;
		//	send(ConnectSocket,sendbuf,8,0);		
		}
	 else if( dabiao & 0x02 ){
			sendbuf[5] = 0x41;
		//	sendbuf[5] = 0;
		//	send(ConnectSocket,sendbuf,8,0);		
		}
	else if( dabiao  &  0x04 ){
			sendbuf[6] = 0x51;				
		//	send(ConnectSocket,sendbuf,8,0);		
		}
	else if( dabiao  &  0x08 ){
			sendbuf[7] = 0x61;					
		//	send(ConnectSocket,sendbuf,8,0);		
		}
	else if( dabiao & 0x10 ){
			sendbuf[4] = 0;
			sendbuf[5] = 0;
			sendbuf[6] = 0;
			sendbuf[7] = 0;
		//	send(ConnectSocket,sendbuf,8,0);		
		}
	 if(dabiao > 0 )
	 	{
	 	//	send(ConnectSocket,sendbuf,8,0);Sleep(1);
		//	send(ConnectSocket,sendbuf,8,0);Sleep(1);
		//	SOCKET ConnectSocket = accept(sock,(sockaddr*)&addrFrom,&len); 
			send(ConnectSocket,sendbuf,8,0);
			sendbuf[4] = 0;
			sendbuf[5] = 0;
			sendbuf[6] = 0;
			sendbuf[7] = 0;
			//Sleep(5);
			//Sleep(90);8888
			//send(ConnectSocket,sendbuf,8,0);
			dabiao = 0;//weldcount++;
		/**/	//	PLC 收到后，自己清零。
	 	}
	closesocket(ConnectSocket); 
}

UINT  RecvProc2(LPVOID lpParameter)  
{  
	char sendbuf[8];
 //   int retval;  

	SOCKET sock=   pRecvParam->sock;
	HWND hwnd= pRecvParam->hwnd;
	memset(sendbuf,0,8*sizeof(char));
	sendbuf[0] = 0x12 ; sendbuf[1] = 0x34 ;sendbuf[2] = 0x43 ;sendbuf[3] = 0x21 ;

	//	AfxMessageBox("PLC网络连接请求");  
	SOCKADDR_IN addrFrom;  
	int len=sizeof(SOCKADDR);  
	char lastrec[2];
	lastrec[0] = 0; 		lastrec[1] = 0;
	ConnectSocket = accept(sock,(sockaddr*)&addrFrom,&len); //得到客户端的IP地址。   	

	while(TRUE)  
	{  
		if(dabiao>0)
		{
		//FlagCard flag = ((RbhUsb20*)(TestSampleControl::cardPtr))->getFlagOfCard();	
			if( dabiao & 1 )
			{
				sendbuf[4] = 0x31;//横外
			}
			if( dabiao & 0x02 ){
				sendbuf[5] = 0x41;
			}
			if( dabiao  &  0x04 ){
				sendbuf[6] = 0x51;				
			}
			if( dabiao  &  0x08 ){
				sendbuf[7] = 0x61;					
			}
			if( dabiao & 0x10 ){
				sendbuf[4] = 0;
				sendbuf[5] = 0;
				sendbuf[6] = 0;
				sendbuf[7] = 0;
			}
			send(ConnectSocket,sendbuf,8,0);
			sendbuf[4] = 0;
			sendbuf[5] = 0;
			sendbuf[6] = 0;
			sendbuf[7] = 0;
	//		send(ConnectSocket,sendbuf,8,0);	
	//		weldcount++;
			dabiao = 0;
	//		closesocket(ConnectSocket); 
		}
			//	send(ConnectSocket,sendbuf,8,0);
	}
	closesocket(ConnectSocket);
   	//}  
	closesocket(sock);    
	WSACleanup();    

	return 0;  
}  
//宏的功能介绍:
//-------------------------------------------------------------
//ABOVE_NORMAL_PRIORITY_CLASS(0x00008000) 高于标准
//BELOW_NORMAL_PRIORITY_CLASS(0x00004000) 低于标准
//HIGH_PRIORITY_CLASS(0x00000080) 高
//IDLE_PRIORITY_CLASS(0x00000040) 低
//NORMAL_PRIORITY_CLASS(0x00000020) 标准
//REALTIME_PRIORITY_CLASS(0x00000100) 实时
//idle （最低）THREAD_PRIORITY_IDLE
//LOWEST 低THREAD_PRIORITY_LOWEST
//BELOW 低于标准THREAD_PRIORITY_BELOW_NORMAL
//NORMAL（标准）THREAD_PRIORITY_NORMAL
//ABOVE 高于标准THREAD_PRIORITY_ABOVE_NORMAL
//HIGHEST （高）		THREAD_PRIORITY_HIGHEST
//CRITICAL（最高)	THREAD_PRIORITY_TIME_CRITICAL
//

BOOL RbhUsb20::Start()
{
	GobalData* g = GobalData::getGobalData();
	DataSaveFactory factory;
	DeletePtr(g->gstyle);
	g->gstyle = factory.getDataSaveStyle(g->getSaveStyle());
    if(g->gstyle->IsNeedTrigger() == FALSE) //不需要触发
	{
	//	StopIntr();
		if( StartIntr(100,iBlockLen,0,channelNum,sampleSpeed * 1000,0,1) == 0) 
		{
			return FALSE;
		}
	//	StopIntr_1();
		if( StartIntr_1(100,iBlockLen,0,channelNum,sampleSpeed * 1000,0,1) == 0) 
		{
			return FALSE;
		}
		if((g->getUsb8221Par()).coding == TRUE)
		{
			AfxBeginThread(SampleThread,wndHandle,THREAD_PRIORITY_BELOW_NORMAL);
		}
	}
 //	AfxMessageBox("start ok");
	flagOfCard = FLAGCARD_START;
 //   AfxBeginThread(AutoSampleThread,wndHandle,THREAD_PRIORITY_BELOW_NORMAL);
	return TRUE;
}

void RbhUsb20::Stop()
{
//   if( StopIntr() == ADCard_Success )
    flagOfCard = FLAGCARD_STOP;
	StopIntr();
	StopIntr_1();
}

void RbhUsb20::setWnd(const HWND hwnd)
{
    wndHandle = hwnd;
}

void RbhUsb20::Pause()
{
    flagOfCard = FLAGCARD_PASUE;
}

void RbhUsb20::setDIsingal(const BOOL singal)
{
    DIsingal = singal;
}

BOOL RbhUsb20::getDIsingal() const
{
    return DIsingal;
}

void RbhUsb20::resume()
{
    flagOfCard = FLAGCARD_START;
}

WORD* RbhUsb20::getADbuf() const
{
    return ADBuf;
}
WORD* RbhUsb20::getADbuf1() const
{
    return ADBuf1;
}
int RbhUsb20::getBlockLen() const
{
    return iBlockLen;
}

FlagCard RbhUsb20::getFlagOfCard() const
{
    return flagOfCard;
}

/*
 * 带编码器的采集触发线程
 */
UINT SampleThread(LPVOID lpParam)
{
	WORD IOResult[32],DI0;
	while(TRUE)
	{
		if((RbhUsb20*)(TestSampleControl::cardPtr) == NULL)
			return 0;
		FlagCard flag = ((RbhUsb20*)(TestSampleControl::cardPtr))->getFlagOfCard();
		if(FLAGCARD_STOP == flag)     //采集卡停止
			return 0;
		if(FLAGCARD_PASUE == flag)    //采集卡暂停
			continue;
		Rbh_DI(9, IOResult);
		DI0 = IOResult[0] & 255;
		int Bit1 = 1;
		Bit1 = Bit1&DI0;
		
		static int oldFlag = Bit1;
		if(oldFlag == Bit1)
			continue;
		else
		{
			::SendMessage((HWND)lpParam,WM_SampleMsg,0,0);
			oldFlag = Bit1;
		}     
	}
	return 0;
}

/*
 *	自动触发采集线程
 */
UINT AutoSampleThread(LPVOID lpParam)
{
	GobalData* g = GobalData::getGobalData();
//	LARGE_INTEGER m_liPerfFreq={0};
//	QueryPerformanceFrequency(&m_liPerfFreq);
//	LARGE_INTEGER liPerfNow={0};
	while(TRUE)
	{
		FlagCard flag = ((RbhUsb20*)(TestSampleControl::cardPtr))->getFlagOfCard();
		if(FLAGCARD_STOP == flag)     //采集卡停止
			return 0;
		if(g->gstyle->autoSampleFuc() == TRUE) //fatal error
			break;
//		LONG64 V_Start2 = GetTickCount();
//		;
//		QueryPerformanceCounter(&liPerfNow);
	}
	return 0;
}

void RbhUsb20::setFlagOfCard(const FlagCard flag)
{
    flagOfCard = flag;
}

BOOL RbhUsb20::Democrate()
{
    return Start();
}

BYTE RbhUsb20::GetDigitalInput()
{
	WORD IOResult[32];
	
	Rbh_DI(2, IOResult);
//	DI0 = IOResult[0] & 255;
	BYTE result = IOResult[0]&0XFF;
//	BYTE result = DI0;
    return result;
}

BYTE RbhUsb20::GetDigitalInput1()
{
	WORD IOResult[32];
	
	Rbh_DI_1(2, IOResult);
//	DI0 = IOResult[0] & 255;
	
	BYTE result = IOResult[0]&0XFF;
    return result;
}

char RbhUsb20::GetDigitalInputByNet()
{
//	WORD IOResult[32],DI0=0;
	BYTE  DI0 = 0;
	if( recvBuf[0] == 0x12 &&  recvBuf[1] == 0x34 &&  recvBuf[2] == 0x43 &&  recvBuf[3] == 0x21)
		{
			//DI0= recvBuf[5]&(0x01)<<8+recvBuf[4]&(0x01) ;
			if( recvBuf[4] == 0x11 )
				DI0 = 1;
			else 
				DI0 = 0;
			if( recvBuf[5] == 0x21 )
				DI0 += 2;
			else
				DI0  = DI0&(0xd);
			return char(DI0);
		}	
       return 0x1f;
}

void GetNetIoStatus(char * comeIn)
{
	if(comeIn != NULL )
		{
			comeIn[0] = recvBuf[4];
			comeIn[1] = recvBuf[5];
			comeIn[2] = weldcount;
		}
}

void RbhUsb20::SendDigitalOuput(char d, BOOL isPlus)
{
   int ret= Rbh_DO(0, d);
    if(isPlus == TRUE)
	{
		Sleep(60);
		Rbh_DO(0, 0);
	}
}

void RbhUsb20::SendDigitalOuput2(char d, BOOL isPlus)
{
   int ret= Rbh_DO_1(0, d);
    if(isPlus == TRUE)
	{
		Sleep(60);
		Rbh_DO_1(0, 0);
	}
}

void RbhUsb20::SendDigitalOuputByNet(char d, BOOL isPlus)
{ 	
//  if(isPlus == TRUE)
//	{
	//   if((dabiao&d)  != d )
	//   	{
	   	//	dabiao = dabiao|d;
	   	dabiao = d;
		      SendNetCmd();			
	//   	}
//  	}
}

BOOL RbhUsb20::SampleStart()
{
	GobalData* g = GobalData::getGobalData();
	flagOfCard = FLAGCARD_START;
	weldcount = 0;	dabiao = 0;
	StopIntr();
	if( StartIntr(100,iBlockLen,0,channelNum,sampleSpeed * 1000,0,1) == 0) 
	{
	//	return FALSE;
	}

	StopIntr_1();
	if( StartIntr_1(100,iBlockLen,0,channelNum,sampleSpeed * 1000,0,1) == 0) 
	{
	//	return FALSE;
	}
	return TRUE;
}
