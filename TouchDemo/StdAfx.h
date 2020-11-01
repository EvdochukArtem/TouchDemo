#pragma once

#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

#include <windows.h>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <tchar.h>

#define WM_UPDATE 0x0130
#define WIDTHPX (int)GetSystemMetrics(SM_CXSCREEN)
#define HEIGHTPX (int)GetSystemMetrics(SM_CYSCREEN)
#define MECHANIC_MENU_HEIGHTPX (int)(GetSystemMetrics(SM_CYSCREEN)*0.04)
#undef TO_PIXEL
#define TO_PIXEL(a) (int)((a)*HEIGHTPX/1080.0)

#define DRAW_KIT (CUtil::Instance().getDrawKit())
#define DRAW_ENGINE (CUtil::Instance().getDrawEngine())
#define GESTURE_ENGINE (CUtil::Instance().getGestureEngine())
#define GESTURE_EMULATOR (CUtil::Instance().getGestureEngineEmulator())
#define EKRAN_HANDLER (CUtil::Instance().getEkranHandler())