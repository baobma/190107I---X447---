// TestSampleControl.h: interface for the TestSampleControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSAMPLECONTROL_H__B3E3DFCC_D50A_4F72_9CA2_4D1CF52F65FE__INCLUDED_)
#define AFX_TESTSAMPLECONTROL_H__B3E3DFCC_D50A_4F72_9CA2_4D1CF52F65FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RbhUsb20.h"

class TestSampleControl  
{
public:
	static CSampleCard* cardPtr;
	TestSampleControl();
	virtual ~TestSampleControl();

};

#endif // !defined(AFX_TESTSAMPLECONTROL_H__B3E3DFCC_D50A_4F72_9CA2_4D1CF52F65FE__INCLUDED_)
