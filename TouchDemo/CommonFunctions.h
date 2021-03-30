#pragma once
#include <windows.h>
#include <string>
#include <tchar.h>

POINT Rotate(POINT &pts, double angle, int smx, int smy);
POINT Rotate(int x, int y, double angle, int smx, int smy);
void Rotate(long &resx, long &resy, double x, double y, double angle, long smx, long smy);