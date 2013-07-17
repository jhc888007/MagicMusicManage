#include "stdafx.h"



//大写单词所有字母
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

//大写单词第一个字母，其余小写
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

//大写单词第一个字母，其余不改变
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

//小写单词所有字母
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
//寻找单词中是否包含某内容，可识别三种大小写格式：所有字母大写，所有字母小写，头字母大写
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

//寻找两单词是否相同，可识别三种大小写格式：所有字母大写，所有字母小写，头字母大写
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


