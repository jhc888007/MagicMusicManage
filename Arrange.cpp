#include "stdafx.h"
#include "FileArrange.h"
#include "WordCheck.h"
#include "MusicFileRename.h"
#include "GroupArrange.h"
#include "Global.h"
#include "File.h"



void ArrangeSortGroup( CString csMainDir, CString csSubDir, CString csLyrics, CString csCovers,
	CString csLogs, CString csExtra, int nAllMusicFileNum )
{
	CString csName;
	CString csNewName;
	CString csSuffix;
	CString csTemp;
	int nResult;
	int nSuffixLen;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	csTemp.Format( _T("%s\\*"), csSubDir );
	BOOL b = pcFile->FindFile( csTemp );

	b = pcFile->FindNextFile();
	b = pcFile->FindNextFile();
	while( b != NULL )
	{
		b = pcFile->FindNextFile();
		if( pcFile->IsDirectory() )
		{
			csTemp = pcFile->GetFilePath();
			ArrangeSortGroup( csMainDir, csTemp, csLyrics, csCovers, csLogs, csExtra, nAllMusicFileNum );
		}
		else
		{
			csTemp = pcFile->GetFileName();
			csName.Format( _T("%s\\%s"), csSubDir, csTemp );
			csSuffix = FileArrangeGetSuffix( csTemp );
			nSuffixLen = csSuffix.GetLength();
			nResult = WordCheckSuffix( csSuffix );
			csTemp = MusicFileRename( csTemp );
			switch( nResult )
			{
			//音乐
			case 1:
				csNewName.Format( _T("%s\\%s"), csMainDir, csTemp );
				break;
			//索引
			case 2:
				if( csName.Find( _T("SongList") ) == -1 && nAllMusicFileNum > SINGLE_MUSIC_FILE_MAX )
					csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csLogs, csTemp );
				else
					csNewName.Format( _T("%s\\%s"), csMainDir, csTemp );
				break;
			//歌词
			case 3:
				csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csLyrics, csTemp );
				break;
			//图片
			case 4:
				if( csCovers.Compare( _T("") ) != 0 )
					csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csCovers, csTemp );
				else
					csNewName.Format( _T("%s\\%s"), csMainDir, csTemp );
				break;
			//记录
			case 5:
				csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csLogs, csTemp );
				break;
			//无用
			case 6:
				if( csTemp.Compare( _T("Thumbs.db") ) == 0 )
				{
					DeleteFile( csName );
					csNewName.Format( _T("") );
					break; //此处break有意放在括号内
				}
			//其他
			default:
				csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csExtra, csTemp );
				break;
			}
			csNewName = WordCheckLen( csNewName, nSuffixLen );
			if( csName.Compare( csNewName ) != 0 && csNewName.Compare( _T("") ) != 0 )
				MoveFile( csName, csNewName );
		}
	}

	return ;
}

void ArrangeMusicGroup( CString csDir, int nCoverFileNum, int nAllMusicFileNum )
{
	CString csTempLyrics;
	CString csTempCovers;
	CString csTempLogs;
	CString csTempExtra;
	CString csLyrics;
	CString csCovers;
	CString csLogs;
	CString csExtra;

	csTempLyrics.Format( _T("_Lyrics") );
	csLyrics.Format( _T("Lyrics") );
	if( nCoverFileNum > 1 )
	{
		csTempCovers.Format( _T("_Covers") );
		csCovers.Format( _T("Covers") );
	}
	else
	{
		csTempCovers.Format( _T("") );
		csCovers.Format( _T("") );
	}
	csTempLogs.Format( _T("_Logs") );
	csLogs.Format( _T("Logs") );
	csTempExtra.Format( _T("_Extra") );
	csExtra.Format( _T("Extra") );

	GroupArrangeMake( csDir, csTempLyrics, csTempCovers, csTempLogs, csTempExtra );
	ArrangeSortGroup( csDir, csDir, csTempLyrics, csTempCovers, csTempLogs, csTempExtra, nAllMusicFileNum );
	GroupArrangeDelete( csDir );
	GroupArrangeRename( csDir, csTempLyrics, csTempCovers, csTempLogs, csTempExtra,
		csLyrics, csCovers, csLogs, csExtra );

	return ;
}

