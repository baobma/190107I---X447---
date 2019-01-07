// SampleCard.h: interface for the CSampleCard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLECARD_H__72BA2CE8_C02A_498B_B021_8E9CE2C0B35B__INCLUDED_)
#define AFX_SAMPLECARD_H__72BA2CE8_C02A_498B_B021_8E9CE2C0B35B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
 *	数据采集卡抽象类
 */
class CSampleCard  
{
public:
	virtual BOOL SampleStart() = 0;
	virtual BOOL Democrate() = 0;                   //标定
	int getChannelNum();
	void setChannelNum(const int channelNum);
	void setSampleSpeed(const int speed);
	int getSampleSpeed();
	virtual void Stop() = 0;                        //停止
	virtual BOOL Start() = 0;                       //开始
	virtual BOOL Inital() = 0;                      //采集卡初始化
	virtual void workwithPlc()= 0;
	virtual BYTE GetDigitalInput() = 0;             //读取数字口状态
	virtual void SendDigitalOuput(char d, BOOL isPlus = TRUE) = 0;  //数字口输出
		virtual void SendDigitalOuput2(char d, BOOL isPlus = TRUE) = 0;  //数字口输出
	virtual char GetDigitalInputByNet() = 0;             //读取数字口状态
	virtual void SendDigitalOuputByNet(char d, BOOL isPlus = TRUE) = 0;  //数字口输出
	virtual BYTE GetDigitalInput1() = 0;             //读取数字口状态
	CSampleCard(const int sampleSpeed,const int channelNum = 32);
	virtual ~CSampleCard();
protected:
	int sampleSpeed;  //采样率
	int channelNum;   //通道数量
};

#endif // !defined(AFX_SAMPLECARD_H__72BA2CE8_C02A_498B_B021_8E9CE2C0B35B__INCLUDED_)
