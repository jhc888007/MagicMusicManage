#include "stdafx.h"
#include "Punctuation.h"



CString PunctuationSimplify( CString csPunctuation )
{
	CString csResult;
	int nLen = csPunctuation.GetLength();
	int nCount;
	int nResult;
	TCHAR *ptOrigin = new TCHAR[nLen+1];

	csResult.Format( _T("") );
	lstrcpy( ptOrigin, csPunctuation.GetBuffer(nLen) );

	for( nCount = 0; nCount < nLen + 1; nCount++ )
	{
		nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
		if( nResult > 100 || nResult <= 0 )
			csResult.AppendFormat( _T("%c"), *( ptOrigin + nCount ) );
	}

	if( csResult.Compare( _T("") ) == 0 )
		return ( _T(".") );

	csPunctuation.ReleaseBuffer();

	return csResult;
}

CString PunctuationComplicate( CString csPunctuation )
{
	CString csResult;
	int nLen = csPunctuation.GetLength();
	int nCount;
	int nStart;
	int nResult;
	int nLastResult;
	TCHAR *ptOrigin = new TCHAR[nLen+1];
	
	csResult.Format( _T("") );
	lstrcpy( ptOrigin, csPunctuation.GetBuffer(nLen) );

	nStart = 0;
	nLastResult = 0;
	for( nCount = 0; nCount < nLen + 1; nCount++ )
	{
		nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
		//\u7A7A\u683C\u3001\u70B9\u6216\u4E0B\u5212\u7EBF\u7B49\u8FDE\u63A5\u7EBF
		if( nResult < 100 )
			continue;
		//\u4E0E\u524D\u9762\u5B57\u6BCD\u76F8\u63A5\uFF0C\u4E0D\u4E0E\u540E\u9762\u5B57\u6BCD\u76F8\u63A5\u7684\u7B26\u53F7
		else if( nResult < 200 )
		{
			//\u5982\u679C\u524D\u9762\u7B26\u53F7\u662F\u524D\u540E\u4E0D\u76F8\u63A5\u7B26\u53F7
			if( nLastResult > 300 && nLastResult < 400 )
				csResult.AppendFormat(_T(".%c"), *(ptOrigin+nCount) );
			else
				csResult.AppendFormat(_T("%c"), *(ptOrigin+nCount) );
			nLastResult = nResult;
		}
		//\u4E0E\u540E\u9762\u5B57\u6BCD\u76F8\u63A5\uFF0C\u4E0D\u4E0E\u524D\u9762\u5B57\u6BCD\u76F8\u63A5\u7684\u7B26\u53F7
		else if( nResult < 300 )
		{
			//\u5982\u679C\u524D\u9762\u5B57\u6BCD\u4E5F\u662F\u76F8\u540C\u7C7B\u578B\u7684\u7B26\u53F7
			if( nLastResult > 200 && nLastResult < 300 )
				csResult.AppendFormat(_T("%c"), *(ptOrigin+nCount) );
			else
				csResult.AppendFormat(_T(".%c"), *(ptOrigin+nCount) );
			nLastResult = nResult;
		}
		//\u4E0E\u524D\u540E\u5B57\u6BCD\u90FD\u4E0D\u76F8\u63A5\u7684\u7B26\u53F7
		else if( nResult < 400 )
		{
			csResult.AppendFormat(_T(".%c"), *(ptOrigin+nCount) );
			nLastResult = nResult;
		}
		else
			break;
	}

	if( nLastResult > 300 || nLastResult < 200 )
		csResult.AppendFormat(_T("."));

	csPunctuation.ReleaseBuffer();

	return csResult;
}

CString PunctuationWordGetNext( TCHAR *ptChar, int *pNum, int *pFlag )
{
	CString csResult;
	int nResult;

	*pNum = 0;
	csResult.Format( _T("") );
	nResult = PunctuationCheckType( *ptChar );
	
	//\u7B26\u53F7
	if( nResult > 0 )
	{
		*pFlag = 1;
		while( nResult > 0 && nResult < 500 )
		{
			csResult.AppendFormat( _T("%c"), *ptChar );
			(*pNum)++;
			ptChar++;
			nResult = PunctuationCheckType( *ptChar );
		}
	}
	//\u5355\u8BCD
	else
	{
		*pFlag = 2;
		while( nResult <= 0  )
		{
			csResult.AppendFormat( _T("%c"), *ptChar );
			(*pNum)++;
			ptChar++;
			nResult = PunctuationCheckType( *ptChar );
		}
	}
	//\u672B\u5C3E\u7B26\u53F7
	if( nResult > 500 && *pFlag == 1 )
		*pFlag = -1;
	//\u672B\u5C3E\u5355\u8BCD
	if( nResult > 500 && *pFlag == 2 )
		*pFlag = -2;
	
	return csResult;
}

int PunctuationGetDashPosition( TCHAR *ptChar )
{
	int nCount;

	for( nCount = 0; *( ptChar + nCount ) != 0; nCount++ )
		if( PunctuationCheckType( *( ptChar + nCount ) ) == 302 )
			break;

	if( *( ptChar + nCount ) == 0 )
		return 0;

	return nCount;
}

