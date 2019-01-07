// RbhUsb20.h: interface for the RbhUsb20 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RBHUSB20_H__2B197AF0_8EC7_43B6_BA37_B158342C8EF2__INCLUDED_)
#define AFX_RBHUSB20_H__2B197AF0_8EC7_43B6_BA37_B158342C8EF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SampleCard.h"
#include "ADCARD.h"
#include "ADCARD1.h"
#include "TestFuc.h"

enum FlagCard
{
	FLAGCARD_STOP, FLAGCARD_PASUE, FLAGCARD_START
};

#define IOBase 0x140
#define IRQNum 5
#define PhysAddr 0
#define DMAChn 0

#pragma comment(lib,"ADCARD")
void GetNetIoStatus(char * comeIn);
/*
*	RBH 网络USB2.0 8221(3) 采集卡类
 */
class RbhUsb20 : public CSampleCard  
{
public:
	BOOL SampleStart();
	virtual void SendDigitalOuput(char d,BOOL isPlus = TRUE);
		virtual void SendDigitalOuput2(char d,BOOL isPlus = TRUE);
	virtual BYTE GetDigitalInput();
	BOOL Democrate();
	void setFlagOfCard(const FlagCard flag);
	FlagCard getFlagOfCard() const;
	int getBlockLen() const;
	WORD* getADbuf() const;
	WORD* getADbuf1() const;
	void resume();
	BOOL getDIsingal() const;
	void setDIsingal(const BOOL singal);
	void Pause();
	virtual void workwithPlc();
	virtual void SendDigitalOuputByNet(char d,BOOL isPlus = TRUE);
	virtual char GetDigitalInputByNet();
	virtual BYTE GetDigitalInput1();             //读取数字口状态

	void setWnd(const HWND hwnd);
	RbhUsb20(HWND hwnd,const int sampleSpeed,const int channelNum = 32,const int iBlockLen = 100);
	virtual void Stop();
	virtual BOOL Start();
	virtual BOOL Inital();
	virtual ~RbhUsb20();

private:
	 SOCKET m_socket;                //m_socket用于收听
	RbhUsb20(const RbhUsb20& usbcard);
	RbhUsb20& operator=(const RbhUsb20& usbcard);
	FlagCard flagOfCard;
	HWND wndHandle;
	int iBlockLen;
	WORD* ADBuf;
	WORD* ADBuf1;
	BOOL DIsingal;
};

#endif // !defined(AFX_RBHUSB20_H__2B197AF0_8EC7_43B6_BA37_B158342C8EF2__INCLUDED_)
