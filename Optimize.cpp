#include "stdafx.h"
#include <locale.>
#include "File.h"
#include "WordCheck.h"
#include "FileArrange.h"
#include "Optimize.h"
#include "PunctuationDeal.h"
#include "Global.h"



void Optimize1( CString csDir, CString csTitle )
{
	CStdioFile fAllSongList;
	CString csAllSongList;
	CString csTemp;
	CString csSequence;
	CString csName;
	CString csPrefix;
	CString csOldName;
	CString csNewName;
	CString csSubDir;
	CString csSubTitle;
	int nResult;
	int nSuffixLen;
	int nMusicFileCount;
	int nAllSongListCount;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	csTemp.Format( _T("%s\\*"), csDir );
	BOOL b = pcFile->FindFile( csTemp );
	
	csAllSongList.Format( _T("%s\\%s.AllSongList.m3u"), csDir, csTitle );
	csAllSongList = WordCheckLen( csAllSongList, 15 );
	fAllSongList.Open( csAllSongList, CFile::modeWrite|CFile::modeCreate );
	if( fAllSongList == 0 ) return ;
	
	nMusicFileCount = 0;
	nAllSongListCount = 0;
	b = pcFile->FindNextFile();
	b = pcFile->FindNextFile();
	while( b != NULL )
	{
		b = pcFile->FindNextFile();
		if( pcFile->IsDirectory() )
		{
			csSubDir = pcFile->GetFilePath();
			csTemp = FileCheckMusicInGroup( csSubDir );
			if( csTemp.Compare( _T("") ) != 0 )
			{
				nAllSongListCount++;
				csTemp = pcFile->GetFileName();
				csSubTitle.Format( _T("%s.%s"), csTitle, csTemp );
				Optimize2( csSubDir, csTemp, csSubTitle, &fAllSongList );
			}
		}
		else
		{
			csName = pcFile->GetFileName();
			csTemp = FileArrangeGetSuffix( csName );
			nSuffixLen = csTemp.GetLength();
			nResult = WordCheckSuffix( csTemp );
			if( nResult == 1 || nResult == 2 )
			{
				csPrefix = FileArrangeGetPrefix( csName );
				if( csPrefix.Compare( _T("CDImage") ) == 0 )
				{
					csOldName.Format( _T("%s\\%s"), csDir, csName );
					csNewName.Format( _T("%s\\%s.%s"), csDir, csTitle, csTemp );
					csNewName = WordCheckLen( csNewName, nSuffixLen );
					if( csOldName.Compare( csNewName ) != 0 )
						MoveFile( csOldName, csNewName );
				}
				if( nResult == 1 )
					nMusicFileCount++;
			}
			else if( nResult == 4 )
			{
				csOldName.Format( _T("%s\\%s"), csDir, csName );
				csNewName.Format( _T("%s\\%s.Cover.%s"), csDir, csTitle, csTemp );
				csNewName = WordCheckLen( csNewName, nSuffixLen );
				if( csOldName.Compare( csNewName ) != 0 )
					MoveFile( csOldName, csNewName );
			}
			else if( nResult == 5 )
			{
				csOldName.Format( _T("%s\\%s"), csDir, csName );
				csNewName.Format( _T("%s\\%s.Log.%s"), csDir, csTitle, csTemp );
				csNewName = WordCheckLen( csNewName, nSuffixLen );
				if( csOldName.Compare( csNewName ) != 0 )
					MoveFile( csOldName, csNewName );
			}
		}
	}

	Optimize3( csDir, _T(""), csTitle, nMusicFileCount, &fAllSongList );

	fAllSongList.Close();
	if( nAllSongListCount <= 0 )
		fAllSongList.Remove( csAllSongList );

	return ;
}

