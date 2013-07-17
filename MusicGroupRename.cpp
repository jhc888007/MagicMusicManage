#include "stdafx.h"
#include "Word.h"
#include "WordCheck.h"
#include "PunctuationDeal.h"
#include "CutRename.h"



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
		//处理单词
		if( nFlag == 2 || nFlag == -2 )
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
			csWord = PunctuationSimplify( csWord );
			csResult.AppendFormat( csWord );
		}
		//处理末尾符号
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
	
	//如果未指定艺术家
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

	//读取后面单词
	csWord = PunctuationWordGetNext( ptOrigin, &nNum, &nFlag );
	nCount = 0;
	csResult.Format( _T("") );

	while( csWord.Compare( _T("") ) != 0 )
	{
		//处理单词
		if( nFlag == 2 || nFlag == -2 )
		{
			//如果是年代
			if( nCount > 0 && WordCheckYear( ptOrigin + nCount - 1 ) == 1 )
			{
				csYear = csWord;
			}
			//如果是唱片类型
			else if( WordCheckType( csWord ) == 1 )
			{
				csType = csWord;
			}
			//如果是歌曲格式
			else if( WordCheckMusic( csWord ) == 1 )
			{
				csSuffix = WordCap( csWord );
			}
			//其他
			else
			{
				csResult.AppendFormat( csWord );
			}
		}
		//处理符号
		else if( nFlag == 1 )
			csResult.AppendFormat( csWord );
		//处理末尾符号
		else
		{
			csResult.AppendFormat( csWord );
			break;
		}
		nCount += nNum;
		csWord = PunctuationWordGetNext( ptOrigin + nCount, &nNum, &nFlag );
	}

	//处理括号
	csResult = PunctuationDeleteBlankBracket( csResult );
	csResult = PunctuationDeleteHead( csResult );
	csWord = PunctuationDeleteSingleBracket( csResult );

	//整体结构
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
		csResult.AppendFormat( _T("专辑"));
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
		//处理单词
		if( nFlag == 2 || nFlag == -2 )
			csResult.AppendFormat( csWord );
		//处理符号
		else if( nFlag == 1 )
		{
			csWord = PunctuationComplicate( csWord );
			csResult.AppendFormat( csWord );
		}
		//处理末尾符号
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
	
	csResult = CutRename( csName );
	csResult = MusicGroupSimplify( csResult );
	csResult = MusicGroupBeautify( csResult, csArtist, nArtistLock, csType, csSuffix );
	csResult = MusicGroupComplicate( csResult );

	return csResult;
}