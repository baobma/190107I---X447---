// WaveShow.cpp: implementation of the CWaveShow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HUSTNDT.h"
#include "WaveShow.h"
#include "TestFuc.h"
#include <stdlib.h>
#include <time.h>



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "GobalData.h"

extern BOOL showLengthRule ;
//extern BOOL addOrDel;
//BOOL ThickPipeMode = FALSE;
//BOOL thickPipe_flag = FALSE;
//extern  int  inspect;
//extern float G_m_menxianzhi;
//int find_weld_series = 0;
//焊缝上通道数量

//BOOL drawXPt,drawYPt;
//BOOL drawXPt1,drawYPt1;
//extern int Hright_step ,Vright_step ;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
 *	pWnd: 显示块对应的窗口
 */
CWaveShow::CWaveShow(CWnd* pWnd,const int xMax, const int yMax)
:Wndshow(pWnd)
{
	this->blockcompress = 100;
    this->xMax = xMax;
	this->yMax = yMax;
	alertLine = 50;
	alertLine2 = 50;
	screenPage = 1;
	step = 1;	

	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	//alerty1 = set.alertline[0]*2048/100;//报警门限1
	//alerty2 = set.alertline[2]*2048/100;//报警门限2
	//thickPipe_flag = FALSE;
	setAlertyPar();
}

CWaveShow::~CWaveShow()
{

}
/*
 *	画显示块的背景
 */
void CWaveShow::DrawBack(CDC* pdc,int k[21])
{

	CRect rect;
    CWnd* pWnd = this->Wndshow;
    pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	CGdiObject* systemPen = NULL;
	CGdiObject* systemBrush = NULL;
	CGdiObject* org = NULL;
	
	CPen blackPen;
	CPen GreenPen;
// 	if(IsCombine == FALSE)
// 	{
 		blackPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
		GreenPen.CreatePen(PS_SOLID,1,RGB(0,255,0));
// 	}
// 	else
// 	{
//		blackPen.CreatePen(PS_SOLID,1,RGB(0,255,255));
//	}

		int max = 0;
	
		for (int i = 0; i<21;i++)
		{
			if (k[i]>max)
			{
				max = k[i];
			}
		}
    
		systemPen = pdc->SelectObject(&GreenPen);
	pdc->Rectangle(0,0,alertLine*2,max);    //画试板

	for( i = 1; i < 10; i++)
	{
		pdc->MoveTo(kx*i/10,ky);
		pdc->LineTo(kx*i/10,0);
	}
	for(int j = 1; j < 10; j++)
	{
		pdc->MoveTo(0 ,      ky*j/10);
		pdc->LineTo(kx , ky*j/10);
		}
	
//	pdc->Rectangle(0,0,xMax,yMax);
// 	int x1 = (j % (xMax / step)) * step;
// 	int xc = x1*kx/xMax + rect.left;
// 	int yc = rect.bottom - (y+yn)*ky/yMax;

	systemPen = pdc->SelectObject(&blackPen);
	int cx = 0,cy = 0;
	cx = k[20]*kx/max;
	cy = rect.bottom;
	pdc->MoveTo(cx,cy);
	cx = k[19]*kx/max;
	cy = rect.bottom-1*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[18]*kx/max;
	cy = rect.bottom-2*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[17]*kx/max;
	cy = rect.bottom-3*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[16]*kx/max;
	cy = rect.bottom-4*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[15]*kx/max;
	cy = rect.bottom-5*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[14]*kx/max;
	cy = rect.bottom-6*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[13]*kx/max;
	cy = rect.bottom-7*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[12]*kx/max;
	cy = rect.bottom-8*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[11]*kx/max;
	cy = rect.bottom-9*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[10]*kx/max;
	cy = rect.bottom-10*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[9]*kx/max;
	cy = rect.bottom-11*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[8]*kx/max;
	cy = rect.bottom-12*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[7]*kx/max;
	cy = rect.bottom-13*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[6]*kx/max;
	cy = rect.bottom-14*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[5]*kx/max;
	cy = rect.bottom-15*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[4]*kx/max;
	cy = rect.bottom-16*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[3]*kx/max;
	cy = rect.bottom-17*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[2]*kx/max;
	cy = rect.bottom-18*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[1]*kx/max;
	cy = rect.bottom-19*ky/20;
	pdc->LineTo(cx,cy);
	cx = k[0]*kx/max;
	cy = rect.bottom-20*ky/20;
	pdc->LineTo(cx,cy);

	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
	pWnd->ReleaseDC(pdc);
}

int CWaveShow::getxMax()
{
    return xMax;
}

int CWaveShow::getyMax()
{
    return yMax;
}

int CWaveShow::getStep()
{
    return step;
}

float CWaveShow::getCurrentPosition(int ch)
{
	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	int dataLen = buf->getdataLens(ch);
    float position = (dataLen%(xMax/step) * 1.0f/(xMax/step));
	return position;
}

void CWaveShow::setStep(int s)
{
    step = s;
}

void CWaveShow::nextScreen()
{
    screenPage++;
//	find_weld_series = 0;
}

void CWaveShow::preScreen()
{
	if(screenPage > 1)
	{
        screenPage--;
	//		find_weld_series = 0;
	}
}

void CWaveShow::resetScreen()
{
    screenPage = 1;
}

short CWaveShow::getAlertLine()
{
    return alertLine;
}

void CWaveShow::setAlertLine(short a)
{
//     a = a > 100 ? 100 : a;
// 	a = a < 0   ? 0   : a;
	alertLine = a;
}


void CWaveShow::setPage(int p)
{
//   if( screenPage != p )
//   find_weld_series = 0;
    screenPage = p < 1 ? 1: p;
}

void CWaveShow::setxMax(int xMax)
{
    this->xMax = xMax;
}

/*
 *  通道简单显示风格
 *	starch:启始通道号
 *  endch :结束通道号
 *  blocklen: 压缩显示块长
 *  fault   : 是否为缺陷显示模式  FALSE:显示波形  TRUE:显示缺陷分布
 */