CString PunctuationDeleteBlankBracket( CString csName )
{
	CString csResult;
	int nLen = csName.GetLength();
	int nCount;
	int nResult;
	int nNextResult;
	TCHAR *ptOrigin = new TCHAR[nLen+1];

	csResult.Format( _T("") );
	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );

	nNextResult = PunctuationCheckType( *ptOrigin );
	for( nCount = 0; nCount < nLen; nCount++ )
	{
		nResult = nNextResult;
		nNextResult = PunctuationCheckType( *( ptOrigin + nCount + 1 ) );
		if( ( nResult == 201 && nNextResult == 101 )
			|| ( nResult == 202 && nNextResult == 102 ) 
			|| ( nResult == 203 && nNextResult == 103 ) )
		{
			nCount++;
			nNextResult = PunctuationCheckType( *( ptOrigin + nCount + 1 ) );
		}
		else
			csResult.AppendFormat( _T("%c"), *( ptOrigin + nCount ) );
	}

	if( nCount == nLen )
		csResult.AppendFormat( _T("%c"), *( ptOrigin + nCount ) );

	csName.ReleaseBuffer();

	return csResult;
}

CString PunctuationDeleteHead( CString csName )
{
	CString csResult;
	int nLen = csName.GetLength();
	int nCount;
	int nResult;
	TCHAR *ptOrigin = new TCHAR[nLen+1];
	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );

	for( nCount = 0; nCount < nLen + 1; nCount++ )
	{
		nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
		if( nResult <= 0 )
			break;
	}

	csResult.Format( _T("%s"), ptOrigin + nCount );

	csName.ReleaseBuffer();

	return csResult;
}

CString PunctuationDeleteSingleBracket( CString csName )
{
	CString csResult;
	int nLen = csName.GetLength();
	int nCount;
	int nResult;
	int nNum1;
	int nNum2;
	int nNum3;
	TCHAR *ptOrigin = new TCHAR[nLen+1];
	
	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );

	nNum1 = 0;
	nNum2 = 0;
	nNum3 = 0;
	for( nCount = 0; nCount < nLen + 1; nCount++ )
	{
		nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
		if( nResult == 201 )
			nNum1++;
		else if( nResult == 202 )
			nNum2++;
		else if( nResult == 203 )
			nNum3++;
		else if( nResult == 101 )
		{
			if( nNum1 > 0 )
				nNum1--;
			else
				*( ptOrigin + nCount ) = '_';
		}
		else if( nResult == 102 )
		{
			if( nNum2 > 0 )
				nNum2--;
			else
				*( ptOrigin + nCount ) = '_';
		}
		else if( nResult == 103 )
		{
			if( nNum3 > 0 )
				nNum3--;
			else
				*( ptOrigin + nCount ) = '_';
		}
	}

	nNum1 = 0;
	nNum2 = 0;
	nNum3 = 0;
	for( nCount = nLen; nCount >= 0; nCount-- )
	{
		nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
		if( nResult == 101 )
			nNum1++;
		else if( nResult == 102 )
			nNum2++;
		else if( nResult == 103 )
			nNum3++;
		else if( nResult == 201 )
		{
			if( nNum1 > 0 )
				nNum1--;
			else
				*( ptOrigin + nCount ) = '_';
		}
		else if( nResult == 202 )
		{
			if( nNum2 > 0 )
				nNum2--;
			else
				*( ptOrigin + nCount ) = '_';
		}
		else if( nResult == 203 )
		{
			if( nNum3 > 0 )
				nNum3--;
			else
				*( ptOrigin + nCount ) = '_';
		}
	}

	csResult.Format( _T("") );
	nResult = PunctuationCheckType( *( ptOrigin ) );
	nCount = 0;
	while( nResult < 500 )
	{
		if( nResult != 2 )
			csResult.AppendFormat( _T("%c"), *( ptOrigin + nCount ) );
		nCount++;
		nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
	}

	csName.ReleaseBuffer();

	return csResult;
}

CString PunctuationDeleteFirstDot( CString csName )
{
	CString csResult;
	int nLen = csName.GetLength();
	TCHAR *ptOrigin = new TCHAR[nLen+1];
	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );

	if( PunctuationCheckType( *( ptOrigin ) ) == 1 )
		ptOrigin++;
	csResult.Format( _T("%s"), ptOrigin );

	csName.ReleaseBuffer();

	return csResult;
}

CString PunctuationDeleteLastDot( CString csName )
{
	CString csResult;
	int nLen = csName.GetLength();
	TCHAR *ptOrigin = new TCHAR[nLen+1];
	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );

	if( PunctuationCheckType( *( ptOrigin + nLen - 1 ) == 1 ) )
		*( ptOrigin + nLen - 1 ) = 0;
	csResult.Format( _T("%s"), ptOrigin );

	csName.ReleaseBuffer();

	return csResult;
}

CString PunctuationDeleteSequence( CString csName )
{
	CString csResult;
	int nLen = csName.GetLength();
	int nCount;
	int nContinue;
	int nResult;
	TCHAR *ptTemp = new TCHAR[nLen+1];

	if( nLen == 0 ) return _T("");
	lstrcpy( ptTemp, csName.GetBuffer(nLen) );
	csResult.Format( _T("") );

	nCount = 0;
	nContinue = 0;
	nResult = PunctuationCheckType( *( ptTemp ) );
	if( nResult == 0 )
	{
		for( nCount = 1; nCount < nLen + 1; nCount++ )
		{
			nResult = PunctuationCheckType( *( ptTemp + nCount ) );
			if( nResult != 0 )
				nContinue = 1;
			if( nContinue == 1 )
				if( nResult <= 0 || ( nResult > 200 ) && ( nResult < 300 ) )
					break;
		}
	}

	csResult.Format( _T("%s"), ptTemp + nCount );
	csName.ReleaseBuffer();
	return csResult;
}
