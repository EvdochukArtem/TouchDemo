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
#include "CommonConstants.h"
#include "CommonFunctions.h"

#define WM_UPDATE 0x0130

#define DRAW_KIT (CUtil::Instance().GetDrawKit())
#define DRAW_ENGINE (CUtil::Instance().GetDrawEngine())
#define GESTURE_ENGINE (CUtil::Instance().GetGestureEngine())
#define GESTURE_EMULATOR (CUtil::Instance().GetGestureEngineEmulator())
#define EKRAN_HANDLER (CUtil::Instance().GetEkranHandler())

#define MIN(a,b)		( ((a) < (b)) ? (a) : (b) )
#define MAX(a,b)		( ((a) > (b)) ? (a) : (b) )
#define MIN_MAX(a,b,c)	( MIN( (MAX((a),(b))), (c)) )