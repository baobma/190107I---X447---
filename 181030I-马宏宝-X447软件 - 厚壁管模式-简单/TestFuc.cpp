#include "stdafx.h"
#include "TestFuc.h"

void FloorMapSet(CWnd* pWnd,CDC* pdc, int ex, int ey)//²¨ÐÎ»­Í¼Ó³Éä
{
	pdc->SetMapMode(MM_ANISOTROPIC);
	pdc->SetWindowExt(ex,ey);
	CRect rect;
	pWnd->GetClientRect(rect);
	pdc->SetViewportExt(rect.right,-rect.bottom);
	pdc->SetViewportOrg(0,rect.bottom);
}
