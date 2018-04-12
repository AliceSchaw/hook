#pragma once
#define _HOTKEY_ extern "C" __declspec(dllimport)

#include <Windows.h>
#include "stdlib.h"
#include <shellapi.h>
#include <tchar.h>
#pragma data_seg("Segment")
HWND g_hwnd = NULL ;
HHOOK g_hkeyboard = NULL ;
HHOOK g_hlowKeyHook = NULL;     //µÍ¼¶¼üÅÌ¹³×Ó¾ä±ú  
#pragma comment(linker,"/section:Segment,rws")

#define MSG_HAPPEN WM_USER+1
#define KILL_SERVICES_VBS _T("D:\\sys\\SasetC51UI_KillServicecs.vbs")
#define START_SERVICES_VBS _T("D:\\sys\\SasetC51UI_StartServicecs.vbs")
#define COPY_SERVICES_VBS _T("D:\\sys\\SasetC51UI_CopyFolder.vbs")
#define START_TASK_VBS _T("D:\\sys\\StartTask.vbs")
#define SRC_FILES_FOLDER_DIR _T("E:\\HotKey\\TEST")
#define DST_FILES_FOLDER_DIR _T("D:\\sys\\TEST")
_HOTKEY_ bool load_hook(HWND hwnd) ;
_HOTKEY_ bool upload_hook() ;
