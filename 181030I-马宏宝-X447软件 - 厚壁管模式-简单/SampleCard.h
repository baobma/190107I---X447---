// SampleCard.h: interface for the CSampleCard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLECARD_H__72BA2CE8_C02A_498B_B021_8E9CE2C0B35B__INCLUDED_)
#define AFX_SAMPLECARD_H__72BA2CE8_C02A_498B_B021_8E9CE2C0B35B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
 *	���ݲɼ���������
 */
class CSampleCard  
{
public:
	virtual BOOL SampleStart() = 0;
	virtual BOOL Democrate() = 0;                   //�궨
	int getChannelNum();
	void setChannelNum(const int channelNum);
	void setSampleSpeed(const int speed);
	int getSampleSpeed();
	virtual void Stop() = 0;                        //ֹͣ
	virtual BOOL Start() = 0;                       //��ʼ
	virtual BOOL Inital() = 0;                      //�ɼ�����ʼ��
	virtual void workwithPlc()= 0;
	virtual BYTE GetDigitalInput() = 0;             //��ȡ���ֿ�״̬
	virtual void SendDigitalOuput(char d, BOOL isPlus = TRUE) = 0;  //���ֿ����
		virtual void SendDigitalOuput2(char d, BOOL isPlus = TRUE) = 0;  //���ֿ����
	virtual char GetDigitalInputByNet() = 0;             //��ȡ���ֿ�״̬
	virtual void SendDigitalOuputByNet(char d, BOOL isPlus = TRUE) = 0;  //���ֿ����
	virtual BYTE GetDigitalInput1() = 0;             //��ȡ���ֿ�״̬
	CSampleCard(const int sampleSpeed,const int channelNum = 32);
	virtual ~CSampleCard();
protected:
	int sampleSpeed;  //������
	int channelNum;   //ͨ������
};

#endif // !defined(AFX_SAMPLECARD_H__72BA2CE8_C02A_498B_B021_8E9CE2C0B35B__INCLUDED_)
