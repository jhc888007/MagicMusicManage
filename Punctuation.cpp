#include "stdafx.h"



int PunctuationCheckType( TCHAR tChar )
{
	//\u7B26\u53F7\u5224\u65AD
	switch( tChar )
	{
	//\u524D\u540E\u5B57\u6BCD\u90FD\u76F8\u63A5
	case '.': return 1;
	case '_': return 2;
	case ' ': return 3;
	//\u4E0E\u524D\u9762\u5B57\u6BCD\u76F8\u63A5\uFF0C\u4E0D\u4E0E\u540E\u9762\u5B57\u6BCD\u76F8\u63A5\u7684\u7B26\u53F7
	case ']': return 101;
	case ')': return 102;
	case '}': return 103;
	case ',': return 105;
	//\u4E0E\u540E\u9762\u5B57\u6BCD\u76F8\u63A5\uFF0C\u4E0D\u4E0E\u524D\u9762\u5B57\u6BCD\u76F8\u63A5\u7684\u7B26\u53F7
	case '[': return 201;
	case '(': return 202;
	case '{': return 203;
	//\u4E0E\u524D\u540E\u5B57\u6BCD\u90FD\u4E0D\u76F8\u63A5\u7684\u7B26\u53F7
	case '&': return 301;
	case '-': return 302;
	//\u5176\u4ED6\u7B26\u53F7
	case '/': return 502;
	case '\\': return 503;
	case '\n': return 504;
	case '\0': return 505;
	default : ;
	}
	//\u6570\u5B57\u5224\u65AD
	if( tChar >= '0' && tChar <= '9' )
		return 0;
	//\u5176\u4ED6
	return -1;
}