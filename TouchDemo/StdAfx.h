#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <process.h>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <TCHAR.H>

#define WM_UPDATE 0x0130
#define WIDTHPX (int)GetSystemMetrics(SM_CXSCREEN)// - GetSystemMetrics(SM_CXFRAME)
#define HEIGHTPX (int)GetSystemMetrics(SM_CYSCREEN)// - GetSystemMetrics(SM_CYCAPTION) - GetSystemMetrics(SM_CYFRAME)
#define MECHANIC_MENU_HEIGHTPX (int)(GetSystemMetrics(SM_CYSCREEN)*0.04)
#define TO_PIXEL(a) (int)((a)*HEIGHTPX/1080.0)

#define DRAW_KIT CUtil::Instance().getDrawKit()
#define DRAW_ENGINE CUtil::Instance().getDrawEngine()
#define GESTURE_ENGINE CUtil::Instance().getGestureEngine()
#define GESTURE_EMULATOR CUtil::Instance().getGestureEngineEmulator()
#define EKRAN_HANDLER CUtil::Instance().getEkranHandler()