
// hooktestDlg.h : 头文件
//

#pragma once


// ChooktestDlg 对话框
class ChooktestDlg : public CDialogEx
{
// 构造
public:
	ChooktestDlg(CWnd* pParent = NULL);	// 标准构造函数
	~ChooktestDlg();
// 对话框数据
	enum { IDD = IDD_HOOKTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HHOOK g_hKeyBoard;
	void sys_command(char* command);
};
