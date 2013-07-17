#include "stdafx.h"
#include "Word.h"
#include "PunctuationDeal.h"



extern CString g_delete;


CString CutRename( CString csName )
{
	CString csResult;
	CString csWord;
	int nLen = csName.GetLength();
	int nCount;
	int nNum;
	int nFlag;
	TCHAR *ptOrigin = new TCHAR[nLen+1];

	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );
	csWord = PunctuationWordGetNext( ptOrigin, &nNum, &nFlag );
	nCount = nNum;
	csResult.Format( _T("") );

	while( csWord.Compare( _T("") ) != 0 )
	{
		//处理单词
		if( nFlag == 2 || nFlag == -2 )
		{
			if( WordCompare( csWord, g_delete ) == 0 )
				csResult.AppendFormat( csWord );
		}
		//处理符号
		else
		{
			csResult.AppendFormat( csWord );
		}
		csWord = PunctuationWordGetNext( ptOrigin + nCount, &nNum, &nFlag );
		nCount += nNum;
	}

	csName.ReleaseBuffer();

	return csResult;
}