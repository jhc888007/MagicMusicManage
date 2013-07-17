#include "stdafx.h"
#include "Word.h"
#include "WordCheck.h"
#include "Punctuation.h"



CString WordCheckMusicSuffix( CString csWord )
{
	if( WordCompare( csWord, _T("mp3") ) > 0 )
		return _T("MP3");
	if( WordCompare( csWord, _T("ape") ) > 0 )
		return _T("APE");
	if( WordCompare( csWord, _T("flac") ) > 0 )
		return _T("FLAC");
	if( WordCompare( csWord, _T("m4a") ) > 0 )
		return _T("M4A");
	if( WordCompare( csWord, _T("wav") ) > 0 )
		return _T("WAV");
	if( WordCompare( csWord, _T("wv") ) > 0 )
		return _T("WV");
	if( WordCompare( csWord, _T("wma") ) > 0 )
		return _T("WMA");
	if( WordCompare( csWord, _T("ogg") ) > 0 )
		return _T("OGG");
	if( WordCompare( csWord, _T("tta") ) > 0 )
		return _T("TTA");
	if( WordCompare( csWord, _T("mac") ) > 0 )
		return _T("MAC");
	if( WordCompare( csWord, _T("mid") ) > 0 )
		return _T("MID");
	if( WordCompare( csWord, _T("midi") ) > 0 )
		return _T("MIDI");
	if( WordCompare( csWord, _T("rmi") ) > 0 )
		return _T("RMI");
	if( WordCompare( csWord, _T("fla") ) > 0 )
		return _T("FLA");
	if( WordCompare( csWord, _T("dts") ) > 0 )
		return _T("DTS");
	if( WordCompare( csWord, _T("dtswav") ) > 0 )
		return _T("DTSWAV");
	if( WordCompare( csWord, _T("aif") ) > 0 )
		return _T("AIF");
	if( WordCompare( csWord, _T("aiff") ) > 0 )
		return _T("AIFF");
	if( WordCompare( csWord, _T("aifc") ) > 0 )
		return _T("AIFC");
	if( WordCompare( csWord, _T("mp1") ) > 0 )
		return _T("MP1");
	if( WordCompare( csWord, _T("mp2") ) > 0 )
		return _T("MP2");
	if( WordCompare( csWord, _T("mp3pro") ) > 0 )
		return _T("MP3PRO");
	if( WordCompare( csWord, _T("mpa") ) > 0 )
		return _T("MPA");
	if( WordCompare( csWord, _T("mp4") ) > 0 )
		return _T("MP4");
	if( WordCompare( csWord, _T("mpc") ) > 0 )
		return _T("MPC");
	if( WordCompare( csWord, _T("ra") ) > 0 )
		return _T("RA");
	return _T("");
}

int WordCheckSpecial( CString csWord )
{
	//如果需要全大写
	if( WordCompare( csWord, _T("cd") ) > 0 
		|| WordCompare( csWord, _T("cd1") ) > 0 
		|| WordCompare( csWord, _T("cd2") ) > 0
		|| WordCompare( csWord, _T("cd3") ) > 0
		|| WordCompare( csWord, _T("cd4") ) > 0
		|| WordCompare( csWord, _T("cd5") ) > 0
		|| WordCompare( csWord, _T("cd6") ) > 0
		|| WordCompare( csWord, _T("cd7") ) > 0
		|| WordCompare( csWord, _T("cd8") ) > 0
		|| WordCompare( csWord, _T("cd9") ) > 0
		|| WordCompare( csWord, _T("ds") ) > 0
		|| WordCompare( csWord, _T("ep") ) > 0
		|| WordCompare( csWord, _T("va") ) > 0
		|| WordCompare( csWord, _T("dj") ) > 0
		|| WordCompare( csWord, _T("atb") ) > 0
		|| WordCompare( csWord, _T("era") ) > 0
		|| WordCompare( csWord, _T("ost") ) > 0
		|| WordCheckSuffix( csWord ) == 1
		|| WordCheckSuffix( csWord ) == 2 )
		return 1;
	return 0;
}

