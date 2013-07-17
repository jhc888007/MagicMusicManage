#include "stdafx.h"



CString Instruction( void )
{
	CString csResult;
	csResult.Format( _T("") );
	///////////////////////////1234567890123456789012345678901234567890123456789012345678901234567890
	csResult.AppendFormat( _T("**********************************************************************\r\n") );
	csResult.AppendFormat( _T("*                                    欢迎使用JHC888007软件！                                     *\r\n") );
	csResult.AppendFormat( _T("*                                                                                                             *\r\n") );
	csResult.AppendFormat( _T("*                                             by jhc888007                                              *\r\n") );
	csResult.AppendFormat( _T("*                                        jhc888007@163.com                                         *\r\n") );
	csResult.AppendFormat( _T("**********************************************************************\r\n") );
	csResult.AppendFormat( _T("\r\n") );
	csResult.AppendFormat( _T("使用说明：\r\n") );
	csResult.AppendFormat( _T("输入：目录必填，为需整理专辑目录的父目录。\r\n") );
	csResult.AppendFormat( _T("输入：艺术家选填，为（默认）艺术家。\r\n") );
	csResult.AppendFormat( _T("输入：需删除选填，文件（夹）名中需要删除的单词。\r\n") );
	csResult.AppendFormat( _T("选项：选中“锁定”，则认为输入艺术家为所有专辑的艺术家（如果输入不为空）。不\r\n") );
	csResult.AppendFormat( _T("         选“锁定”，则认为输入艺术家为默认艺术家，当程序不能从目录名称获取艺术\r\n") );
	csResult.AppendFormat( _T("         家时使用默认艺术家。\r\n") );
	csResult.AppendFormat( _T("选项：选中“特殊模式”，则认为此目录下所有文件都不是音乐文件，仅仅将所有文件\r\n") );
	csResult.AppendFormat( _T("         命名整理。不选“特殊模式”，则为普通模式。\r\n") );
	csResult.AppendFormat( _T("专辑目录名-艺术家：在不锁定艺术家状态，专辑目录名的第一个“-”符号前是艺术家\r\n") );
	csResult.AppendFormat( _T("         名。\r\n") );
	csResult.AppendFormat( _T("专辑目录名-发行年份：发行年份需要使用“()”“[]”“{}”括起。\r\n") );
	csResult.AppendFormat( _T("专辑目录名-音乐格式：如果专辑目录名中包含格式信息，则使用该格式，否则则以\r\n") );
	csResult.AppendFormat( _T("         专辑内任意音乐文件格式为专辑格式。\r\n") );
	csResult.AppendFormat( _T("专辑目录名-唱片类型：支持“专辑”“合辑”“EP”三种格式，默认为“专辑”，另两种需要\r\n") );
	csResult.AppendFormat( _T("         在目录名任意位置注明（前后不与其他字母数字相连）。\r\n") );
	csResult.AppendFormat( _T("\r\n") );
	csResult.AppendFormat( _T("**********************************************************************") );
	return csResult;
}

