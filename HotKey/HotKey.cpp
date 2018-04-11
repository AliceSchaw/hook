#include "stdafx.h"
#include "HotKey.h"
#define _HOTKEY_ extern "C" __declspec(dllexport)

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
		LPKBDLLHOOKSTRUCT pKbStruct = (LPKBDLLHOOKSTRUCT)lParam;
         
		WORD Ctrl_Pressed = HIBYTE( GetAsyncKeyState( VK_CONTROL ) );
		WORD Alt_Pressed = HIBYTE( GetAsyncKeyState(VK_MENU) );
        /*if(wParam == WM_KEYUP){
			if(pKbStruct->vkCode>64&&pKbStruct->vkCode<91){
				PostMessage(g_hwnd,MSG_HAPPEN,(pKbStruct->vkCode)-65,lParam) ;
			}
		}*/
		if(pKbStruct->vkCode=='B'){
			if(Ctrl_Pressed && Alt_Pressed && (wParam == WM_KEYUP)){
				//WinExec(KILL_SERVICES_VBS, SW_SHOWMAXIMIZED);  
				//system(KILL_SERVICES_VBS);
				//system(START_SERVICES_VBS);
				restartService();
			}

		}
        //ÆÁ±Î Windows ÈÈ¼ü
        if(pKbStruct->vkCode == VK_LWIN || pKbStruct->vkCode == VK_RWIN)
        {
            return TRUE;
        }
         
        //ÆÁ±Î Ctrl + Esc ÈÈ¼ü
        if(pKbStruct->vkCode == VK_ESCAPE)
        {
            if( Ctrl_Pressed )
                return TRUE;
        }
         
        //ÆÁ±Î Alt + '` ~'
        if(pKbStruct->vkCode == VK_OEM_3)
        {
            if( Alt_Pressed )
                return TRUE;
        }
         
        //ÆÁ±Î Ctrl + Alt + Del
        if(pKbStruct->vkCode == VK_DELETE || pKbStruct->vkCode == VK_DECIMAL)
        {
            if(Ctrl_Pressed && Alt_Pressed)
                return TRUE;
        }
         
        //ÆÁ±Î Alt + Tab
        if(pKbStruct->vkCode == VK_TAB)
        {
            if( Alt_Pressed )
                return TRUE;
        }
         
        //ÆÁ±Î Alt + Esc
        if(pKbStruct->vkCode = VK_ESCAPE)
        {
            if( Alt_Pressed )
                return TRUE;
        }
        return 0; //»Øµ÷
}



_HOTKEY_ bool load_hook(HWND hwnd)
{
	g_hwnd = hwnd ;
	//g_hkeyboard = SetWindowsHookEx(WH_KEYBOARD,keyboard_proc,GetModuleHandle(TEXT("HotKey")),0);
	g_hlowKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL,Hotkey_Filter,GetModuleHandle(TEXT("HotKey")),0);
	//Òþ²Ø¿ªÊ¼²Ëµ¥
	//hideStartMenu();
	return true ;
}

_HOTKEY_ bool upload_hook()
{
	//UnhookWindowsHookEx(g_hkeyboard) ;
	UnhookWindowsHookEx(g_hlowKeyHook) ;
	return true ;
}