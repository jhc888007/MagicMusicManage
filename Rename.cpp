#include "stdafx.h"
#include "File.h"
#include "MusicFileRename.h"
#include "MusicGroupRename.h"
#include "CommonGroupRename.h"
#include "Check.h"
#include "Optimize.h"
#include "WordCheck.h"



void RenameInGroup( CString csDir )
{
	CString csName;
	CString csSubDir;
	CString csNewName;
	CString csTemp;
	CString csTemp1;
	CString csTemp2;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	csTemp.Format( _T("%s\\*"), csDir );
	BOOL b = pcFile->FindFile( csTemp );
	
	b = pcFile->FindNextFile();
	b = pcFile->FindNextFile();
	while( b != NULL )
	{
		b = pcFile->FindNextFile();
		if( pcFile->IsDirectory() )
		{
			csSubDir = pcFile->GetFilePath();
			RenameInGroup( csSubDir );

			csTemp1 = pcFile->GetFileName();
			csTemp2 = CommonGroupRename( csTemp1 );
			csName.Format( _T("%s\\%s"), csDir, csTemp1 );
			csNewName.Format( _T("%s\\%s"), csDir, csTemp2 );
			csNewName = WordCheckLen( csNewName, 0 );
			if( csName.Compare( csNewName ) != 0 )
				MoveFile( csName, csNewName);
		}
		else
		{
			csTemp1 = pcFile->GetFileName();
			csTemp2 = MusicFileRename( csTemp1 );
			csName.Format( _T("%s\\%s"), csDir, csTemp1 );
			csNewName.Format( _T("%s\\%s"), csDir, csTemp2 );
			csNewName = WordCheckLen( csNewName, -1 );
			if( csName.Compare( csNewName ) != 0 )
				MoveFile( csName, csNewName);
		}
	}
	return ;
}

void RenameAfterCheck( CString csDir, CString csArtist, int nArtistLock, CString csType )
{
	CString csName;
	CString csSubDir;
	CString csNewName;
	CString csMark;
	CString csTemp;
	CString csTemp1;
	CString csTemp2;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	csTemp.Format( _T("%s\\*"), csDir );
	BOOL b = pcFile->FindFile( csTemp );

	csMark.Format( _T("") );
	b = pcFile->FindNextFile();
	b = pcFile->FindNextFile();
	while( b != NULL )
	{
		b = pcFile->FindNextFile();
		if( pcFile->IsDirectory() )
		{
			csSubDir = pcFile->GetFilePath();
			csMark = FileCheckMusicInGroup( csSubDir );
			if( csMark.Compare( _T("") ) != 0 )
			{
				CheckGroupTypeAndArrange( csSubDir );
				csTemp1 = pcFile->GetFileName();
				csTemp2 = MusicGroupRename( csTemp1, csArtist, nArtistLock, csType, csMark );
				csName.Format( _T("%s\\%s"), csDir, csTemp1 );
				csNewName.Format( _T("%s\\%s"), csDir, csTemp2 );
				csNewName = WordCheckLen( csNewName, 0 );
				if( csName.Compare( csNewName ) != 0 )
					MoveFile( csName, csNewName);
				csTemp1 = WordCheckTitle( csTemp2 );
				Optimize1( csNewName, csTemp1 );
			}
		}
	}
	return ;
}