void CWaveShow::DrawWave_block(int startch, int endch, int blocklen, BOOL fault)
{ 
    CWnd* pWnd = Wndshow;
    CDC* pdc = pWnd->GetDC();
	pWnd->UpdateWindow();
	
	if(fault == FALSE)
	{
	    FloorMapSet(pWnd,pdc,xMax,yMax);
	}
	else
        FloorMapSet(pWnd,pdc,xMax,8);
 
	CGdiObject* systemPen = NULL;
	CGdiObject* org = NULL;
	
	CPen penA(PS_SOLID,1,RGB(128,0,0));
	CPen Pen0(PS_SOLID,1,RGB(128,0,0));	
	CPen Pen1(PS_SOLID,1,RGB(255,128,64));
	CPen Pen2(PS_SOLID,1,RGB(255,255,0));
	CPen Pen3(PS_SOLID,1,RGB(0,255,0));	
	CPen Pen4(PS_SOLID,1,RGB(0,128,64));
	CPen Pen5(PS_SOLID,1,RGB(0,0,255));
	CPen Pen6(PS_SOLID,1,RGB(128,0,255));
	CPen Pen7(PS_SOLID,1,RGB(0,255,255));
	
	CPen* pens[8] = 
	{
		&Pen0,&Pen1 ,&Pen2,&Pen3,
		&Pen4,&Pen5 ,&Pen6,&Pen7
	};
    systemPen = pdc->SelectObject(&penA);
	
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();   //数据缓存指针
	
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格

	int start = (screenPage - 1) * xMax / step;
	for(int i = startch; i <= endch; i++)
	{
		int dataLen = databuf->getdataLens(i);
        int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);

		org = pdc->SelectObject(pens[i-startch]);
		org->DeleteObject();
		
		int yn = yMax/2-restrainY*yMax/100;            //显示块基准
		for(int j = start; j <= end; j += blocklen)
		{
			int y = 0;
			style->getShowWaveNum(databuf,i,j,blocklen,timelapes,y);  //取得显示值
			int x1 = (j % (xMax / step)) * step;
			if(x1 == 0 && j != start)
				x1 = xMax;
			if(fault == false)
			{
				if(j == start)
				{
					pdc->MoveTo(x1,y+yn);
				}
				else
				{
					pdc->LineTo(x1,y+yn);   //画波形
				}
			}
			else  //画缺陷分布
			{
				int ch = i - startch;
				if( y+yn > alertLine*yMax/(2*100)+yMax/2 )
				{
                    pdc->MoveTo(x1,8 - ch);
					pdc->LineTo(x1,8 - ch - 1);
				}
			}
		}
	}
	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
	pWnd->ReleaseDC(pdc);
	DeletePtr(style);
}

int CWaveShow::getScreenPage()
{
    return screenPage;
}

void CWaveShow::setWaveStyle(WaveShowStyle s)
{
    wavestyle = s;
}

WaveShowStyle CWaveShow::getWaveShowStyle()
{
    return wavestyle;
}

/*
 *  通道融合显示风格
 *	starch:启始通道号
 *  endch :结束通道号
 *  blocklen: 压缩显示块长
 */
void CWaveShow::DrawWave_combine(int startch, int endch, int blocklen)
{
    CWnd* pWnd = Wndshow;
    CDC* pdc = pWnd->GetDC();
	pWnd->UpdateWindow();
	FloorMapSet(pWnd,pdc,xMax,yMax);
	
	CGdiObject* systemPen = NULL;
	CGdiObject* org = NULL;
	
	CPen penA(PS_SOLID,1,RGB(0,0,0));

    systemPen = pdc->SelectObject(&penA);
	
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf(); //数据缓存指针
	
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格
	
	int start = (screenPage - 1) * xMax / step;

	int dataLen = databuf->getdataLens(startch);
	int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);
	
	for(int j = start; j <= end; j += blocklen)
	{
		int y = 0;
		style->getShowWaveNum(databuf,startch,endch-startch,j,blocklen,timelapes,y);//取得显示值
		int yn = yMax/2-restrainY*yMax/100;
		int x1 = (j % (xMax / step)) * step;
		if(x1 == 0 && j != start)
			x1 = xMax;
		if(j == start)
		{
			pdc->MoveTo(x1,y+yn);
		}
		else
		{
			pdc->LineTo(x1,y+yn);  //画波形
		}
	}

	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
	pWnd->ReleaseDC(pdc);
	DeletePtr(style);
}

void CWaveShow::setRestrainY(short r)
{
     restrainY = r;
}

/*
 *	//缺陷显示模式背景
 */
void CWaveShow::DrawWaveFaultBack(CDC *pdc)  
{
	CRect rect;
    CWnd* pWnd = this->Wndshow;
    pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	
	CGdiObject* systemPen = NULL;
	CGdiObject* systemBrush = NULL;
	CGdiObject* org = NULL;
	CPen blackPen(PS_SOLID,1,RGB(0,0,0));
    systemPen = pdc->SelectObject(&blackPen);
	
	pdc->Rectangle(0,0,xMax,yMax);    //画试板
	pdc->MoveTo(0,yMax/2);
	pdc->LineTo(xMax,yMax/2);         //中心坐标线
	
	for(int i = 1; i < 10; i++)
	{
		pdc->MoveTo(kx*i/10,rect.bottom - ky/2);
		pdc->LineTo(kx*i/10,rect.bottom - ky/2 - ky/30);
	}
	
	for(int j = 1; j < 4; j++)
	{
		pdc->MoveTo(0 ,rect.bottom -  ky*j/4);
		pdc->LineTo(kx,rect.bottom -  ky*j/4);
	}
	
	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
	pWnd->ReleaseDC(pdc);
}

void CWaveShow::aotuToCurrentPage(int i)
{
    	GobalData* g = GobalData::getGobalData();
	DataBuf* buf = g->getDataBuf();
	int dataLen = buf->getdataLens(g->showCHS[0][i]);
    	int p = (dataLen-1)/(xMax/step) + 1;  //-1是为了在整屏的时候显示前一屏
	setPage(p);
}

short CWaveShow::getAlertLine2()
{
    return alertLine2;
}

void CWaveShow::setAlertLine2(short a)
{
    alertLine2 = a;
}

