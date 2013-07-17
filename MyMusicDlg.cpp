
// MyMusicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyMusic.h"
#include "MyMusicDlg.h"
#include "afxdialogex.h"

#include "Word.h"
#include "Punctuation.h"
#include "WordCheck.h"
#include "PunctuationDeal.h"
#include "MusicGroupRename.h"
#include "MusicFileRename.h"
#include "File.h"
#include "Rename.h"
#include "FileArrange.h"
#include "Arrange.h"
#include "GroupArrange.h"
#include "CommonGroupRename.h"
#include "Instruction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyMusicDlg 对话框




CMyMusicDlg::CMyMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyMusicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_group_name = _T("");
	//  m_Artist = _T("");
	m_artist = _T("");
	//  m_type = _T("");
	m_instruction = _T("");
	m_delete = _T("");
}

void CMyMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_group_name);
	//  DDX_Text(pDX, IDC_EDIT2, m_Artist);
	DDX_Text(pDX, IDC_EDIT2, m_artist);
	//  DDX_Control(pDX, IDC_EDIT3, m_type);
	//  DDX_Text(pDX, IDC_EDIT3, m_type);
	DDX_Text(pDX, IDC_EDIT4, m_instruction);
	DDX_Text(pDX, IDC_EDIT3, m_delete);
}

