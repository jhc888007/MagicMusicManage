#include "stdafx.h"



int PunctuationCheckType( TCHAR tChar )
{
	//符号判断
	switch( tChar )
	{
	//前后字母都相接
	case '.': return 1;
	case '_': return 2;
	case ' ': return 3;
	//与前面字母相接，不与后面字母相接的符号
	case ']': return 101;
	case ')': return 102;
	case '}': return 103;
	case ',': return 105;
	//与后面字母相接，不与前面字母相接的符号
	case '[': return 201;
	case '(': return 202;
	case '{': return 203;
	//与前后字母都不相接的符号
	case '&': return 301;
	case '-': return 302;
	//其他符号
	case '/': return 502;
	case '\\': return 503;
	case '\n': return 504;
	case '\0': return 505;
	default : ;
	}
	//数字判断
	if( tChar >= '0' && tChar <= '9' )
		return 0;
	//其他
	return -1;
}