#include "stdafx.h"
#include "WordCheck.h"



void GroupArrangeMake( CString csDir, CString csLyrics, CString csCovers, CString csLogs,
	CString csExtra )
{
	CString csName;

	csName.Format( _T("%s\\%s"), csDir, csLyrics );
	csName = WordCheckLen( csName, 0 );
	CreateDirectory( csName, NULL );
	if( csCovers.Compare( _T("") ) != 0 )
	{
		csName.Format( _T("%s\\%s"), csDir, csCovers );
		csName = WordCheckLen( csName, 0 );
		CreateDirectory( csName, NULL );
	}
	csName.Format( _T("%s\\%s"), csDir, csLogs );
	csName = WordCheckLen( csName, 0 );
	CreateDirectory( csName, NULL );
	csName.Format( _T("%s\\%s"), csDir, csExtra );
	csName = WordCheckLen( csName, 0 );
	CreateDirectory( csName, NULL );

	return ;
}

int GroupArrangeDelete( CString csDir )
{
	CString csName;
	CString csTemp;
	int nFlag;
	CFileFind cFile;
	CFileFind *pcFile = &cFile;
	BOOL b;

	nFlag = 0;
	while( nFlag == 0 )
	{
		nFlag = 1;

		//\u67E5\u627E\u6587\u4EF6\u5939\u4E2D\u7684\u6587\u4EF6
		csTemp.Format( _T("%s\\*"), csDir );
		b = pcFile->FindFile( csTemp );
		b = pcFile->FindNextFile();
		b = pcFile->FindNextFile();
		//\u5982\u679C\u6587\u4EF6\u5939\u4E3A\u7A7A\uFF0C\u8FD4\u56DE0
		if( b == NULL )
			return 0;

		//\u5220\u9664\u7A7A\u6587\u4EF6\u5939
		while( b != NULL )
		{
			b = pcFile->FindNextFile();
			if( pcFile->IsDirectory() )
			{
				csTemp = pcFile->GetFilePath();
				if( GroupArrangeDelete( csTemp ) == 0 )
				{
					RemoveDirectory( csTemp );
					nFlag = 0;
					break;
				}
			}
		}
	}

	return 1;
}

void GroupArrangeRename( CString csDir, CString csLyrics, CString csCovers, CString csLogs,
	CString csExtra, CString csLyrics1, CString csCovers1, CString csLogs1, CString csExtra1 )
{
	CString csName;
	CString csName1;

	csName.Format( _T("%s\\%s"), csDir, csLyrics );
	csName1.Format( _T("%s\\%s"), csDir, csLyrics1 );
	csName1 = WordCheckLen( csName1, 0 );
	MoveFile( csName, csName1 );
	if( csCovers.Compare( _T("") ) != 0 )
	{
		csName.Format( _T("%s\\%s"), csDir, csCovers );
		csName1.Format( _T("%s\\%s"), csDir, csCovers1 );
		csName1 = WordCheckLen( csName1, 0 );
		MoveFile( csName, csName1 );
	}
	csName.Format( _T("%s\\%s"), csDir, csLogs );
	csName1.Format( _T("%s\\%s"), csDir, csLogs1 );
	csName1 = WordCheckLen( csName1, 0 );
	MoveFile( csName, csName1 );
	csName.Format( _T("%s\\%s"), csDir, csExtra );
	csName1.Format( _T("%s\\%s"), csDir, csExtra1 );
	csName1 = WordCheckLen( csName1, 0 );
	MoveFile( csName, csName1 );

	return ;
}


