#pragma once
#define _HOTKEY_ extern "C" __declspec(dllimport)

#include <Windows.h>

#pragma data_seg("Segment")
HWND g_hwnd = NULL ;
HHOOK g_hkeyboard = NULL ;
#pragma comment(linker,"/section:Segment,rws")

#define MSG_HAPPEN WM_USER+1

_HOTKEY_ bool load_hook(HWND hwnd) ;
_HOTKEY_ bool upload_hook() ;