short CWaveShow::getAlertLine3()
{
    return alertLine3;
}
//获取横向报警下线
float CWaveShow::getHoriAlertyParL()
{
	return 	alerty1_xiaxian;
}
//获取横向报警上限
float CWaveShow::getHoriAlertyParH()
{
	return 	alerty1_shangxian;
}
//获取纵向报警下线
float CWaveShow::getVertAlertyParL()
{
	return 	alerty2_xiaxian;
}
//获取纵向报警上限
float CWaveShow::getVertAlertyParH()
{
	return 	alerty2_shangxian;
}


void CWaveShow::setAlertLine3(short a)
{
    alertLine3 = a;
}

void CWaveShow::setAlertyPar()
{
	GobalData* g = GobalData::getGobalData();
	AUTOSET& set = g->getAutoSet();
	alerty1 = set.alertline[0]*2048/100;//报警门限1
	alerty2 = set.alertline[2]*2048/100;//报警门限2
	int h_sel = set.nserl_hacc;//横向动态增益系数
	int v_sel = set.nserl_vacc;//纵向动态增益系数
	switch(h_sel)
	{
	case 0:
		alerty1_shangxian = alerty1;
		alerty1_xiaxian = alerty1;
		break;
	case 1:
		alerty1_shangxian = (int)(alerty1*1.12);
		alerty1_xiaxian = (int)(alerty1/1.12);
		break;
	case 2:
		alerty1_shangxian = (int)(alerty1*1.26);
		alerty1_xiaxian = (int)(alerty1/1.26);
		break;
	case 3:
		alerty1_shangxian = (int)(alerty1*1.41);
		alerty1_xiaxian = (int)(alerty1/1.41);
		break;
	case 4:
		alerty1_shangxian = (int)(alerty1*1.585);
		alerty1_xiaxian = (int)(alerty1/1.585);
		break;
	}
	switch(v_sel)
	{
	case 0:
		alerty2_shangxian = alerty2;
		alerty2_xiaxian = alerty2;
		break;
	case 1:
		alerty2_shangxian = alerty2*1.12;
		alerty2_xiaxian = alerty2/1.12;
		break;
	case 2:
		alerty2_shangxian = alerty2*1.26;
		alerty2_xiaxian = alerty2/1.26;
		break;
	case 3:
		alerty2_shangxian = alerty2*1.41;
		alerty2_xiaxian = alerty2/1.41;
		break;
	case 4:
		alerty2_shangxian = alerty2*1.585;
		alerty2_xiaxian = alerty2/1.585;
		break;
	}
}



void CWaveShow::setDifferAdjust(short i)
{
	differadjust = i;
}

short CWaveShow::getDifferAdjust()
{
	return differadjust;
}

void CWaveShow::setDiffer(short i)
{
	differ = i;
}

short CWaveShow::getDiffer()
{
	return differ;
}
/*
 *	双缓存画图
 */
void CWaveShow::DrawWave_combineEx(CDC *pdc, int startch, int endch, int blocklen,int dataOpenMode)
{
	blocklen = blockcompress;
    CWnd* pWnd = Wndshow;
	CRect rect;
    pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	
	CGdiObject* systemPen = NULL;
	CGdiObject* org = NULL;
	
	CPen penA(PS_SOLID,1,RGB(128,0,0));
	CPen Pen0(PS_SOLID,1,RGB(160,82,45));  //综红
	CPen Pen1(PS_SOLID,1,RGB(255,97,0));   //橙
	CPen Pen2(PS_SOLID,1,RGB(255,200,0));  //黄
	CPen Pen3(PS_SOLID,1,RGB(0,255,0));	//绿
	CPen Pen4(PS_SOLID,1,RGB(8,46,84));    //靛青 
	CPen Pen5(PS_SOLID,1,RGB(0,0,255));    //蓝
	CPen Pen6(PS_SOLID,1,RGB(160,32,240)); //紫 
	CPen Pen7(PS_SOLID,1,RGB(135,206,235));//天蓝
	
	CPen* pens[8] = 
	{
		&Pen0,&Pen1 ,&Pen2,&Pen3,
		&Pen4,&Pen5 ,&Pen6,&Pen7
	};
    systemPen = pdc->SelectObject(&penA);
	
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf(); //数据缓存指针
	float speed =g->getAutoSet().speed; 
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格
	
	int start = (screenPage - 1) * xMax / step;
for(int i = startch; i <= endch; i=8+i)
{  
		int dataLen = databuf->getdataLens(i);
        	int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);
		if(end <= 0)
			continue;
		if( i > 71 ){
				org = pdc->SelectObject(pens[(i-72)/8]);
		}else if ( i>=4 ) 
			org = pdc->SelectObject(pens[(i-4)/8]);
		else
       		org = pdc->SelectObject(pens[i%8]);
		int yn = yMax/2-restrainY*yMax/100;            //显示块基准
		if(half == TRUE)
		{
			yn = -restrainY*yMax/100;
		}
	
		end = end - end%blocklen;
		for(int j = start; j <= end; j += blocklen)
		{
			int y = 0;
			int x1 = (j % (xMax / step)) * step;
			if(x1 == 0 && j != start)
				x1 = xMax;
			int xc = x1*kx/xMax + rect.left;			
		
			style->getShowWaveNum(databuf,i,7,j,blocklen,timelapes,y);	
			
			if (y<alertLine2*2048/(100)) 
			{
				y=y/3;
			}		
			int yc = rect.bottom - (y+yn)*ky/yMax;
			
			if(half == TRUE)
			{
				yc = rect.bottom - 2*(y+yn)*ky/yMax;
			}
	
		if( showLengthRule == TRUE && startch == 104  )
			{
				CString ruleValue;
				if( j%3000 == 0 && j >0 ){
				ruleValue.Format(_T("%.1f"),j*speed);
				pdc->TextOut(xc,rect.top+rect.bottom/25,ruleValue);
				}
			}
			{
				if(j == start)
				{
					pdc->MoveTo(xc,yc);
				}
				else
				{
					pdc->LineTo(xc,yc);   //画波形
				}
			}
			
		}
	}
	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
	pWnd->ReleaseDC(pdc);
	DeletePtr(style);
	
}

CWnd* CWaveShow::getWnd()
{
    return Wndshow;
}

