#include "stdafx.h"
#include "Word.h"
#include "WordCheck.h"
#include "PunctuationDeal.h"



CString MusicGroupSimplify( CString csName )
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
		{
			csWord = WordFirstCap( csWord );
			csResult.AppendFormat( csWord );
		}
		//\u5904\u7406\u7B26\u53F7
		else if( nFlag == 1 )
		{
			csWord = PunctuationSimplify( csWord );
			csResult.AppendFormat( csWord );
		}
		//\u5904\u7406\u672B\u5C3E\u7B26\u53F7
		else
		{
			csWord = PunctuationSimplify( csWord );
			csResult.AppendFormat( csWord );
			break;
		}
		csWord = PunctuationWordGetNext( ptOrigin + nCount, &nNum, &nFlag );
		nCount += nNum;
	}

	csName.ReleaseBuffer();

	return csResult;
}

CString MusicGroupBeautify( CString csName, CString csArtist, int nArtistLock, CString csType, CString csSuffix )
{
	CString csResult;
	CString csWord;
	CString csYear;
	int nLen = csName.GetLength();
	int nCount;
	int nNum;
	int nFlag;
	TCHAR *ptOrigin = new TCHAR[nLen+1];

	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );
	csResult.Format( _T("") );
	
	//\u5982\u679C\u672A\u6307\u5B9A\u827A\u672F\u5BB6
	if( csArtist.Compare( _T("") ) == 0 || nArtistLock == 0 )
	{
		nCount = PunctuationGetDashPosition( ptOrigin );
		if( nCount != 0 )
		{
			*( ptOrigin + nCount ) = 0;
			csArtist.Format( _T("%s"), ptOrigin );
			ptOrigin += nCount + 1;
		}
	}

	//\u8BFB\u53D6\u540E\u9762\u5355\u8BCD
	csWord = PunctuationWordGetNext( ptOrigin, &nNum, &nFlag );
	nCount = 0;
	csResult.Format( _T("") );

	while( csWord.Compare( _T("") ) != 0 )
	{
		//\u5904\u7406\u5355\u8BCD
		if( nFlag == 2 || nFlag == -2 )
		{
			//\u5982\u679C\u662F\u5E74\u4EE3
			if( nCount > 0 && WordCheckYear( ptOrigin + nCount - 1 ) == 1 )
			{
				csYear = csWord;
			}
			//\u5982\u679C\u662F\u5531\u7247\u7C7B\u578B
			else if( WordCheckType( csWord ) == 1 )
			{
				csType = csWord;
			}
			//\u5982\u679C\u662F\u6B4C\u66F2\u683C\u5F0F
			else if( WordCheckMusic( csWord ) == 1 )
			{
				csSuffix = WordCap( csWord );
			}
			//\u5176\u4ED6
			else
			{
				csResult.AppendFormat( csWord );
			}
		}
		//\u5904\u7406\u7B26\u53F7
		else if( nFlag == 1 )
			csResult.AppendFormat( csWord );
		//\u5904\u7406\u672B\u5C3E\u7B26\u53F7
		else
		{
			csResult.AppendFormat( csWord );
			break;
		}
		nCount += nNum;
		csWord = PunctuationWordGetNext( ptOrigin + nCount, &nNum, &nFlag );
	}

	//\u5904\u7406\u62EC\u53F7
	csResult = PunctuationDeleteBlankBracket( csResult );
	csResult = PunctuationDeleteHead( csResult );
	csWord = PunctuationDeleteSingleBracket( csResult );

	//\u6574\u4F53\u7ED3\u6784
	csResult.Format( _T("") );
	if( csArtist.Compare( _T("") ) != 0 )
		csResult.AppendFormat( _T("%s-"), csArtist );
	csResult.AppendFormat( _T("[%s"), csWord );
	if( csYear.Compare( _T("") ) != 0 )
		csResult.AppendFormat( _T("(%s)]"), csYear );
	else
		csResult.AppendFormat( _T("]"), csYear );
	if( csType.Compare( _T("") ) != 0 )
		csResult.AppendFormat( _T("%s"), csType );
	else
		csResult.AppendFormat( _T("\u4E13\u8F91"));
	csResult.AppendFormat( _T("(%s)"), csSuffix );

	csName.ReleaseBuffer();

	return csResult;
}

CString MusicGroupComplicate( CString csName )
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
			csWord = PunctuationComplicate( csWord );
			csResult.AppendFormat( csWord );
		}
		//\u5904\u7406\u672B\u5C3E\u7B26\u53F7
		else
		{
			csWord = PunctuationComplicate( csWord );
			csWord = PunctuationDeleteLastDot( csWord );
			csResult.AppendFormat( csWord );
			break;
		}
		csWord = PunctuationWordGetNext( ptOrigin + nCount, &nNum, &nFlag );
		nCount += nNum;
	}

	csResult = PunctuationDeleteFirstDot( csResult );

	csName.ReleaseBuffer();

	return csResult;
}

CString MusicGroupRename( CString csName, CString csArtist, int nArtistLock, CString csType, CString csSuffix )
{
	CString csResult;
	
	csResult = MusicGroupSimplify( csName );
	csResult = MusicGroupBeautify( csResult, csArtist, nArtistLock, csType, csSuffix );
	csResult = MusicGroupComplicate( csResult );

	return csResult;
}