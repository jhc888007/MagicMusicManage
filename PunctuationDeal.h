#ifndef __PUNCTUATION_DEAL_H__
#define __PUNCTUATION_DEAL_H__



CString PunctuationSimplify( CString csPunctuation );
CString PunctuationComplicate( CString csPunctuation );
CString PunctuationWordGetNext( TCHAR *ptChar, int *pCount, int *pFlag );
int PunctuationGetDashPosition( TCHAR *ptChar );
CString PunctuationDeleteBlankBracket( CString csName );
CString PunctuationDeleteHead( CString csName );
CString PunctuationDeleteSingleBracket( CString csName );
CString PunctuationDeleteFirstDot( CString csName );
CString PunctuationDeleteLastDot( CString csName );
CString PunctuationDeleteSequence( CString csName );



#endif