void CWaveShow::DrawBackEx(CDC* pdc,BOOL IsCombine)
{
	CRect rect;
	CWnd* pWnd = this->Wndshow;
	pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	CGdiObject* systemPen = NULL;
	CGdiObject* systemBrush = NULL;
	CGdiObject* org = NULL;
	CPen blackPen;
	if(IsCombine == FALSE)
	{
		blackPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	}
	else
	{
		blackPen.CreatePen(PS_SOLID,1,RGB(0,255,255));
	}
    
	pdc->Rectangle(0,0,xMax,yMax);    //画试板

		if(half == TRUE) //半屏显示
		{
			for(int i = 1; i < 10; i++)
			{
				pdc->MoveTo(kx*i/10,ky);
				pdc->LineTo(kx*i/10,ky-ky/20);
			}
			for(int j = 1; j < 5; j++)
			{
				pdc->MoveTo(0 ,      ky*j/5);
				pdc->LineTo(kx/100 , ky*j/5);
			}
		}
		else
		{
			int m= 25/step;
			for(int i = 1; i <m; i++)
			{
				pdc->MoveTo(kx*i/m,ky);
				pdc->LineTo(kx*i/m,ky - ky/5);
			}

			for( i = 1; i <5*m; i++)
			{
				pdc->MoveTo(kx*i/(5*m),ky);
				pdc->LineTo(kx*i/(5*m),ky - ky/10);
			}
			for(int j = 1; j < 10; j++)
			{
				pdc->MoveTo(0 ,      ky*j/10);
				pdc->LineTo(kx/100 , ky*j/10);
			}
		}	
	systemPen = pdc->SelectObject(&blackPen);
	CPen redPen(PS_SOLID,1,RGB(255,0,0));
	CPen bluePen(PS_SOLID,1,RGB(0,0,255));

	if(half == TRUE)
	{
		org = pdc->SelectObject(&redPen);
		org->DeleteObject();
		pdc->MoveTo(0,ky - ky * alertLine / 100);
		pdc->LineTo(kx,ky - ky * alertLine / 100);
	
	}
	else
	{
		pdc->MoveTo(0,ky/2);
		pdc->LineTo(kx,ky/2);                        //中心坐标线		
		org = pdc->SelectObject(&redPen);
		org->DeleteObject();
		pdc->MoveTo(0,ky/2 - ky * alertLine / 200);
		pdc->LineTo(kx,ky/2 - ky * alertLine / 200);

	}

	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
//	pWnd->ReleaseDC(pdc);
}
//找伤的信号
int CWaveShow::GetAverageMaxofCHS(int startch, int endch, int blocklen, int ch,int start, int end)
{
	return 0;
}

int CWaveShow::GetAverageMaxofCHS2(int startch, int endch, int blocklen, int ch,int start, int end)
{
	return 0;
}

void CWaveShow::DrawWave_blockEx(CDC *pdc, int startch, int endch, int blocklen, BOOL fault,int dataOpenMode)
{
	blocklen = blockcompress;
	CWnd* pWnd = Wndshow;
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	
	
	CGdiObject* systemPen = NULL;
	CGdiObject* org = NULL;
	
	CPen penA(PS_SOLID,1,RGB(128,0,0));
	CPen Pen0(PS_SOLID,1,RGB(160,82,45));  //综红
	CPen Pen1(PS_SOLID,1,RGB(255,97,0));   //橙
	CPen Pen2(PS_SOLID,1,RGB(255,200,0));  //黄
	CPen Pen3(PS_SOLID,1,RGB(0,255,0));	//绿
	CPen Pen4(PS_SOLID,1,RGB(8,46,84));    //靛青 
	CPen Pen5(PS_SOLID,1,RGB(0,0,255));    //蓝
	CPen Pen6(PS_SOLID,1,RGB(160,32,240)); //紫 
	CPen Pen7(PS_SOLID,1,RGB(135,206,235));//天蓝
	
	CPen* pens[8] = 
	{
		&Pen0,&Pen1 ,&Pen2,&Pen3,
		&Pen4,&Pen5 ,&Pen6,&Pen7
	};
    systemPen = pdc->SelectObject(&penA);
//	drawXPt = FALSE;drawYPt = FALSE;
//	drawXPt1 = FALSE;drawYPt1 = FALSE;
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();   //数据缓存指针
	WORD** data = databuf->getDataPtr();
//	float speed =g->getAutoSet().speed; 
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格
	AUTOSET& set = g->getAutoSet();
//	float speed =set.speed;
	int start = (screenPage - 1) * xMax / step;

	for(int i = startch; i <= endch; i++)
	{  
		int dataLen = databuf->getdataLens(i);
        int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);
		if(end <= 0)
			continue;
		if( i > 71 )		
			org = pdc->SelectObject(pens[i%8]);
		else if (i>=4)
			org = pdc->SelectObject(pens[(i-4)%8]);
		else
			org = pdc->SelectObject(pens[i%8]);
		int yn = yMax/2-restrainY*yMax/100;	
		if(half == TRUE)
		{
			yn = -restrainY*yMax/100;
		}
		end = end - end%blocklen;
		for(int j = start;j <= end;j += blocklen)
		{
			int y = 0;
			int x1 = (j % (xMax / step)) * step;
			if(x1 == 0 && j != start)
				x1 = xMax;
			int xc = x1*kx/xMax + rect.left;
			switch(dataOpenMode)
			{
			case 0:
				style->getShowWaveNum(databuf,i,j,blocklen,timelapes,y);	
				break;
			case 1:
				style->getShowWaveNum3(databuf,i,j,blocklen,y);
				break;
			default:
				break;
			}
			if((alertLine2 !=0 )&&(y<alertLine2*2048/100))
			{
				y=y/3;
			}	

			if(i<72)
			{
				int alerty1_l = getHoriAlertyParL();//报警门限1
				int alerty1_h = getHoriAlertyParH();
				if (y>alerty1_l && y<alerty1_h)
					{
						y = alerty1 + 0.3*y;
						if (y>2000)
						{
							y=2000;
						}
					}
			}
			else
			{
				float alerty2_l = getVertAlertyParL();//报警门限1
				float alerty2_h = getVertAlertyParH();
				if (y>alerty2_l && y<alerty2_h)
				{
					y = alerty2 +0.3*y;
					if (y>2000)
					{
						y=2000;
					}
				}
			}
			if( showLengthRule == TRUE && i == 104  )
			{
				CString ruleValue;
				if( j%3000 == 0 && j >0 && set.speed>0 )
				{
					ruleValue.Format(_T("%.1f"),j*set.speed);
					pdc->TextOut(xc,rect.top+rect.bottom/25,ruleValue);
				}
			}
			 		 
//(0-5v)  对应满屏的上半部
			int yc = rect.bottom - (y+yn)*ky/yMax;
			if(half == TRUE)
			{
				yc = rect.bottom - 2*(y+yn)*ky/yMax;
			}
			if(j == start)
			{
					pdc->MoveTo(xc,yc);
			}
			else
			{
					pdc->LineTo(xc,yc);
			}			
		}
	}
	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	pWnd->ReleaseDC(pdc);
	DeletePtr(style);
}

