#include "stdafx.h"



//\u5927\u5199\u5355\u8BCD\u6240\u6709\u5B57\u6BCD
CString WordCap( CString csWord )
{
	CString csResult;
	int nLen = csWord.GetLength();
	int nCount;
	TCHAR *ptTemp = new TCHAR[nLen+1];

	if( nLen == 0 ) return _T("");
	lstrcpy( ptTemp, csWord.GetBuffer(nLen) );

	for( nCount = 0; nCount < nLen + 1; nCount++ )
	{
		if( *( ptTemp + nCount ) >= 'a' && *( ptTemp + nCount ) <= 'z' )
			*( ptTemp + nCount ) = *( ptTemp + nCount ) - 32;
	}

	csResult.Format( ptTemp );
	csWord.ReleaseBuffer();
	return csResult;
}

//\u5927\u5199\u5355\u8BCD\u7B2C\u4E00\u4E2A\u5B57\u6BCD\uFF0C\u5176\u4F59\u5C0F\u5199
CString WordFirstCapOnly( CString csWord )
{
	CString csResult;
	int nLen = csWord.GetLength();
	int nCount;
	csResult.Format( _T("%d"), nLen );
	TCHAR *ptTemp = new TCHAR[nLen+1];

	if( nLen == 0 ) return _T("");
	lstrcpy( ptTemp, csWord.GetBuffer(nLen) );

	for( nCount = 0; nCount < nLen + 1; nCount++ )
	{
		if( nCount == 0 && *( ptTemp + nCount ) >= 'a' && *( ptTemp + nCount ) <= 'z' )
			*( ptTemp + nCount ) = *( ptTemp + nCount ) - 32;
		else if( *( ptTemp + nCount ) >= 'A' && *( ptTemp + nCount ) <= 'Z' )
			*( ptTemp + nCount ) = *( ptTemp + nCount ) + 32;
	}

	csResult.Format( ptTemp );
	csWord.ReleaseBuffer();
	return csResult;
}

//\u5927\u5199\u5355\u8BCD\u7B2C\u4E00\u4E2A\u5B57\u6BCD\uFF0C\u5176\u4F59\u4E0D\u6539\u53D8
CString WordFirstCap( CString csWord )
{
	CString csResult;
	int nLen = csWord.GetLength();
	TCHAR *ptTemp = new TCHAR[nLen+1];

	if( nLen == 0 ) return _T("");
	lstrcpy( ptTemp, csWord.GetBuffer(nLen) );

	if( *( ptTemp ) >= 'a' && *( ptTemp ) <= 'z' )
		*( ptTemp ) = *( ptTemp ) - 32;

	csResult.Format( ptTemp );
	csWord.ReleaseBuffer();
	return csResult;
}

//\u5C0F\u5199\u5355\u8BCD\u6240\u6709\u5B57\u6BCD
CString WordLower( CString csWord )
{
	CString csResult;
	int nLen = csWord.GetLength();
	int nCount;
	TCHAR *ptTemp = new TCHAR[nLen+1];

	if( nLen == 0 ) return _T("");
	lstrcpy( ptTemp, csWord.GetBuffer(nLen) );

	for( nCount = 0; nCount < nLen + 1; nCount++ )
	{
		if( *( ptTemp + nCount ) >= 'A' && *( ptTemp + nCount ) <= 'Z' )
			*( ptTemp + nCount ) = *( ptTemp + nCount ) + 32;
	}

	csResult.Format( ptTemp );
	csWord.ReleaseBuffer();
	return csResult;
}
/*
//\u5BFB\u627E\u5355\u8BCD\u4E2D\u662F\u5426\u5305\u542B\u67D0\u5185\u5BB9\uFF0C\u53EF\u8BC6\u522B\u4E09\u79CD\u5927\u5C0F\u5199\u683C\u5F0F\uFF1A\u6240\u6709\u5B57\u6BCD\u5927\u5199\uFF0C\u6240\u6709\u5B57\u6BCD\u5C0F\u5199\uFF0C\u5934\u5B57\u6BCD\u5927\u5199
int WordFind1( CString csWord, CString csContent )
{
	CString csCap;
	CString csFirstCap;
	CString csLower;

	csCap = WordCap( csContent );
	csFirstCap = WordFirstCapOnly( csContent );
	csLower = WordLower( csContent );
	
	if( csWord.Find( csCap ) != -1 )
		return 1;
	if( csWord.Find( csFirstCap ) != -1 )
		return 2;
	if( csWord.Find( csLower ) != -1 )
		return 3;

	return 0;
}

//\u5BFB\u627E\u4E24\u5355\u8BCD\u662F\u5426\u76F8\u540C\uFF0C\u53EF\u8BC6\u522B\u4E09\u79CD\u5927\u5C0F\u5199\u683C\u5F0F\uFF1A\u6240\u6709\u5B57\u6BCD\u5927\u5199\uFF0C\u6240\u6709\u5B57\u6BCD\u5C0F\u5199\uFF0C\u5934\u5B57\u6BCD\u5927\u5199
int WordCompare1( CString csWord1, CString csWord2 )
{
	CString csCap;
	CString csFirstCap;
	CString csLower;

	csCap = WordCap( csWord2 );
	csFirstCap = WordFirstCapOnly( csWord2 );
	csLower = WordLower( csWord2 );
	if( csWord1.Compare( csCap ) == 0 )
		return 1;
	if( csWord1.Compare( csFirstCap ) == 0 )
		return 2;
	if( csWord1.Compare( csLower ) == 0 )
		return 3;

	return 0;
}*/

