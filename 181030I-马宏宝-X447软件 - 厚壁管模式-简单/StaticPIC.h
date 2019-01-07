#if !defined(AFX_STATICPIC_H__0F8C62F5_C63F_49B8_B6AD_092992D61120__INCLUDED_)
#define AFX_STATICPIC_H__0F8C62F5_C63F_49B8_B6AD_092992D61120__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticPIC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticPIC window

class CStaticPIC : public CStatic
{
// Construction
public:
	CStaticPIC();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticPIC)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticPIC();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticPIC)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICPIC_H__0F8C62F5_C63F_49B8_B6AD_092992D61120__INCLUDED_)