void ArrangeSortGroupSimple( CString csMainDir, CString csSubDir, CString csCovers, CString csLogs, CString csExtra )
{
	CString csName;
	CString csNewName;
	CString csSuffix;
	CString csTemp;
	int nResult;
	int nSuffixLen;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	csTemp.Format( _T("%s\\*"), csSubDir );
	BOOL b = pcFile->FindFile( csTemp );

	b = pcFile->FindNextFile();
	b = pcFile->FindNextFile();
	while( b != NULL )
	{
		b = pcFile->FindNextFile();
		if(  pcFile->IsDirectory() )
		{
			csTemp = pcFile->GetFilePath();
			csSuffix = FileCheckMusicInGroup( csTemp );
			if( csSuffix.Compare( _T("") ) == 0 )
				ArrangeSortGroupSimple( csMainDir, csTemp, csCovers, csLogs, csExtra );
		}
		else
		{
			csTemp = pcFile->GetFileName();
			csName.Format( _T("%s\\%s"), csSubDir, csTemp );
			csSuffix = FileArrangeGetSuffix( csTemp );
			nSuffixLen = csSuffix.GetLength();
			nResult = WordCheckSuffix( csSuffix );
			csTemp = MusicFileRename( csTemp );
			switch( nResult )
			{
			//音乐
			case 1:
				csNewName.Format( _T("%s\\%s"), csMainDir, csTemp );
				break;
			//索引
			case 2:
				if( csName.Find( _T("SongList") ) == -1 )
					csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csLogs, csTemp );
				else
					csNewName.Format( _T("%s\\%s"), csMainDir, csTemp );
				break;
			//歌词
			case 3:
				DeleteFile( csName );
				csNewName.Format( _T("") );
				break;
			//图片
			case 4:
				csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csCovers, csTemp );
				break;
			//记录
			case 5:
				csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csLogs, csTemp );
				break;
			//无用
			case 6:
				if( csTemp.Compare( _T("Thumbs.db") ) == 0 )
				{
					DeleteFile( csName );
					csNewName.Format( _T("") );
				}
				else
				{
					csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csExtra, csTemp );
				}
			//其他
			default:
				csNewName.Format( _T("%s\\%s\\%s"), csMainDir, csExtra, csTemp );
				break;
			}
			csNewName = WordCheckLen( csNewName, nSuffixLen );
			if( csName.Compare( csNewName ) != 0 && csNewName.Compare( _T("") ) != 0 )
				MoveFile( csName, csNewName );
		}
	}

	return ;
}

void ArrangeMusicGroupSimple( CString csDir )
{
	CString csTempLyrics;
	CString csTempCovers;
	CString csTempLogs;
	CString csTempExtra;
	CString csLyrics;
	CString csCovers;
	CString csLogs;
	CString csExtra;

	csTempLyrics.Format( _T("_Lyrics") );
	csLyrics.Format( _T("Lyrics") );
	csTempCovers.Format( _T("_Covers") );
	csCovers.Format( _T("Covers") );
	csTempLogs.Format( _T("_Logs") );
	csLogs.Format( _T("Logs") );
	csTempExtra.Format( _T("_Extra") );
	csExtra.Format( _T("Extra") );

	GroupArrangeMake( csDir, csTempLyrics, csTempCovers, csTempLogs, csTempExtra );
	ArrangeSortGroupSimple( csDir, csDir, csTempCovers, csTempLogs, csTempExtra );
	GroupArrangeDelete( csDir );
	GroupArrangeRename( csDir, csTempLyrics, csTempCovers, csTempLogs, csTempExtra,
		csLyrics, csCovers, csLogs, csExtra );

	return ;
}



