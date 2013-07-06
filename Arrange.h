#ifndef _ARRANGE_H_
#define _ARRANGE_H_



void ArrangeSortGroup( CString csMainDir, CString csSubDir, CString csLyrics, CString csCovers,
	CString csLogs, CString csExtra, int nAllMusicFileNum );
void ArrangeMusicGroup( CString csDir, int nCoverFileNum, int nAllMusicFileNum );
void ArrangeSortGroupSimple( CString csMainDir, CString csSubDir, CString csCovers, CString csLogs, CString csExtra );
void ArrangeMusicGroupSimple( CString csDir );



#endif
