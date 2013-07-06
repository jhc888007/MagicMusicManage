// MyMusic.h : PROJECT_NAME \u5E94\u7528\u7A0B\u5E8F\u7684\u4E3B\u5934\u6587\u4EF6
//

#pragma once

#ifndef __AFXWIN_H__
	#error "\u5728\u5305\u542B\u6B64\u6587\u4EF6\u4E4B\u524D\u5305\u542B\u201Cstdafx.h\u201D\u4EE5\u751F\u6210 PCH \u6587\u4EF6"
#endif

#include "resource.h"		// \u4E3B\u7B26\u53F7


// CMyMusicApp:
// \u6709\u5173\u6B64\u7C7B\u7684\u5B9E\u73B0\uFF0C\u8BF7\u53C2\u9605 MyMusic.cpp
//

class CMyMusicApp : public CWinApp
{
public:
	CMyMusicApp();

// \u91CD\u5199
public:
	virtual BOOL InitInstance();

// \u5B9E\u73B0

	DECLARE_MESSAGE_MAP()
};

extern CMyMusicApp theApp;