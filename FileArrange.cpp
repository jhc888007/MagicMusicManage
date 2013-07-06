#include "stdafx.h"
#include "Punctuation.h"



CString FileArrangeGetSuffix( CString csName )
{
	CString csResult;
	int nResult;
	int nCount;
	int nLen = csName.GetLength();
	TCHAR *ptOrigin = new TCHAR[nLen+1];
	
	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );

	nResult = PunctuationCheckType( *ptOrigin );
	nCount = 0;
	while( nResult < 500 )
	{
		csResult.Format( _T("") );
		nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
		nCount++;
		while( nResult != 1 && nResult < 500 )
		{
			csResult.AppendFormat( _T("%c"), *( ptOrigin + nCount - 1 ) );
			nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
			nCount++;
		}
	}

	csName.ReleaseBuffer();

	return csResult;
}

CString FileArrangeGetPrefix( CString csName )
{
	CString csResult;
	int nResult;
	int nCount;
	int nLen = csName.GetLength();
	TCHAR *ptOrigin = new TCHAR[nLen+1];
	
	lstrcpy( ptOrigin, csName.GetBuffer(nLen) );
	
	for( nCount = nLen; nCount >= 0; nCount-- )
	{
		nResult = PunctuationCheckType( *( ptOrigin + nCount ) );
		if( nResult == 1 )
			break;
	}
	
	if( nCount <= 0 )
		csResult.Format( csName );
	else
	{
		*( ptOrigin + nCount ) = 0;
		csResult.Format( _T("%s"), ptOrigin );
	}

	csName.ReleaseBuffer();

	return csResult;
}


