// MyMusicDlg.cpp : \u5B9E\u73B0\u6587\u4EF6
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


// \u7528\u4E8E\u5E94\u7528\u7A0B\u5E8F\u201C\u5173\u4E8E\u201D\u83DC\u5355\u9879\u7684 CAboutDlg \u5BF9\u8BDD\u6846

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// \u5BF9\u8BDD\u6846\u6570\u636E
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV \u652F\u6301

// \u5B9E\u73B0
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


// CMyMusicDlg \u5BF9\u8BDD\u6846




CMyMusicDlg::CMyMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyMusicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_group_name = _T("");
	//  m_Artist = _T("");
	m_artist = _T("");
	m_type = _T("");
	m_instruction = _T("");
}

void CMyMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_group_name);
	//  DDX_Text(pDX, IDC_EDIT2, m_Artist);
	DDX_Text(pDX, IDC_EDIT2, m_artist);
	//  DDX_Control(pDX, IDC_EDIT3, m_type);
	DDX_Text(pDX, IDC_EDIT3, m_type);
	DDX_Text(pDX, IDC_EDIT4, m_instruction);
}

BEGIN_MESSAGE_MAP(CMyMusicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyMusicDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyMusicDlg \u6D88\u606F\u5904\u7406\u7A0B\u5E8F

BOOL CMyMusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// \u5C06\u201C\u5173\u4E8E...\u201D\u83DC\u5355\u9879\u6DFB\u52A0\u5230\u7CFB\u7EDF\u83DC\u5355\u4E2D\u3002

	// IDM_ABOUTBOX \u5FC5\u987B\u5728\u7CFB\u7EDF\u547D\u4EE4\u8303\u56F4\u5185\u3002
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

	// \u8BBE\u7F6E\u6B64\u5BF9\u8BDD\u6846\u7684\u56FE\u6807\u3002\u5F53\u5E94\u7528\u7A0B\u5E8F\u4E3B\u7A97\u53E3\u4E0D\u662F\u5BF9\u8BDD\u6846\u65F6\uFF0C\u6846\u67B6\u5C06\u81EA\u52A8
	//  \u6267\u884C\u6B64\u64CD\u4F5C
	SetIcon(m_hIcon, TRUE);			// \u8BBE\u7F6E\u5927\u56FE\u6807
	SetIcon(m_hIcon, FALSE);		// \u8BBE\u7F6E\u5C0F\u56FE\u6807

	// TODO: \u5728\u6B64\u6DFB\u52A0\u989D\u5916\u7684\u521D\u59CB\u5316\u4EE3\u7801
	m_instruction = Instruction();
	UpdateData(FALSE);

	return TRUE;  // \u9664\u975E\u5C06\u7126\u70B9\u8BBE\u7F6E\u5230\u63A7\u4EF6\uFF0C\u5426\u5219\u8FD4\u56DE TRUE
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

// \u5982\u679C\u5411\u5BF9\u8BDD\u6846\u6DFB\u52A0\u6700\u5C0F\u5316\u6309\u94AE\uFF0C\u5219\u9700\u8981\u4E0B\u9762\u7684\u4EE3\u7801
//  \u6765\u7ED8\u5236\u8BE5\u56FE\u6807\u3002\u5BF9\u4E8E\u4F7F\u7528\u6587\u6863/\u89C6\u56FE\u6A21\u578B\u7684 MFC \u5E94\u7528\u7A0B\u5E8F\uFF0C
//  \u8FD9\u5C06\u7531\u6846\u67B6\u81EA\u52A8\u5B8C\u6210\u3002

void CMyMusicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // \u7528\u4E8E\u7ED8\u5236\u7684\u8BBE\u5907\u4E0A\u4E0B\u6587

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// \u4F7F\u56FE\u6807\u5728\u5DE5\u4F5C\u533A\u77E9\u5F62\u4E2D\u5C45\u4E2D
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// \u7ED8\u5236\u56FE\u6807
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//\u5F53\u7528\u6237\u62D6\u52A8\u6700\u5C0F\u5316\u7A97\u53E3\u65F6\u7CFB\u7EDF\u8C03\u7528\u6B64\u51FD\u6570\u53D6\u5F97\u5149\u6807
//\u663E\u793A\u3002
HCURSOR CMyMusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyMusicDlg::OnBnClickedOk()
{
	/*CString csName1;
	CString csName2;
	CString csDir;
	CString csResult;
	CString csTemp;
	csName1.Format(_T(".00_._Britney_ Spears-Femme_Fatale(Deluxe_Edition)[..].mp3"));
	csName2.Format(_T(".Hans Zimmer & Lorne Balfe -.. The Bible-OST www.tori.com(2013)..."));
	csName2.Format(_T("Backstreet.Boys.-.[Black.&.Blue(2000)].\u4E13\u8F91.(WAV)"));
	csName2.Format(_T("Backstreet.Boys.-.[Black.&.Blue EP .. (2000).(WAV)"));
	csName2.Format(_T("Angelight.-.[\u0421\u0435\u0430\u043D\u0441\u044B.\u0438\u0441\u0446\u0435\u043B\u044F\u044E\u0449\u0435\u0439_\u043C\u0443\u0437\u044B\u043A\u0438.(1-\u044B\u0439.\u0441\u0435\u0430\u043D\u0441)].\u4E13\u8F91.[FLAC"));
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
	//csName.Format(_T("Above.&.Beyond.-.[Tri.State.2008.Remix.Edition.(Limited.Edition)].\u4E13\u8F91.(MP3)"));
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
	//csName.Format(_T("C:\\Users\\jhc888007\\Desktop\\C++\\My_Music\\My_Music_Compete\\John_Williams_Complete\\John.Williams.-.[Indiana.Jones.The.Soundtracks.Collection.(2008)].\u4E13\u8F91.(FLAC)\\CD4.-.Indiana.Jones.And.The.Kingdom.Of.The.Crystal.Skull\\dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd.txtx"));
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
		if( BST_UNCHECKED == ( (CButton *)GetDlgItem( IDC_SPECIAL_CHECK ) )->GetCheck() )
		{
			if( BST_CHECKED == ( (CButton *)GetDlgItem( IDC_CHECK_BOX ) )->GetCheck() )
				RenameAfterCheck( m_group_name, m_artist, 1, m_type );
			else
				RenameAfterCheck( m_group_name, m_artist, 0, m_type );
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