BEGIN_MESSAGE_MAP(CMyMusicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyMusicDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyMusicDlg 消息处理程序

BOOL CMyMusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_instruction = Instruction();
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyMusicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyMusicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyMusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



CString g_delete;



void CMyMusicDlg::OnBnClickedOk()
{
	/*CString csName1;
	CString csName2;
	CString csDir;
	CString csResult;
	CString csTemp;
	csName1.Format(_T(".00_._Britney_ Spears-Femme_Fatale(Deluxe_Edition)[..].mp3"));
	csName2.Format(_T(".Hans Zimmer & Lorne Balfe -.. The Bible-OST www.tori.com(2013)..."));
	csName2.Format(_T("Backstreet.Boys.-.[Black.&.Blue(2000)].专辑.(WAV)"));
	csName2.Format(_T("Backstreet.Boys.-.[Black.&.Blue EP .. (2000).(WAV)"));
	csName2.Format(_T("Angelight.-.[Сеансы.исцеляющей_музыки.(1-ый.сеанс)].专辑.[FLAC"));
	csResult = MusicGroupRename( csName2, _T(""), _T(""), _T("") );
	csResult = MusicFileRename( csName1 );*/
	//FileCheckAndRename(_T("C:\\Users\\jhc888007\\Desktop\\2"));
	//rename( "C:\\Users\\jhc888007\\Desktop\\C++\\Test\\TyDi - Remixeddsd",
	//	"C:\\Users\\jhc888007\\Desktop\\C++\\Test\\TyDi - Remixeddsdwe" );
	//MessageBox((LPCTSTR)csResult,0,0 );
	//rename( "C:\\Users\\jhc888007\\Desktop\\C++\\Test\\The Best Of - Celine Dion David Foster",
	//	"C:\\Users\\jhc888007\\Desktop\\C++\\Test\\The Best.Ofcc - Celine Dion David Foster" );
	//MessageBox(_T("a"),0,0 );

	//CString csName;
	//CString csName1;
	//CString csName2;
	//CString csResult;
	//csName.Format(_T(".00_._Britney_ Spears-Femme_Fatale(Deluxe_Edition)[..].mp3"));
	//csName.Format(_T("Above.&.Beyond.-.[Tri.State.2008.Remix.Edition.(Limited.Edition)].专辑.(MP3)"));
	//csResult = WordCheckTitle( csName );
	//csResult = FileArrangeGetSuffix( csName );
	//csName1.Format( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test\\01 Cu_Chullain.mp3") );
	//csName2.Format( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test\\ABC - Oh my love (2012)\\01 Cu_Chullain.mp3") );
	//MoveFile( csName2, csName1 );
	//MessageBox((LPCTSTR)csResult,0,0 );
	//csName1.Format( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test\\TyDi.-.[Remixed].EP.(APE)") );
	//ArrangeSortGroup( csName1, csName1 );
	//csName1.Format( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test\\TyDi - Remixed EP") );
	//ArrangeSortGroup( csName1, csName1, _T("_Lyrics"), _T("_Covers"), _T("_Logs"), _T("_Extra"));
	//GroupArrangeMake( csName1, _T("_Lyrics"), _T("_Covers"), _T("_Logs"), _T("_Extra"));
	//ArrangeSortGroup( csName1, csName1, _T("_Lyrics"), _T("_Covers"), _T("_Logs"), _T("_Extra"));
	//GroupArrangeDelete( csName1 );
	//GroupArrangeRename( csName1, _T("_Lyrics"), _T("_Covers"), _T("_Logs"), _T("_Extra"),
	//	_T("Lyrics"), _T("Covers"), _T("Logs"), _T("Extra") );
	//ArrangeMusicGroup( csName1 );

	//int nResult = WordFind( _T("Log.log"), _T("ogg") );
	//CString csTemp;
	//csTemp.Format( _T("%d"), nResult );
	//MessageBox((LPCTSTR)csTemp,0,0 );

	//CString csName;
	//csName.Format(_T("C:\\Users\\jhc888007\\Desktop\\C++\\My_Music\\My_Music_Compete\\John_Williams_Complete\\John.Williams.-.[Indiana.Jones.The.Soundtracks.Collection.(2008)].专辑.(FLAC)\\CD4.-.Indiana.Jones.And.The.Kingdom.Of.The.Crystal.Skull\\dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd.txtx"));
	//csName = WordCheckLen( csName, 4 );

	/*CStdioFile fSongList;
	CString csSongList;
	csSongList.Format( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test1.txt") );
	fSongList.Open( csSongList, CFile::modeWrite|CFile::modeCreate );
	fSongList.WriteString( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test1.txt" ) );
	fSongList.WriteString( _T("\n" ) );
	fSongList.WriteString( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test1.txt" ) );
	fSongList.WriteString( _T("\n" ) );
	fSongList.WriteString( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test1.txt" ) );
	fSongList.WriteString( _T("\n" ) );
	fSongList.Close();*/

	/*int nCount;
	for( nCount = 0; nCount < 10; nCount++ )
	{
		switch( nCount )
		{
		case 0:
			nCount++;
			continue;
			break;
		case 2:
			nCount++;
			break;
		default:
			break;
		}
	}*/

	/*CFileFind cFile;
	CFileFind *pcFile = &cFile;
	BOOL b;
	CString csTemp;
	b = pcFile->FindFile( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test\\ABC - Oh my love (2012)\\*") );
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();
	b = pcFile->FindNextFile();
	csTemp = pcFile->GetFileName();*/

	/*CString csTemp;
	csTemp.Format( _T("C:\\Users\\jhc888007\\Desktop\\C++\\Test\\Thumbs.db") );
	DeleteFile( csTemp );*/

	/*CString csTemp;
	csTemp.Format( _T("asdfcco") );
	csTemp = FileArrangeGetPrefix( csTemp );*/

	UpdateData(TRUE);
	if( m_group_name.Compare( _T("") ) != 0 )
	{
		g_delete.Format( m_delete );
		if( BST_UNCHECKED == ( (CButton *)GetDlgItem( IDC_SPECIAL_CHECK ) )->GetCheck() )
		{
			if( BST_CHECKED == ( (CButton *)GetDlgItem( IDC_CHECK_BOX ) )->GetCheck() )
				RenameAfterCheck( m_group_name, m_artist, 1, _T("") );
			else
				RenameAfterCheck( m_group_name, m_artist, 0, _T(""));
		}
		else
		{
			RenameInGroup( m_group_name );
		}
		MessageBox( _T("Optimize Successful!"), _T("Thank You For Using!"), 0 );
	}
	else
		MessageBox( _T("Please Enter A Directory!"), _T("Thank You For Using!"), 0 );
}
