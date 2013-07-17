#include "stdafx.h"
#include "WordCheck.h"
#include "MusicFileRename.h"
#include "MusicGroupRename.h"
#include "FileArrange.h"



CString FileCheckMusicInGroup( CString csDir )
{
	CString csName;
	CString csTemp;
	CString csMark;
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
			csTemp = pcFile->GetFilePath();
			csMark = FileCheckMusicInGroup( csTemp );
		}
		else
		{
			csName = pcFile->GetFileName();
			csTemp = FileArrangeGetSuffix( csName );
			csMark = WordCheckMusicSuffix( csTemp );
		}
		if( csMark.Compare( _T("") ) > 0 )
			return csMark;
	}
	return csMark;
}

void FileCheckTypeInGroup( CString csDir, int *pMusicCount, int *pCoverCount )
{
	CString csName;
	CString csTemp;
	int nResult;
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
			csTemp = pcFile->GetFilePath();
			FileCheckTypeInGroup( csTemp, pMusicCount, pCoverCount );
		}
		else
		{
			csTemp = pcFile->GetFileName();
			csTemp = FileArrangeGetSuffix( csTemp );
			nResult = WordCheckSuffix( csTemp );
			if( nResult == 1 )
				( *pMusicCount ) += 1;
			else if( nResult == 4 )
				( *pCoverCount ) += 1;
		}
	}

	return ;
}