void CWaveShow::DrawWaveFaultBackEx(CDC *pdc)
{
    CRect rect;
    CWnd* pWnd = this->Wndshow;
    pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	
	CGdiObject* systemPen = NULL;
	CGdiObject* systemBrush = NULL;
	CGdiObject* org = NULL;
	CPen blackPen(PS_SOLID,1,RGB(0,0,0));
    systemPen = pdc->SelectObject(&blackPen);
 
	pdc->Rectangle(0,0,xMax,yMax);    //画试板
	pdc->MoveTo(0,yMax/2);
	pdc->LineTo(xMax,yMax/2);         //中心坐标线
	
	for(int i = 1; i < 10; i++)
	{
		pdc->MoveTo(kx*i/10,rect.bottom - ky/2);
		pdc->LineTo(kx*i/10,rect.bottom - ky/2 - ky/30);
	}
	
	for(int j = 1; j < 8; j++)
	{
		pdc->MoveTo(0 ,rect.bottom -  ky*j/8);
		pdc->LineTo(kx,rect.bottom -  ky*j/8);
	}
	
	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
//	pWnd->ReleaseDC(pdc);
}

BOOL CWaveShow::ishalfshow()
{
    return half;
}

void CWaveShow::setHalfShow(BOOL h)
{
    half = h;
}

void CWaveShow::setShowCompress(short i)
{
    blockcompress = i;
}

short CWaveShow::getShowCompress()
{
    return blockcompress;
}
// 二阶
void CWaveShow::DrawDifferWave(CDC *pdc, int startch, int endch, int blocklen,int dataOpenMode)
{
	blocklen = blockcompress;
	CWnd* pWnd = Wndshow;
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	
	CGdiObject* systemPen = NULL;
	CGdiObject* org = NULL;
	
	CPen penA(PS_SOLID,1,RGB(128,0,0));
	CPen Pen0(PS_SOLID,1,RGB(160,82,45));  //综红
	CPen Pen1(PS_SOLID,1,RGB(255,97,0));   //橙
	CPen Pen2(PS_SOLID,1,RGB(255,200,0));  //黄
	CPen Pen3(PS_SOLID,1,RGB(0,255,0));	//绿
	CPen Pen4(PS_SOLID,1,RGB(8,46,84));    //靛青 
	CPen Pen5(PS_SOLID,1,RGB(0,0,255));    //蓝
	CPen Pen6(PS_SOLID,1,RGB(160,32,240)); //紫 
	CPen Pen7(PS_SOLID,1,RGB(135,206,235));//天蓝
	
	CPen* pens[8] = 
	{
		&Pen0,&Pen1 ,&Pen2,&Pen3,
		&Pen4,&Pen5 ,&Pen6,&Pen7
	};
    	systemPen = pdc->SelectObject(&penA);	
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();   //数据缓存指针

	AUTOSET& set = g->getAutoSet();
	WORD** data = databuf->getDataPtr();	
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格
//	drawXPt = FALSE;drawYPt = FALSE;
//		int drawweld  = 0;
	int start = (screenPage - 1) * xMax / step;
	for(int i = startch; i <= endch; i++)
	{
		int dataLen = databuf->getdataLens(i);
        int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);
		if(end <= 0)
			continue;
	
		if( i > 71 )		
			org = pdc->SelectObject(pens[i%8]);
		else if (i>=4) 
			org = pdc->SelectObject(pens[(i-4)%8]);
		else
			org = pdc->SelectObject(pens[i%8]);
        	int yn = yMax/2-restrainY*yMax/100;            //显示块基准
		if(half == TRUE)
		{
			yn = -restrainY*yMax/100;
		}
		
		end = end - end%blocklen;
		for(int j = start; j <= end; j += blocklen)
		{
			int y = 0;
		//	switch(dataOpenMode)
		//	{
		//	case 0: 
				style->GetDifferWaveNum(databuf,i,j,blocklen,timelapes,y);	
		//		break;
		//	case 1:
		//		style->GetWaveNum(databuf,i,j,blocklen,timelapes,y);  //取得显示值
		//		break;
		//	default:
		//		break;
		//	}		
			if (y<alertLine2*2048/(100)&& alertLine2!=0) 
			{
				y=y/3;
			}
			int x1 = (j % (xMax / step)) * step;

			if(x1 == 0 && j != start)
				x1 = xMax;
			int xc = x1*kx/xMax + rect.left;

			if( showLengthRule == TRUE && i == 104  )
			{
				CString ruleValue;
				if( j%3000 == 0 && j >0 && set.speed>0){
						ruleValue.Format(_T("%.1f"),j*set.speed);
						pdc->TextOut(xc,rect.top+rect.bottom/25,ruleValue);
					}				
			}
	#if 0		
			if( showLengthRule == TRUE && i == 4  )
				{
					extern int hEndCutTime;
					extern char indexAlert;
					extern int recordXPt[10];

					if( drawXPt == FALSE && j > set.alertline3[0] )
						{
							drawXPt = TRUE;
							pdc->FillSolidRect(xc,rect.top,8,8,RGB(0,255,0)); 
						}
					if( drawXPt1 == FALSE && (j>( hEndCutTime+set.alertline3[1]) && (hEndCutTime!=0)))
						{
							drawXPt1 =  TRUE;
							pdc->FillSolidRect(xc,rect.top,8,8,RGB(0,255,0)); 
						}
					if(    j >= set.alertline3[0]&&(set.alertline3[4]==1) )
						{						
							if(  recordXPt[drawweld] == j )
								{
											int y1=0; int y2 =0;
											int nn = set.alertline3[5];
											int start1 =j;							
											int block = 100+nn*100;
											if( start1+block > (hEndCutTime + set.alertline3[1]) )
												block = hEndCutTime + set.alertline3[1]-start1;
											
											style->getShowWaveNum(databuf,4,31,start1,block,set.timelapes[0],y1);
											style->getShowWaveNum(databuf,36,31,start1,block,set.timelapes[1],y2);	
											if(y1 > set.alertline[0]*2048/100 && y2 > set.alertline[1]*2048/100 )
											{
												pdc->FillSolidRect(xc,rect.top,8,4,RGB(0,0,255));
											}
											else
												{															
													pdc->FillSolidRect(xc,rect.top,8,4,RGB(255,0,0));
												}
											drawweld++;
									}
						}
						
				}
			 else  if( showLengthRule == TRUE && i == 72  )
				{
					extern  int vEndCutTime;
					extern char indexAlert2;
					extern int recordYPt[20];

					if( drawYPt == FALSE &&  j > set.alertline3[2])
						{
							drawYPt = TRUE;
							pdc->FillSolidRect(xc,rect.top,8,8,RGB(0,255,0)); 
						}
					if( drawYPt1 == FALSE && (j> vEndCutTime+set.alertline3[3]) && (vEndCutTime!=0))
						{
							drawYPt1 = TRUE;
							pdc->FillSolidRect(xc,rect.top,8,8,RGB(0,255,0)); 
						}
					if(( j >=  set.alertline3[2] )/*&& (j<=(vEndCutTime + set.alertline3[3]))*/&&(set.alertline3[4]==1))
						{							
							if(  recordYPt[drawweld] == j )
								{
									int start1 = j; 
									int y1=0; int y2 =0;
									int nn = set.alertline3[6];
									int block = 100+nn*100;
								
									if( start1+block > dataLen)
										block = dataLen-start1;
								
									style->GetMinWaveNum(databuf,72,31,start1,block,set.timelapes[2],y1);
									style->GetMinWaveNum(databuf,104,31,start1,block,set.timelapes[3],y2);
									if(y1 > set.alertline[2]*2048/100  && y2 > set.alertline[3]*2048/100  )
										{									
											pdc->FillSolidRect(xc,rect.top,4,8,RGB(0,0,255));
										}
									else
										{									
												pdc->FillSolidRect(xc,rect.top,4,8,RGB(255,0,0));
										}
									
									drawweld++;
								}
						}
				
						}
#endif
			int yc = rect.bottom - (y+yn)*ky/yMax;
			if(half == TRUE)
			{
				yc = rect.bottom - 2*(y+yn)*ky/yMax;
			}
			if(j == start)
			{
				pdc->MoveTo(xc,yc);
			}
			else
			{
				pdc->LineTo(xc,yc);   //画波形
			}

		}
	}
	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
	pWnd->ReleaseDC(pdc);
	DeletePtr(style);
}

