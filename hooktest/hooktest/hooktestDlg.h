
// hooktestDlg.h : ͷ�ļ�
//

#pragma once


// ChooktestDlg �Ի���
class ChooktestDlg : public CDialogEx
{
// ����
public:
	ChooktestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~ChooktestDlg();
// �Ի�������
	enum { IDD = IDD_HOOKTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HHOOK g_hKeyBoard;
	void sys_command(char* command);
};
