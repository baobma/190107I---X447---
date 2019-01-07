// DataSaveFactory.h: interface for the DataSaveFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATASAVEFACTORY_H__74E6CF68_7B14_4A04_8770_02BB24521468__INCLUDED_)
#define AFX_DATASAVEFACTORY_H__74E6CF68_7B14_4A04_8770_02BB24521468__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DataSaveStyle.h"
#include "enmuHead.h"

/*
 *	���ݱ����ʽ������
 */
class DataSaveFactory  
{
public:
	/*
	 *	����������
	 */
	DataSaveStyle* getDataSaveStyle(char* suffix);
	DataSaveStyle* getDataSaveStyle(SaveStyle s);
	DataSaveFactory();
	virtual ~DataSaveFactory();

};

#endif // !defined(AFX_DATASAVEFACTORY_H__74E6CF68_7B14_4A04_8770_02BB24521468__INCLUDED_)
