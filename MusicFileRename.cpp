#include "stdafx.h"
#include "Word.h"
#include "WordCheck.h"
#include "PunctuationDeal.h"
#include "CutRename.h"



CString MusicFileSimplify( CString csName )
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
			csResult.AppendFormat( csWord );
		//处理符号
		else if( nFlag == 1 )
		{
			csWord = PunctuationSimplify( csWord );
			csResult.AppendFormat( csWord );
		}
		//处理末尾符号
		else
			break;
		csWord = PunctuationWordGetNext( ptOrigin + nCount, &nNum, &nFlag );
		nCount += nNum;
	}

	csName.ReleaseBuffer();

	return csResult;
}

CString MusicFileBeautify( CString csName )
{
	CString csResult;
	csResult = PunctuationDeleteBlankBracket( csName );
	csResult = PunctuationDeleteHead( csResult );
	csResult = PunctuationDeleteSingleBracket( csResult );
	return csResult;
}

CString MusicFileComplicate( CString csName )
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
		//处理非后缀单词
		if( nFlag == 2 )
		{
			if( WordCheckSpecial( csWord ) == 1 )
				csWord = WordCap( csWord );
			else
				csWord = WordFirstCap( csWord );
			csResult.AppendFormat( csWord );
		}
		//处理符号
		else if( nFlag == 1 )
		{
			csWord = PunctuationComplicate( csWord );
			csResult.AppendFormat( csWord );
		}
		//处理后缀
		else if( nFlag == -2 )
		{
			csWord = WordLower( csWord );
			csResult.AppendFormat( csWord );
		}
		//处理末尾符号
		else
			break;
		csWord = PunctuationWordGetNext( ptOrigin + nCount, &nNum, &nFlag );
		nCount += nNum;
	}

	csName.ReleaseBuffer();

	return csResult;
}

CString MusicFileRename( CString csName )
{
	CString csResult;
	
	csResult = CutRename( csName );
	csResult = MusicFileSimplify( csResult );
	csResult = MusicFileBeautify( csResult );
	csResult = MusicFileComplicate( csResult );

	return csResult;
}