int WordCheckYear( TCHAR *ptChar )
{
	if( PunctuationCheckType( *ptChar ) > 200
		&& PunctuationCheckType( *ptChar ) < 300
		&& PunctuationCheckType( *(ptChar+1) ) == 0
		&& PunctuationCheckType( *(ptChar+2) ) == 0
		&& PunctuationCheckType( *(ptChar+3) ) == 0
		&& PunctuationCheckType( *(ptChar+4) ) == 0
		&& PunctuationCheckType( *(ptChar+5) ) > 100
		&& PunctuationCheckType( *(ptChar+5) ) < 200 )
		return 1;
	return 0;
}

int WordCheckType( CString csWord )
{
	if( csWord.Compare( _T("专辑") ) == 0
		|| csWord.Compare( _T("合辑") ) == 0
		|| csWord.Compare( _T("EP") ) == 0 )
		return 1;
	return 0;
}

int WordCheckMusic( CString csWord )
{
	if( WordCompare( csWord, _T("mp3") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("ape") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("flac") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("m4a") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("wav") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("wv") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("wv") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("wma") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("ogg") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("tta") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("mac") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("mid") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("midi") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("rmi") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("fla") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("dts") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("dtswav") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("aif") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("aiff") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("aifc") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("mp1") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("mp2") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("mp3pro") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("mpa") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("mp4") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("mpc") ) > 0 )
		return 1;
	if( WordCompare( csWord, _T("ra") ) > 0 )
		return 1;
	return 0;
}

int WordCheckSuffix( CString csWord )
{
	//音乐文件
	if( WordCheckMusic( csWord ) > 0 )
		return 1;
	//索引文件
	if( WordCompare( csWord, _T("cue") ) > 0 
		|| WordCompare( csWord, _T("m3u") ) > 0 
		|| WordCompare( csWord, _T("m3u8") ) > 0
		|| WordCompare( csWord, _T("pls") ) > 0 )
		return 2;
	//歌词文件
	if( WordCompare( csWord, _T("lrc") ) > 0 )
		return 3;
	//图像文件
	if( WordCompare( csWord, _T("ani") ) > 0 
		|| WordCompare( csWord, _T("bmp") ) > 0 
		|| WordCompare( csWord, _T("bw") ) > 0 
		|| WordCompare( csWord, _T("cr2") ) > 0 
		|| WordCompare( csWord, _T("crw") ) > 0 
		|| WordCompare( csWord, _T("dcr") ) > 0 
		|| WordCompare( csWord, _T("dcx") ) > 0 
		|| WordCompare( csWord, _T("dib") ) > 0 
		|| WordCompare( csWord, _T("djv") ) > 0 
		|| WordCompare( csWord, _T("djvu") ) > 0 
		|| WordCompare( csWord, _T("emf") ) > 0 
		|| WordCompare( csWord, _T("gif") ) > 0 
		|| WordCompare( csWord, _T("icn") ) > 0 
		|| WordCompare( csWord, _T("jif") ) > 0 
		|| WordCompare( csWord, _T("jfif") ) > 0 
		|| WordCompare( csWord, _T("jp2") ) > 0 
		|| WordCompare( csWord, _T("jpc") ) > 0 
		|| WordCompare( csWord, _T("jce") ) > 0 
		|| WordCompare( csWord, _T("jpeg") ) > 0 
		|| WordCompare( csWord, _T("jpg") ) > 0 
		|| WordCompare( csWord, _T("jpk") ) > 0 
		|| WordCompare( csWord, _T("jpx") ) > 0 
		|| WordCompare( csWord, _T("pct") ) > 0 
		|| WordCompare( csWord, _T("pcx") ) > 0 
		|| WordCompare( csWord, _T("pdf") ) > 0
		|| WordCompare( csWord, _T("pic") ) > 0 
		|| WordCompare( csWord, _T("pict") ) > 0 
		|| WordCompare( csWord, _T("pix") ) > 0 
		|| WordCompare( csWord, _T("png") ) > 0 
		|| WordCompare( csWord, _T("psp") ) > 0 
		|| WordCompare( csWord, _T("raw") ) > 0 
		|| WordCompare( csWord, _T("tga") ) > 0 
		|| WordCompare( csWord, _T("tif") ) > 0 
		|| WordCompare( csWord, _T("tiff") ) > 0 
		|| WordCompare( csWord, _T("ttc") ) > 0 
		|| WordCompare( csWord, _T("ttf") ) > 0 
		|| WordCompare( csWord, _T("wbm") ) > 0 
		|| WordCompare( csWord, _T("xpm") ) > 0 )
		return 4;
	//记录文件
	if( WordCompare( csWord, _T("log") ) > 0 
		|| WordCompare( csWord, _T("txt") ) > 0 
		|| WordCompare( csWord, _T("nfo") ) > 0 
		|| WordCompare( csWord, _T("lfml") ) > 0 
		|| WordCompare( csWord, _T("pk") ) > 0 
		|| WordCompare( csWord, _T("md5") ) > 0 
		|| WordCompare( csWord, _T("sfv") ) > 0 )
		return 5;
	//无用文件
	if( WordCompare( csWord, _T("db") ) > 0 )
		return 6;
	//其他文件
	return 0;
}

