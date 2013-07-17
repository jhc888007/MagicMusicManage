#ifndef __WORD_CHECK_H__
#define __WORD_CHECK_H__



CString WordCheckMusicSuffix( CString csWord );
int WordCheckSpecial( CString csWord );
int WordCheckYear( TCHAR *ptChar );
int WordCheckType( CString csWord );
int WordCheckMusic( CString csWord );
int WordCheckSuffix( CString csWord );
CString WordCheckTitle( CString csName );
CString WordCheckSequence( CString csName );
CString WordCheckLen( CString csName, int nSuffixLen );



#endif