int WordCharactorCompare( TCHAR *pt1, TCHAR *pt2 )
{
	if( *pt1 >= 'A' && *pt1 <= 'Z' )
	{
		if( *pt1 != *pt2 && *pt1 != *pt2 - 32 )
			return 0;
		else
			return 1;
	}
	if( *pt1 >= 'a' && *pt1 <= 'z' )
	{
		if( *pt1 != *pt2 && *pt1 != *pt2 + 32 )
			return 0;
		else
			return 1;
	}
	if( *pt1 >= '0' && *pt2 <= '9' )
	{
		if( *pt1 != *pt2 )
			return 0;
		else
			return 1;
	}
	return 0;
}

int WordFind( CString csWord, CString csContent )
{
	int nWord1Len = csWord.GetLength();
	int nWord2Len = csContent.GetLength();
	int nCount1;
	int nCount2;
	TCHAR *ptTemp1 = new TCHAR[nWord1Len+1];
	TCHAR *ptTemp2 = new TCHAR[nWord2Len+1];

	if( nWord1Len == 0 ) return 0;
	if( nWord2Len == 0 ) return 1;
	if( nWord1Len < nWord2Len ) return 0;
	lstrcpy( ptTemp1, csWord.GetBuffer(nWord1Len) );
	lstrcpy( ptTemp2, csContent.GetBuffer(nWord2Len) );

	nCount2 =0;
	for( nCount1 = 0; nCount1 < nWord1Len + 1; nCount1++ )
	{
		if( WordCharactorCompare( ptTemp1 + nCount1, ptTemp2 + nCount2 ) > 0 )
		{
			if( nCount2 < nWord2Len - 1 ) nCount2++;
			else break;
		}
		else
			nCount2 = 0;
	}

	csWord.ReleaseBuffer();
	csContent.ReleaseBuffer();

	if( nCount2 >= nWord2Len - 1 ) return 1;
	else return 0;
}

int WordCompare( CString csWord1, CString csWord2 )
{
	int nWord1Len = csWord1.GetLength();
	int nWord2Len = csWord2.GetLength();
	int nCount;
	TCHAR *ptTemp1 = new TCHAR[nWord1Len+1];
	TCHAR *ptTemp2 = new TCHAR[nWord2Len+1];

	if( nWord1Len == 0 && nWord2Len == 0 ) return 0;
	if( nWord1Len != nWord2Len ) return 0;
	lstrcpy( ptTemp1, csWord1.GetBuffer(nWord1Len) );
	lstrcpy( ptTemp2, csWord2.GetBuffer(nWord2Len) );

	for( nCount = 0; nCount < nWord1Len; nCount++ )
	{
		if( WordCharactorCompare( ptTemp1 + nCount, ptTemp2 + nCount ) == 0 )
			break;
	}

	csWord1.ReleaseBuffer();
	csWord2.ReleaseBuffer();

	if( nCount < nWord1Len ) return 0;
	else return 1;
}