void CWaveShow::DrawWavePhase(CDC *pdc, int startch, int endch, int blocklen)
{
// 	blocklen = blockcompress;
// 	CWnd* pWnd = Wndshow;
// 	CRect rect;
//     pWnd->GetClientRect(&rect);
// 	pWnd->UpdateWindow();
// 	int kx = rect.right - rect.left;
// 	int ky = rect.bottom - rect.top;
// 	
// 	CGdiObject* systemPen = NULL;
// 	CGdiObject* org = NULL;
// 	
// 	CPen penA(PS_SOLID,1,RGB(255,0,0));
// 	CPen Pen0(PS_SOLID,1,RGB(160,82,45));  //综红
// 	CPen Pen1(PS_SOLID,1,RGB(255,97,0));   //橙
// 	CPen Pen2(PS_SOLID,1,RGB(255,200,0));  //黄
// 	CPen Pen3(PS_SOLID,1,RGB(0,255,0));	   //绿
// 	CPen Pen4(PS_SOLID,1,RGB(8,46,84));    //靛青 
// 	CPen Pen5(PS_SOLID,1,RGB(0,0,255));    //蓝
// 	CPen Pen6(PS_SOLID,1,RGB(160,32,240)); //紫 
// 	CPen Pen7(PS_SOLID,1,RGB(135,206,235));//天蓝
// 	
// 	CPen* pens[8] = 
// 	{
// 		&Pen0,&Pen1 ,&Pen2,&Pen3,
// 		&Pen4,&Pen5 ,&Pen6,&Pen7
// 	};
//     systemPen = pdc->SelectObject(&penA);
// 	
// 	GobalData* g = GobalData::getGobalData();
// 	DataBuf* databuf = g->getDataBuf();   //数据缓存指针
// 	
// 	DataSaveFactory factory;
// 	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格
// 	
// 	int start = (screenPage - 1) * xMax / step;
// 	for(int i = startch; i <= endch; i++)
// 	{
// 		int dataLen = databuf->getdataLens(i);
//         int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);
// 		if(end <= 0)
// 			continue;
// 		org = pdc->SelectObject(pens[i-startch]);
// 		org->DeleteObject();
// 		int yn = yMax/2-restrainY*yMax/100;            //显示块基准
// 		end = end - end%blocklen;
// 		for(int j = start; j <= end; j ++)
// 		{
// 			int y[2] = {0,0}; int x[2] = {0,0};
// 			for ( int k = 0 ; k <= 1 ; k++ )
// 			{
// 				int ytemp = 0;
// 				style->GetWaveNum(databuf,i,j-k*blocklen,blocklen,timelapes,ytemp);  //取得显示值
// 				int x1 = ((j-k*blocklen) % (xMax / step)) * step;
// 				if(x1 == 0 && j != start)
// 					x1 = xMax;
// 				int xc = x1*kx/xMax + rect.left;
// 				y[k] = ytemp; x[k] = xc;
// 			}
// 			int yk = yMax/2-restrainY*yMax/100;
// //			int yalert1 = alertLine*yMax/(2*100)+yMax/2;
// //			int yalert2 = alertLine2*yMax/(2*100)+yMax/2;
// 		
// 			int ymax = 0 , ymin = 0, ydiffermax = 0, ydiffermin = 0;
// 			
// 			if ( yk+y[0] <= 2400 && yk+y[1] >= 2400)
// 			{
// 				aflag = 1;
// 			}
// 
// 			if ( yk+y[0] >= 1600 && yk+y[1] <= 1600)
// 			{
// 				bflag = 1;
// 			}	
// 			
// 			if (aflag == 1 && bflag ==1 && j>=100)
// 			{
// 				for (int t = 0; t <= 100 ;t++)
// 				{
// 					int yvalue = 0;
// 					style->GetWaveNum(databuf,i,j-t*blocklen,blocklen,timelapes,yvalue);
// 					if (yvalue > ymax)
// 					{
// 						ymax = yvalue;
// 					}
// 					else if (yvalue < ymin)
// 					{
// 						ymin = yvalue;
// 					}		
// 				}
// 				for ( int m = 100 ; m >= 0 ; m--)
// 				{
// 					int yv[3] = {0,0,0};
// 					for ( int k = m ; k >= m-2 ; k-- )
// 					{
// 						int ytemp = 0;
// 						style->GetWaveNum(databuf,i,j-k*blocklen,blocklen,timelapes,ytemp);  //取得显示值
// 						yv[m-k] = ytemp;					
// 					}
// 					int differ = yv[0] - 2*yv[1] + yv[2];
// 					if (differ > ydiffermax)
// 					{
// 						ydiffermax = differ;
// 					}
// 					else if (differ < ydiffermin)
// 					{
// 						ydiffermin = differ;
// 					}
// 				}	
// 				double phase = double(ymax-ymin-ydiffermax+ydiffermin)/double(ymax-ymin);
// 				double yc = double(phase*ky);
// 				pdc->MoveTo(x[0],rect.bottom);
// 				pdc->LineTo(x[0],rect.bottom-yc);   //画波形
// 				aflag = 0; bflag = 0;
// 			}
// 		}
// 	}

	blocklen = blockcompress;
	CWnd* pWnd = Wndshow;
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;

	CGdiObject* systemPen = NULL;
	CGdiObject* org = NULL;

	CPen penA(PS_SOLID,1,RGB(0,0,0));
	CBrush brush(RGB(255,0,0));

	systemPen = pdc->SelectObject(&penA);

	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf(); //数据缓存指针

	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格

	int start = (screenPage - 1) * xMax / step;

	int dataLen = databuf->getdataLens(startch);
	int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);
	if(end <= 0)
	return;
	end = end - end%blocklen;
    int miny = -2048;
	int xcoo=0,ycoo=0;
	for(int j = start; j <= end; j += blocklen)
	{
		int y = 0;
		
		style->GetAvgWaveNum(databuf,startch,endch-startch,j,blocklen,timelapes,y);//取得显示值
// 		switch(dataOpenMode)
// 		{
// 		case 0: 
// 			style->getShowWaveNum(databuf,startch,endch-startch,j,blocklen,timelapes,y);//取得显示值
// 			break;
// 		case 1:
// 			style->GetWaveNum(databuf,startch,endch-startch,j,blocklen,timelapes,y);//取得显示值
// 			break;
// 		default:
// 			break;
// 		}
		int yn = yMax/2-restrainY*yMax/100;
		if(half == TRUE)
		{
			yn = -restrainY*yMax/100;
		}
		
		int x1 = (j % (xMax / step)) * step;
		if(x1 == 0 && j != start)
			x1 = xMax;
		int xc = x1*kx/xMax + rect.left;
		int yc = rect.bottom - (-y+yn)*ky/yMax;
		if(half == TRUE)
		{
			yc = rect.bottom - 2*(y+yn)*ky/yMax;
		}
		if(j == start)
		{
			pdc->MoveTo(xc,yc);
		}
		else
		{
			pdc->LineTo(xc,yc);  //画波形
		}
		if((j>9000)&&(y>miny))
		{
// 			systemPen = pdc->SelectObject(&brush);
// 			pdc->Ellipse(xc-2,yc-2,xc+2,yc+2);
			xcoo= xc;
			ycoo = yc;
			miny  = y;
		}
	}
	systemPen = pdc->SelectObject(&brush);
 	pdc->Ellipse(xcoo-2,ycoo-2,xcoo+2,ycoo+2);

	org = pdc->SelectObject(systemPen);
	org->DeleteObject();

	pWnd->ReleaseDC(pdc);
		DeletePtr(style);
}

