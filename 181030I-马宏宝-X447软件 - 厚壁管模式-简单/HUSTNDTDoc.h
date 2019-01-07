// HUSTNDTDoc.h : interface of the CHUSTNDTDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUSTNDTDOC_H__BFBD365C_4DFD_4083_930E_10C7A4541700__INCLUDED_)
#define AFX_HUSTNDTDOC_H__BFBD365C_4DFD_4083_930E_10C7A4541700__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHUSTNDTDoc : public CDocument
{
protected: // create from serialization only
	CHUSTNDTDoc();
	DECLARE_DYNCREATE(CHUSTNDTDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHUSTNDTDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHUSTNDTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHUSTNDTDoc)
	afx_msg void OnSet();
	afx_msg void OnMIAN();
	afx_msg void OnParSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUSTNDTDOC_H__BFBD365C_4DFD_4083_930E_10C7A4541700__INCLUDED_)
