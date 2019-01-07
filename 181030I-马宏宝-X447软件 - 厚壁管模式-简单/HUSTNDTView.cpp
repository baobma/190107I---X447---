// HUSTNDTView.cpp : implementation of the CHUSTNDTView class
//

#include "stdafx.h"
#include "HUSTNDT.h"

#include "HUSTNDTDoc.h"
#include "HUSTNDTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTView

IMPLEMENT_DYNCREATE(CHUSTNDTView, CView)

BEGIN_MESSAGE_MAP(CHUSTNDTView, CView)
	//{{AFX_MSG_MAP(CHUSTNDTView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTView construction/destruction

CHUSTNDTView::CHUSTNDTView()
{
	// TODO: add construction code here

}

CHUSTNDTView::~CHUSTNDTView()
{
}

BOOL CHUSTNDTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTView drawing

void CHUSTNDTView::OnDraw(CDC* pDC)
{
	CHUSTNDTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTView diagnostics

#ifdef _DEBUG
void CHUSTNDTView::AssertValid() const
{
	CView::AssertValid();
}

void CHUSTNDTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHUSTNDTDoc* CHUSTNDTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHUSTNDTDoc)));
	return (CHUSTNDTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTView message handlers

BOOL CHUSTNDTView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_BACKGROUND);
	
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	
	dcCompatible.SelectObject(&bitmap);

	CRect rect;
	GetClientRect(&rect);
//	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	return TRUE;
// 	return CView::OnEraseBkgnd(pDC);
}
