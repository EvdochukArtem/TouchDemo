#include "StdAfx.h"
#include "GestureEngine.h"
#include "KadrHandler.h"
#include "DrawEngine.h"

HINSTANCE hInst;
HWND hMainWnd;
PAINTSTRUCT ps;
HDC hdc;
TCHAR szClassName[] = L"TouchDemo Class";
TCHAR szTitle[] = L"Touch App Demo";
CGestureEngine gestureEngine;
CKadrHandler kadrHandler;
CDrawEngine drawEngine;
CDrawKit drawKit;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);