#include "stdafx.h"
#include "HotKey.h"
#define _HOTKEY_ extern "C" __declspec(dllexport)


LRESULT CALLBACK keyboard_proc(
	int nCode,
	WPARAM wParam,
	LPARAM lParam)
{
	if (wParam == VK_ESCAPE)
	{
		SendMessage(g_hwnd,WM_CLOSE,0,0) ;
		UnhookWindowsHookEx(g_hkeyboard) ;
	}


	if (1==lParam>>29&1)
	{
		switch(wParam)
		{
		case 'A' : 
			PostMessage(g_hwnd,MSG_HAPPEN,0,lParam) ;
			break ;
		case 'B' :
			PostMessage(g_hwnd,MSG_HAPPEN,1,lParam) ;
			break ;
		case 'C' :
			PostMessage(g_hwnd,MSG_HAPPEN,2,lParam) ;
			break ;
		case 'D' :
			PostMessage(g_hwnd,MSG_HAPPEN,3,lParam) ;
			break ;
		case 'E' :
			PostMessage(g_hwnd,MSG_HAPPEN,4,lParam) ;
			break ;
		case 'F' :
			PostMessage(g_hwnd,MSG_HAPPEN,5,lParam) ;
			break ;
		case 'G' :
			PostMessage(g_hwnd,MSG_HAPPEN,6,lParam) ;
			break ;
		case 'H' :
			PostMessage(g_hwnd,MSG_HAPPEN,7,lParam) ;
			break ;
		case 'I' :
			PostMessage(g_hwnd,MSG_HAPPEN,8,lParam) ;
			break ;
		case 'J' :
			PostMessage(g_hwnd,MSG_HAPPEN,9,lParam) ;
			break ;
		case 'K' :
			PostMessage(g_hwnd,MSG_HAPPEN,10,lParam) ;
			break ;
		case 'L' :
			PostMessage(g_hwnd,MSG_HAPPEN,11,lParam) ;
			break ;
		case 'M' :
			PostMessage(g_hwnd,MSG_HAPPEN,12,lParam) ;
			break ;
		case 'N' :
			PostMessage(g_hwnd,MSG_HAPPEN,13,lParam) ;
			break ;
		case 'O' :
			PostMessage(g_hwnd,MSG_HAPPEN,14,lParam) ;
			break ;
		case 'P' :
			PostMessage(g_hwnd,MSG_HAPPEN,15,lParam) ;
			break ;
		case 'Q' :
			PostMessage(g_hwnd,MSG_HAPPEN,16,lParam) ;
			break ;
		case 'R' :
			PostMessage(g_hwnd,MSG_HAPPEN,17,lParam) ;
			break ;
		case 'S' :
			PostMessage(g_hwnd,MSG_HAPPEN,18,lParam) ;
			break ;
		case 'T' :
			PostMessage(g_hwnd,MSG_HAPPEN,19,lParam) ;
			break ;
		case 'U' :
			PostMessage(g_hwnd,MSG_HAPPEN,20,lParam) ;
			break ;
		case 'V' :
			PostMessage(g_hwnd,MSG_HAPPEN,21,lParam) ;
			break ;
		case 'W' :
			PostMessage(g_hwnd,MSG_HAPPEN,22,lParam) ;
			break ;
		case 'X' :
			PostMessage(g_hwnd,MSG_HAPPEN,23,lParam) ;
			break ;
		case 'Y' :
			PostMessage(g_hwnd,MSG_HAPPEN,24,lParam) ;
			break ;
		case 'Z' :
			PostMessage(g_hwnd,MSG_HAPPEN,25,lParam) ;
			break ;
		default:
			break ;
		}
	}

	return 0 ; 
}

LRESULT CALLBACK Hotkey_Filter(int nCode, WPARAM wParam, LPARAM lParam)
{
		LPKBDLLHOOKSTRUCT pKbStruct = (LPKBDLLHOOKSTRUCT)lParam;
         
		WORD Ctrl_Pressed = HIBYTE( GetAsyncKeyState( VK_CONTROL ) );
		WORD Alt_Pressed = HIBYTE( GetAsyncKeyState(VK_MENU) );
        if(wParam == WM_KEYUP){
			if(pKbStruct->vkCode>64&&pKbStruct->vkCode<91){
				PostMessage(g_hwnd,MSG_HAPPEN,(pKbStruct->vkCode)-65,lParam) ;
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
	return true ;
}

_HOTKEY_ bool upload_hook()
{
	//UnhookWindowsHookEx(g_hkeyboard) ;
	UnhookWindowsHookEx(g_hlowKeyHook) ;
	return true ;
}