void CWaveShow::DrawPly(CDC *pdc, int startch, int endch, int blocklen)
{
	blocklen = blockcompress;
    CWnd* pWnd = Wndshow;
	CRect rect;
    pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	
	CGdiObject* systemPen = NULL;
	CGdiObject* org = NULL;
	
	CPen penA(PS_SOLID,1,RGB(128,0,0));
	CPen Pen0(PS_SOLID,1,RGB(160,82,45));  //综红
	CPen Pen1(PS_SOLID,1,RGB(255,97,0));   //橙
	CPen Pen2(PS_SOLID,1,RGB(255,200,0));  //黄
	CPen Pen3(PS_SOLID,1,RGB(0,255,0));	//绿
	CPen Pen4(PS_SOLID,1,RGB(8,46,84));    //靛青 
	CPen Pen5(PS_SOLID,1,RGB(0,0,255));    //蓝
	CPen Pen6(PS_SOLID,1,RGB(160,32,240)); //紫 
	CPen Pen7(PS_SOLID,1,RGB(135,206,235));//天蓝
	
	CPen* pens[8] = 
	{
		&Pen0,&Pen1 ,&Pen2,&Pen3,
		&Pen4,&Pen5 ,&Pen6,&Pen7
	};
    systemPen = pdc->SelectObject(&penA);
	
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();   //数据缓存指针
	
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格
	
	int start = (screenPage - 1) * xMax / step;
	for(int i = startch; i <= endch; i++)
	{
		int dataLen = databuf->getdataLens(i);
        int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);
		if(end <= 0)
			continue;
		org = pdc->SelectObject(pens[i-startch]);
		org->DeleteObject();
		
        int yn = yMax/2-restrainY*yMax/100;            //显示块基准
		if(half == TRUE)
		{
			yn = -restrainY*yMax/100;
		}
		
		end = end - end%blocklen;
		for(int j = start; j <= end; j += blocklen)
		{
			int y = 0;
// 			switch(dataOpenMode)
// 			{
// 			case 0: 
				style->getShowWaveNum(databuf,i,j,blocklen,timelapes,y);  //取得显示值
				if ((j<7500 && i<16) || ( j>dataLen-7500 && i<16))  /* (加厚)*/
				{
					y = 0;
				}
//				break;
// 			case 1:
// 				style->GetWaveNum(databuf,i,j,blocklen,timelapes,y);  //取得显示值
// 				break;
// 			default:
// 				break;
// 			}
			
			int x1 = (j % (xMax / step)) * step;
			if(x1 == 0 && j != start)
				x1 = xMax;
			int xc = x1*kx/xMax + rect.left;
			int yc = rect.bottom - (y+yn)*ky/yMax;
			if(half == TRUE)
			{
				yc = rect.bottom - 2*(y+yn)*ky/yMax;
			}

				if(j == start)
				{
					pdc->MoveTo(xc,yc);
				}
				else
				{
					pdc->LineTo(xc,yc);   //画波形
				}
		}
	}
	org = pdc->SelectObject(systemPen);
	org->DeleteObject();

	pWnd->ReleaseDC(pdc);
	DeletePtr(style);
}


