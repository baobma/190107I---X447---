// HUSTNDTDoc.cpp : implementation of the CHUSTNDTDoc class
//

#include "stdafx.h"
#include "HUSTNDT.h"
#include "IntialSetDlg.h"

#include "HUSTNDTDoc.h"
#include "ardSet.h"
#include "ParSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "MainDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTDoc

IMPLEMENT_DYNCREATE(CHUSTNDTDoc, CDocument)

BEGIN_MESSAGE_MAP(CHUSTNDTDoc, CDocument)
	//{{AFX_MSG_MAP(CHUSTNDTDoc)
	ON_COMMAND(INTIAL_SET, OnSet)
	ON_COMMAND(MIAN, OnMIAN)
	ON_COMMAND(PAR_SET, OnParSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTDoc construction/destruction

CHUSTNDTDoc::CHUSTNDTDoc()
{
	// TODO: add one-time construction code here

}

CHUSTNDTDoc::~CHUSTNDTDoc()
{
}

BOOL CHUSTNDTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTDoc serialization

void CHUSTNDTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTDoc diagnostics

#ifdef _DEBUG
void CHUSTNDTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHUSTNDTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTDoc commands

/*
 *	打开初始化对话框
 */
void CHUSTNDTDoc::OnSet() 
{
	IntialSetDlg dlg;
	dlg.DoModal();
}

/*
 *	打开采集分析主对话框
 */
void CHUSTNDTDoc::OnMIAN() 
{
//	::ShowWindow(,SW_SHOWMINIMIZED);
	MainDlg dlg;
	dlg.DoModal();
}

/*
 *	打开参数设置对话框
 */
void CHUSTNDTDoc::OnParSet() 
{
//	PARSET dlg;
//	dlg.analysis = FALSE;  //设置状态
//	dlg.DoModal();
}
