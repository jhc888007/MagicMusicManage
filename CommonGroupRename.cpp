#include "stdafx.h"
#include "File.h"
#include "MusicGroupRename.h"
#include "PunctuationDeal.h"



CString CommonGroupSimplify( CString csName )
{
	CString csResult;
	csResult = MusicGroupSimplify( csName );
	return csResult;
}

CString CommonGroupBeautify( CString csName )
{
	CString csResult;
	csResult = PunctuationDeleteBlankBracket( csName );
	csResult = PunctuationDeleteSingleBracket( csResult );
	return csResult;
}

CString CommonGroupComplicate( CString csName )
{
	CString csResult;
	csResult = MusicGroupComplicate( csName );
	return csResult;
}

CString CommonGroupRename( CString csName )
{
	CString csResult;
	
	csResult = CommonGroupSimplify( csName );
	csResult = CommonGroupBeautify( csResult );
	csResult = CommonGroupComplicate( csResult );

	return csResult;
}