CString WordCheckTitle( CString csName )
{
	CString csResult;
	int nLen = csName.GetLength();
	int nCount;
	TCHAR *ptTemp = new TCHAR[nLen+1];

	if( nLen == 0 ) return _T("");
	lstrcpy( ptTemp, csName.GetBuffer(nLen) );
	csResult.Format( _T("") );

	for( nCount = nLen; nCount >= 0; nCount-- )
	{
		if( *( ptTemp + nCount ) == ']' )
		{
			if( WordCheckYear( ptTemp + nCount - 6 ) == 1 )
				*( ptTemp + nCount - 7 ) = 0;
			else
				*( ptTemp + nCount ) = 0;
		}
	}

	for( nCount = 0; nCount < nLen; nCount++ )
		if( *( ptTemp + nCount ) == '[' )
			break;

	if( nCount < nLen )
		csResult.Format( _T("%s"), ptTemp + nCount + 1 );
	csName.ReleaseBuffer();
	return csResult;
}

CString WordCheckSequence( CString csName )
{
	CString csResult;
	int nLen = csName.GetLength();
	int nCount;
	int nStart;
	TCHAR *ptTemp = new TCHAR[nLen+1];

	if( nLen == 0 ) return _T("");
	lstrcpy( ptTemp, csName.GetBuffer(nLen) );
	csResult.Format( _T("") );

	nStart = 0xFFFFFF;
	for( nCount = 0; nCount < nLen + 1; nCount++ )
	{
		if( PunctuationCheckType( *( ptTemp + nCount ) ) == 0 && nStart == 0xFFFFFF )
			nStart = nCount;
		if( PunctuationCheckType( *( ptTemp + nCount ) ) != 0 && nStart != 0xFFFFFF )
			*( ptTemp + nCount ) = 0;
	}

	if( nStart != 0xFFFFFF )
		csResult.Format( _T("%s"), ptTemp + nStart );
	nLen = csResult.GetLength();
	if( nLen <= 1 || nLen >= 4 )
		csResult.Format( _T("") );

	csName.ReleaseBuffer();
	return csResult;
}

CString WordCheckLen( CString csName, int nSuffixLen )
{
	CString csResult;
	int nLen = csName.GetLength();
	int nCount;
	int nMaxLen;
	TCHAR *ptTemp = new TCHAR[nLen+1];

	if( nLen == 0 ) return _T("");
	lstrcpy( ptTemp, csName.GetBuffer(nLen) );
	csResult.Format( _T("") );

	nMaxLen = 250;
	if( nLen > nMaxLen )
	{
		if( nSuffixLen < 0 )
			for( nCount = nLen; nCount >= 0; nCount-- )
				if( *( ptTemp + nCount ) == '.' )
					nSuffixLen = nLen - nCount;

		if( nSuffixLen < 0 || nSuffixLen > 247 ) nSuffixLen = 0;
		
		if( *( ptTemp + nMaxLen - nSuffixLen - 1 ) == '.' )
			nMaxLen--;

		if( nSuffixLen > 0 )
		{
			*( ptTemp + nMaxLen - nSuffixLen - 1 ) = '.';
			for( nCount = 0; nCount < nSuffixLen; nCount++ )
				*( ptTemp + nMaxLen - nSuffixLen + nCount ) = *( ptTemp + nLen - nSuffixLen + nCount );
		}
		*( ptTemp + nMaxLen ) = 0;
	}

	csResult.Format( _T("%s"), ptTemp );
	csName.ReleaseBuffer();
	return csResult;
}



