
// MyMusicDlg.h : 头文件
//

#pragma once


// CMyMusicDlg 对话框
class CMyMusicDlg : public CDialogEx
{
// 构造
public:
	CMyMusicDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYMUSIC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
//	CString m_type;
	CString m_instruction;
	CString m_delete;
};
