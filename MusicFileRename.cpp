\uFEFF#include "stdafx.h"
#include "Word.h"
#include "WordCheck.h"
#include "PunctuationDeal.h"



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
		//\u5904\u7406\u5355\u8BCD
		if( nFlag == 2 || nFlag == -2 )
			csResult.AppendFormat( csWord );
		//\u5904\u7406\u7B26\u53F7
		else if( nFlag == 1 )
		{
			csWord = PunctuationSimplify( csWord );
			csResult.AppendFormat( csWord );
		}
		//\u5904\u7406\u672B\u5C3E\u7B26\u53F7
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
		//\u5904\u7406\u975E\u540E\u7F00\u5355\u8BCD
		if( nFlag == 2 )
		{
			if( WordCheckSpecial( csWord ) == 1 )
				csWord = WordCap( csWord );
			else
				csWord = WordFirstCap( csWord );
			csResult.AppendFormat( csWord );
		}
		//\u5904\u7406\u7B26\u53F7
		else if( nFlag == 1 )
		{
			csWord = PunctuationComplicate( csWord );
			csResult.AppendFormat( csWord );
		}
		//\u5904\u7406\u540E\u7F00
		else if( nFlag == -2 )
		{
			csWord = WordLower( csWord );
			csResult.AppendFormat( csWord );
		}
		//\u5904\u7406\u672B\u5C3E\u7B26\u53F7
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
	
	csResult = MusicFileSimplify( csName );
	csResult = MusicFileBeautify( csResult );
	csResult = MusicFileComplicate( csResult );

	return csResult;
}


