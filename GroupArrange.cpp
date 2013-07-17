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

		//查找文件夹中的文件
		csTemp.Format( _T("%s\\*"), csDir );
		b = pcFile->FindFile( csTemp );
		b = pcFile->FindNextFile();
		b = pcFile->FindNextFile();
		//如果文件夹为空，返回0
		if( b == NULL )
			return 0;

		//删除空文件夹
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


