#include "stdafx.h"
#include "File.h"
#include "WordCheck.h"
#include "Arrange.h"
#include "Rename.h"
#include "CommonGroupRename.h"
#include "MusicFileRename.h"
#include "FileArrange.h"



extern CString g_delete;



int CheckGroupTypeAndArrange( CString csDir )
{
	CString csName;
	CString csNewName;
	CString csSubDir;
	CString csTemp;
	int nResult;
	int nMusicDirectoryCount;
	int nSubMusicFileCount;
	int nAllMusicFileCount;
	int nMusicFileCount;
	int nCoverFileCount;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	csTemp.Format( _T("%s\\*"), csDir );
	BOOL b = pcFile->FindFile( csTemp );

	//检查音乐文件夹类型
	nMusicDirectoryCount = 0;
	nAllMusicFileCount = 0;
	nMusicFileCount = 0;
	nCoverFileCount = 0;
	b = pcFile->FindNextFile();
	b = pcFile->FindNextFile();
	while( b != NULL )
	{
		b = pcFile->FindNextFile();
		if( pcFile->IsDirectory() )
		{
			nSubMusicFileCount = 0;
			csSubDir = pcFile->GetFilePath();
			FileCheckTypeInGroup( csSubDir, &nSubMusicFileCount, &nCoverFileCount );
			if( nSubMusicFileCount > 0 )
			{
				nAllMusicFileCount += nSubMusicFileCount;
				nMusicDirectoryCount++;
			}
		}
		else
		{
			csTemp = pcFile->GetFileName();
			csTemp = FileArrangeGetSuffix( csTemp );
			nResult = WordCheckSuffix( csTemp );
			if( nResult == 1 )
			{
				nMusicFileCount++;
				nAllMusicFileCount++;
			}
			else if( nResult == 4 )
				nCoverFileCount++;
		}
	}

	//如果不包含音乐文件和音乐文件夹
	if( nMusicDirectoryCount == 0 && nMusicFileCount == 0 )
		return 0;
	//如果只包含音乐文件，不包含音乐文件夹
	else if( nMusicDirectoryCount == 0 )
		ArrangeMusicGroup( csDir, nCoverFileCount, nAllMusicFileCount );
	//如果只包含一个音乐文件夹
	else if( nMusicDirectoryCount == 1 )
		ArrangeMusicGroup( csDir, nCoverFileCount, nAllMusicFileCount );
	//如果包含一个以上音乐文件夹，又包含音乐文件
	else if( nMusicDirectoryCount > 1 && nMusicFileCount > 0 )
		RenameInGroup( csDir );
	//如果包含一个以上音乐文件夹，不包含音乐文件
	else
	{
		csTemp.Format( _T("%s\\*"), csDir );
		b = pcFile->FindFile( csTemp );
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
					CheckGroupTypeAndArrange( csSubDir );
				else
					RenameInGroup( csSubDir );

				csTemp = pcFile->GetFileName();
				csName.Format( _T("%s\\%s"), csDir, csTemp );
				csTemp = CommonGroupRename( csTemp );
				csNewName.Format( _T("%s\\%s"), csDir, csTemp );
				csNewName = WordCheckLen( csNewName, 0 );
				if( csName.Compare( csNewName ) != 0 )
					MoveFile( csName, csNewName);
			}
			else
			{
				csTemp = pcFile->GetFileName();
				csName.Format( _T("%s\\%s"), csDir, csTemp );
				csTemp = MusicFileRename( csTemp );
				csNewName.Format( _T("%s\\%s"), csDir, csTemp );
				csNewName = WordCheckLen( csNewName, -1 );
				if( csName.Compare( csNewName ) != 0 )
					MoveFile( csName, csNewName);
			}
		}
		ArrangeMusicGroupSimple( csDir );
	}

	return 1;
}


