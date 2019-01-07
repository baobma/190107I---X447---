// SRoomSample.h: interface for the SRoomSample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SROOMSAMPLE_H__4EE51A7E_66BF_4A4D_B704_9A8E4B2D19D9__INCLUDED_)
#define AFX_SROOMSAMPLE_H__4EE51A7E_66BF_4A4D_B704_9A8E4B2D19D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SimpleDataSave.h"

/*
 *	Î´Íê³É
 */
class SRoomSample : public SimpleDataSave  
{
public:
	BOOL getDateFromCard();
	SRoomSample();
	virtual ~SRoomSample();
};

#endif // !defined(AFX_SROOMSAMPLE_H__4EE51A7E_66BF_4A4D_B704_9A8E4B2D19D9__INCLUDED_)
