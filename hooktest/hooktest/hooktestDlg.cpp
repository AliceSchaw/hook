
// hooktestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "hooktest.h"
#include "hooktestDlg.h"
#include "afxdialogex.h"
#include "Hotkey.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include<fstream>
#include<iostream>
#include "HotKey.h"
#pragma comment(lib,"HotKey.lib")

using namespace std;

// ChooktestDlg �Ի���




ChooktestDlg::ChooktestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChooktestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChooktestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
ChooktestDlg::~ChooktestDlg()
{
	//file_input() ;
	upload_hook() ;
}

BEGIN_MESSAGE_MAP(ChooktestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// ChooktestDlg ��Ϣ�������

BOOL ChooktestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	load_hook(m_hWnd);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void ChooktestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR ChooktestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void ChooktestDlg::sys_command(char* command)
{
	if (command != NULL)
	{
		char* temp = new char[100] ;
		//sprintf(temp,"cmd.exe /c start E:\"HotKey"\"test.txt");
		sprintf(temp,"cmd.exe /c taskkill /im notepad.exe") ;
		sprintf(temp,"cmd.exe /c start %s",command) ;
		WinExec(temp,SW_HIDE) ;
		free(temp) ;
	}
}
