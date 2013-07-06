// MyMusicDlg.h : \u5934\u6587\u4EF6
//

#pragma once


// CMyMusicDlg \u5BF9\u8BDD\u6846
class CMyMusicDlg : public CDialogEx
{
// \u6784\u9020
public:
	CMyMusicDlg(CWnd* pParent = NULL);	// \u6807\u51C6\u6784\u9020\u51FD\u6570

// \u5BF9\u8BDD\u6846\u6570\u636E
	enum { IDD = IDD_MYMUSIC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV \u652F\u6301


// \u5B9E\u73B0
protected:
	HICON m_hIcon;

	// \u751F\u6210\u7684\u6D88\u606F\u6620\u5C04\u51FD\u6570
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_group_name;
//	CString m_Artist;
	CString m_artist;
//	CEdit m_type;
	CString m_type;
	CString m_instruction;
};