void Optimize2( CString csDir, CString csSubDirName, CString csTitle, CStdioFile *pfAllSongList )
{
	CString csName;
	CString csPrefix;
	CString csSequence;
	CString csOldName;
	CString csNewName;
	CString csTemp;
	CString csSubDir;
	CString csSubTitle;
	int nResult;
	int nSuffixLen;
	int nMusicFileCount;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	csTemp.Format( _T("%s\\*"), csDir );
	BOOL b = pcFile->FindFile( csTemp );
	
	nMusicFileCount = 0;
	b = pcFile->FindNextFile();
	b = pcFile->FindNextFile();
	while( b != NULL )
	{
		b = pcFile->FindNextFile();
		if( pcFile->IsDirectory() )
		{
			csSubDir = pcFile->GetFilePath();
			csTemp = FileCheckMusicInGroup( csSubDir );
			if( csTemp.Compare( _T("") ) != 0 )
			{
				csName = pcFile->GetFileName();
				csSubTitle.Format( _T("%s.%s"), csTitle, csName );
				csTemp.Format( _T("%s\\%s"), csSubDirName, csName );
				Optimize2( csSubDir, csTemp, csSubTitle, pfAllSongList );
			}
		}
		else
		{
			csName = pcFile->GetFileName();
			csTemp = FileArrangeGetSuffix( csName );
			nSuffixLen = csTemp.GetLength();
			nResult = WordCheckSuffix( csTemp );
			if( nResult == 1 || nResult == 2 )
			{
				csPrefix = FileArrangeGetPrefix( csName );
				if( csPrefix.Compare( _T("CDImage") ) == 0 )
				{
					csOldName.Format( _T("%s\\%s"), csDir, csName );
					csNewName.Format( _T("%s\\%s.%s"), csDir, csTitle, csTemp );
					csNewName = WordCheckLen( csNewName, nSuffixLen );
					if( csOldName.Compare( csNewName ) != 0 )
						MoveFile( csOldName, csNewName );
				}
				if( nResult == 1 )
					nMusicFileCount++;
			}
			else if( nResult == 4 )
			{
				csOldName.Format( _T("%s\\%s"), csDir, csName );
				csNewName.Format( _T("%s\\%s.Cover.%s"), csDir, csTitle, csTemp );
				csNewName = WordCheckLen( csNewName, nSuffixLen );
				if( csOldName.Compare( csNewName ) != 0 )
					MoveFile( csOldName, csNewName );
			}
			else if( nResult == 5 )
			{
				csOldName.Format( _T("%s\\%s"), csDir, csName );
				csNewName.Format( _T("%s\\%s.Log.%s"), csDir, csTitle, csTemp );
				csNewName = WordCheckLen( csNewName, nSuffixLen );
				if( csOldName.Compare( csNewName ) != 0 )
					MoveFile( csOldName, csNewName );
			}
		}
	}

	Optimize3( csDir, csSubDirName, csTitle, nMusicFileCount, pfAllSongList );

	return ;
}

void Optimize3( CString csDir, CString csSubDirName, CString csTitle, int nMusicFileCount, CStdioFile *pfAllSongList )
{
	CStdioFile fSongList;
	CString csSongList;
	CString csName;
	CString csSequence;
	CString csOldName;
	CString csNewName;
	CString csTemp;
	int nSuffixLen;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	csTemp.Format( _T("%s\\*"), csDir );
	BOOL b = pcFile->FindFile( csTemp );

	if( nMusicFileCount > SINGLE_MUSIC_FILE_MAX )
	{
		csSongList.Format( _T("%s\\%s.SongList.m3u"), csDir, csTitle );
		csSongList = WordCheckLen( csSongList, 12 );
		fSongList.Open( csSongList, CFile::modeWrite|CFile::modeCreate );
	}
	
	b = pcFile->FindNextFile();
	b = pcFile->FindNextFile();
	while( b != NULL )
	{
		b = pcFile->FindNextFile();
		if( !( pcFile->IsDirectory() ) )
		{
			csName = pcFile->GetFileName();
			csTemp = FileArrangeGetSuffix( csName );
			nSuffixLen = csTemp.GetLength();
			if( WordCheckSuffix( csTemp ) == 1 )
			{
				csOldName.Format( _T("%s\\%s"), csDir, csName );
				csSequence = WordCheckSequence( csName );
				//如果需要添加序号
				if( csSequence.Compare( _T("") ) != 0 && nMusicFileCount > SINGLE_MUSIC_FILE_MAX )
				{
					csTemp = PunctuationDeleteSequence( csName );
					csNewName.Format( _T("%s\\%s.-.%s"), csDir, csSequence, csTemp );
					csNewName = WordCheckLen( csNewName, nSuffixLen );
					if( csOldName.Compare( csNewName ) != 0 )
						MoveFile( csOldName, csNewName );
					csNewName.Format( _T("%s.-.%s"), csSequence, csTemp );
					if( csSubDirName.Compare( _T("") ) != 0 )
						csName.Format( _T("%s\\%s.-.%s"), csSubDirName, csSequence, csTemp );
					else
						csName.Format( _T("%s.-.%s"), csSequence, csTemp );
				}
				//如果需要删除序号
				else if( csSequence.Compare( _T("") ) != 0 && nMusicFileCount <= NO_SEQUENCE_FILE_MAX )
				{
					csTemp = PunctuationDeleteSequence( csName );
					csNewName.Format( _T("%s\\%s"), csDir, csTemp );
					csNewName = WordCheckLen( csNewName, nSuffixLen );
					if( csOldName.Compare( csNewName ) != 0 )
						MoveFile( csOldName, csNewName );
					csNewName.Format( _T("%s"), csTemp );
					if( csSubDirName.Compare( _T("") ) != 0 )
						csName.Format( _T("%s\\%s"), csSubDirName, csTemp );
					else
						csName.Format( _T("%s"), csTemp );
				}
				//如果不需要改变
				else
				{
					csNewName.Format( _T("%s"), csName );
					csTemp.Format( _T("%s\\%s"), csSubDirName, csName );
					csName.Format( _T("%s"), csTemp );
				}
				setlocale( LC_CTYPE, "chs" );
				if( nMusicFileCount > SINGLE_MUSIC_FILE_MAX && fSongList != 0 )
				{
					fSongList.WriteString( csNewName );
					fSongList.WriteString( _T("\n") );
				}
				pfAllSongList->WriteString( csName );
				pfAllSongList->WriteString( _T("\n") );
			}
		}
	}

	if( nMusicFileCount > SINGLE_MUSIC_FILE_MAX && fSongList != 0 )
		fSongList.Close();
	
	return ;
}


