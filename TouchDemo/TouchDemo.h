#pragma once

HINSTANCE hInst;
HWND MFIWindow;
PAINTSTRUCT ps;
HDC hdc;
TCHAR szClassName[] = L"TouchDemo Class";
TCHAR szTitle[] = L"Touch App Demo";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);