void CWaveShow::DrawDifference(CDC *pdc, int startch, int endch, int blocklen, int dataOpenMode)
{
	blocklen = blockcompress;
	CWnd* pWnd = Wndshow;
	CRect rect;
	pWnd->GetClientRect(&rect);
	pWnd->UpdateWindow();
	int kx = rect.right - rect.left;
	int ky = rect.bottom - rect.top;
	
	CGdiObject* systemPen = NULL;
	CGdiObject* org = NULL;
	
	CPen penA(PS_SOLID,1,RGB(128,0,0));
	CPen Pen0(PS_SOLID,1,RGB(160,82,45));  //综红
	CPen Pen1(PS_SOLID,1,RGB(255,97,0));   //橙
	CPen Pen2(PS_SOLID,1,RGB(255,200,0));  //黄
	CPen Pen3(PS_SOLID,1,RGB(0,255,0));	//绿
	CPen Pen4(PS_SOLID,1,RGB(8,46,84));    //靛青 
	CPen Pen5(PS_SOLID,1,RGB(0,0,255));    //蓝
	CPen Pen6(PS_SOLID,1,RGB(160,32,240)); //紫 
	CPen Pen7(PS_SOLID,1,RGB(135,206,235));//天蓝

	CPen* pens[8] = 
	{
		&Pen0,&Pen1 ,&Pen2,&Pen3,
		&Pen4,&Pen5 ,&Pen6,&Pen7
	};
	GobalData* g = GobalData::getGobalData();
	DataBuf* databuf = g->getDataBuf();   //数据缓存指针
	AUTOSET& set = g->getAutoSet();
	float speed =set.speed;
	DataSaveFactory factory;
	DataSaveStyle* style = factory.getDataSaveStyle(g->getSuffix());  //获得显示风格
	systemPen = pdc->SelectObject(&penA);
	int start = (screenPage - 1) * xMax / step;



	for(int i = startch; i <= endch; i++)
	{
		int dataLen = databuf->getdataLens(i);	
        	int end =  (start + xMax / step) > (dataLen-blocklen) ?  (dataLen-blocklen) : (start + xMax / step);
		if(end <= 0)
			continue;
		if( i > 71 )		
			org = pdc->SelectObject(pens[i%8]);
		else if (i>=4) 
			org = pdc->SelectObject(pens[(i-4)%8]);
		else
			org = pdc->SelectObject(pens[i%8]);

		int yn = yMax/2-restrainY*yMax/100;            //显示块基准
		if(half == TRUE)
		{
			yn = -restrainY*yMax/100;
		}
		
		end = end - end%blocklen;
		for(int j = start; j <= end; j += blocklen)
		{
			int y = 0;
			switch(dataOpenMode)
			{
			case 0: 
			case 1:				
				style->GetWaveNum(databuf,i,j,blocklen,timelapes,y);		
				break;
			default:
				break;
			}
			
			if (y<alertLine2*2048/(100)&& alertLine2 !=0 ) 
			{
				y=y/3;
			}

			if(i<72)
				{
					float alerty1_l = getHoriAlertyParL();
					float alerty1_h = getHoriAlertyParH();

					if (y>alerty1_l && y<alerty1_h)
					{
						y = (int)(alerty1 +0.3*y);
						if (y>2000)
							{
								y=2000;
							}
					}
				}
			else
				{
					int alerty2_l = getVertAlertyParL();
					int alerty2_h = getVertAlertyParH();
					if (y>alerty2_l && y<alerty2_h)
					{
						y =(int) (alerty2 +0.3*y);
						if (y>2000)
							{
								y=2000;
							}
					}
				}

			int x1 = (j % (xMax / step)) * step;
			if(x1 == 0 && j != start)
				x1 = xMax;
			int xc = x1*kx/xMax + rect.left;
			
			if( showLengthRule == TRUE && i == 104  )
			{
				CString ruleValue;
				if(( j%3000) == 0 && j >0 ){
					ruleValue.Format(_T("%.1f"),j*speed);
					pdc->TextOut(xc,rect.top+rect.bottom/25,ruleValue);
				}		
			}	
		 int yc = rect.bottom - (y+yn)*ky/yMax;
			if(half == TRUE)
			{
				yc = rect.bottom - 2*(y+yn)*ky/yMax;
			}
			if(j == start)
			{
				pdc->MoveTo(xc,yc);
			}
			else
			{
				pdc->LineTo(xc,yc);   //画波形
			}

		}
	}
	org = pdc->SelectObject(systemPen);
	org->DeleteObject();
	
	pWnd->ReleaseDC(pdc);
	DeletePtr(style);
}

void CWaveShow::setTimeLapes(short i)
{
	timelapes = i;
}

short CWaveShow::getTimeLapes()
{
	return timelapes;
}
void CWaveShow::ReadlvboToFile(CString strFileName)
{
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeRead)) 
	{
	//	AfxMessageBox("Read lvbo file error!");
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
