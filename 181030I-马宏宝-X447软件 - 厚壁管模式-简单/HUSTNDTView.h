// HUSTNDTView.h : interface of the CHUSTNDTView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUSTNDTVIEW_H__EEB27203_28E1_413D_AD38_3E66D293ACDF__INCLUDED_)
#define AFX_HUSTNDTVIEW_H__EEB27203_28E1_413D_AD38_3E66D293ACDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHUSTNDTView : public CView
{
protected: // create from serialization only
	CHUSTNDTView();
	DECLARE_DYNCREATE(CHUSTNDTView)

// Attributes
public:
	CHUSTNDTDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHUSTNDTView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHUSTNDTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHUSTNDTView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HUSTNDTView.cpp
inline CHUSTNDTDoc* CHUSTNDTView::GetDocument()
   { return (CHUSTNDTDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUSTNDTVIEW_H__EEB27203_28E1_413D_AD38_3E66D293ACDF__INCLUDED_)
