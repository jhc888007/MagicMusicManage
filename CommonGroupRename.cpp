#include "stdafx.h"
#include "File.h"
#include "MusicGroupRename.h"
#include "PunctuationDeal.h"
#include "CutRename.h"



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
	
	csResult = CutRename( csName );
	csResult = CommonGroupSimplify( csResult );
	csResult = CommonGroupBeautify( csResult );
	csResult = CommonGroupComplicate( csResult );

	return csResult;
}

