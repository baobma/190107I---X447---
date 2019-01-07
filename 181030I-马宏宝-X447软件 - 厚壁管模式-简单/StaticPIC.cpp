// StaticPIC.cpp : implementation file
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "StaticPIC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticPIC

CStaticPIC::CStaticPIC()
{
}

CStaticPIC::~CStaticPIC()
{
}


BEGIN_MESSAGE_MAP(CStaticPIC, CStatic)
	//{{AFX_MSG_MAP(CStaticPIC)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticPIC message handlers

BOOL CStaticPIC::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
	
	//return CStatic::OnEraseBkgnd(pDC);
}
