#include "stdafx.h"
#include "HotKey.h"
#define _HOTKEY_ extern "C" __declspec(dllexport)
#define KILL_SERVICES_VBS _T("D:\\sys\\SasetC51UI_KillServicecs.vbs")
#define START_SERVICES_VBS _T("D:\\sys\\SasetC51UI_StartServicecs.vbs")

void hideStartMenu(){
	HWND hWnd = FindWindow(L"Shell_TrayWnd",NULL);  
	HWND hStar =FindWindowEx(NULL,NULL,L"Button",NULL);

	ShowWindow(hWnd,SW_HIDE);
	ShowWindow(hStar,SW_HIDE);
}

void ExVBSCmd(LPCWSTR cmd_line) {
	SHELLEXECUTEINFO shei;
	shei.cbSize = sizeof(shei);
	shei.fMask = SEE_MASK_INVOKEIDLIST;
	shei.lpFile = cmd_line ;
	shei.lpVerb = _T("open");
	ShellExecute(NULL,shei.lpVerb, shei.lpFile, _T(""), _T(""), SW_HIDE);
}
void restartService(){
	ExVBSCmd(KILL_SERVICES_VBS);
	ExVBSCmd(START_SERVICES_VBS);
}
LRESULT CALLBACK Hotkey_Filter(int nCode, WPARAM wParam, LPARAM lParam)
{
	bool isClick = false;  
    PKBDLLHOOKSTRUCT LowKey = NULL;   //�ýṹ������ײ���������¼�����Ϣ  
         
		WORD Ctrl_Pressed = HIBYTE( GetAsyncKeyState( VK_CONTROL ) );
		WORD Alt_Pressed = HIBYTE( GetAsyncKeyState(VK_MENU) ); 
    if (nCode == HC_ACTION)      //HC_ACTION  ��ʾ����Ϣ  
    {  
        LowKey = (PKBDLLHOOKSTRUCT)lParam;  
        switch (wParam)  
        {  
        case WM_KEYDOWN:  
        case WM_SYSKEYDOWN:  
        case WM_KEYUP: {
			if(LowKey->vkCode=='R'){
				if (Ctrl_Pressed && Alt_Pressed ){
					isClick = 1; 
					//WinExec(KILL_SERVICES_VBS, SW_SHOWMAXIMIZED);  
					//system(KILL_SERVICES_VBS);
					//system(START_SERVICES_VBS);
					restartService();
					   
				}
			}
			if(LowKey->vkCode=='F'){
				if(Ctrl_Pressed && Alt_Pressed ){
					isClick = 1; 
					if(GetFileAttributes(KILL_SERVICES_VBS)<0)//==-1
					{
						//�ļ������ڣ�
					}
					else{
						//����
					}
				}
			}
			break;
		}
        case WM_SYSKEYUP:  
            {       // ����Win  
                isClick = (LowKey->vkCode == VK_LWIN) || (LowKey->vkCode == VK_RWIN) ||    
                    // ����Alt+F4  
                    ((LowKey->vkCode == VK_F4) && ((LowKey->flags & LLKHF_ALTDOWN) != 0)) ||  
                    // ����Alt+Tab  
                    ((LowKey->vkCode == VK_TAB) && ((LowKey->flags & LLKHF_ALTDOWN) != 0)) ||  
                    // ����Alt+Esc  
                    ((LowKey->vkCode == VK_ESCAPE) && ((LowKey->flags & LLKHF_ALTDOWN) != 0)) ||  
                    // ����Ctrl+Esc  
                    ((LowKey->vkCode == VK_ESCAPE) && (Ctrl_Pressed != 0))||
					// ����Alt+~`
					((LowKey->vkCode == VK_OEM_3) && (Alt_Pressed != 0));  
                break;  
            }  
        default:  
            break;  
        }  
    }  
    if (isClick)  
    {  
        return 1;  
    }  
    return CallNextHookEx(g_hlowKeyHook,nCode,wParam,lParam);  //������һ������  
}



_HOTKEY_ bool load_hook(HWND hwnd)
{
	g_hwnd = hwnd ;
	//g_hkeyboard = SetWindowsHookEx(WH_KEYBOARD,keyboard_proc,GetModuleHandle(TEXT("HotKey")),0);
	g_hlowKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL,Hotkey_Filter,GetModuleHandle(TEXT("HotKey")),0);
	//���ؿ�ʼ�˵�
	//hideStartMenu();
	return true ;
}

_HOTKEY_ bool upload_hook()
{
	//UnhookWindowsHookEx(g_hkeyboard) ;
	UnhookWindowsHookEx(g_hlowKeyHook) ;
	return true ;
}