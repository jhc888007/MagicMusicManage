#include "stdafx.h"
#include "File.h"
#include "WordCheck.h"
#include "Arrange.h"
#include "Rename.h"
#include "CommonGroupRename.h"
#include "MusicFileRename.h"
#include "FileArrange.h"



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

	//\u68C0\u67E5\u97F3\u4E50\u6587\u4EF6\u5939\u7C7B\u578B
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

	//\u5982\u679C\u4E0D\u5305\u542B\u97F3\u4E50\u6587\u4EF6\u548C\u97F3\u4E50\u6587\u4EF6\u5939
	if( nMusicDirectoryCount == 0 && nMusicFileCount == 0 )
		return 0;
	//\u5982\u679C\u53EA\u5305\u542B\u97F3\u4E50\u6587\u4EF6\uFF0C\u4E0D\u5305\u542B\u97F3\u4E50\u6587\u4EF6\u5939
	else if( nMusicDirectoryCount == 0 )
		ArrangeMusicGroup( csDir, nCoverFileCount, nAllMusicFileCount );
	//\u5982\u679C\u53EA\u5305\u542B\u4E00\u4E2A\u97F3\u4E50\u6587\u4EF6\u5939
	else if( nMusicDirectoryCount == 1 )
		ArrangeMusicGroup( csDir, nCoverFileCount, nAllMusicFileCount );
	//\u5982\u679C\u5305\u542B\u4E00\u4E2A\u4EE5\u4E0A\u97F3\u4E50\u6587\u4EF6\u5939\uFF0C\u53C8\u5305\u542B\u97F3\u4E50\u6587\u4EF6
	else if( nMusicDirectoryCount > 1 && nMusicFileCount > 0 )
		RenameInGroup( csDir );
	//\u5982\u679C\u5305\u542B\u4E00\u4E2A\u4EE5\u4E0A\u97F3\u4E50\u6587\u4EF6\u5939\uFF0C\u4E0D\u5305\u542B\u97F3\u4E50\u6587\u4EF6
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


