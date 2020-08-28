#include <windows.h>
#include <math.h>

#define WM_UPDATE 0x0130
#define WIDTHPX (int)GetSystemMetrics(SM_CXSCREEN) - GetSystemMetrics(SM_CXFRAME)
#define HEIGHTPX (int)GetSystemMetrics(SM_CYSCREEN) - GetSystemMetrics(SM_CYCAPTION) - GetSystemMetrics(SM_CYFRAME) 