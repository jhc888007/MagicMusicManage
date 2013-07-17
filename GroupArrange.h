#ifndef _GROUP_ARRANGE_H_
#define _GROUP_ARRANGE_H_



void GroupArrangeMake( CString csDir, CString csLyrics, CString csCovers, CString csLogs,
	CString csExtra );
int GroupArrangeDelete( CString csDir );
void GroupArrangeRename( CString csDir, CString csLyrics, CString csCovers, CString csLogs,
	CString csExtra, CString csLyrics1, CString csCovers1, CString csLogs1, CString csExtra1 );



#endif
