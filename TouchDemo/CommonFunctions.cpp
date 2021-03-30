#include "StdAfx.h"
#include <assert.h>
#include "CommonFunctions.h"
#include <locale>

const double ToDegree	= 180. / PI;

const TCHAR tchGradeSymbol = TCHAR(0xB0);

const float zeroX = 5000000.f; // Начало координат
const float zeroZ = 6600000.f;

// Данные для пересчёта координат из прямоугольных в геодезические
const float centerX = 11123000.f - zeroX;
const float centerZ =  6900000.f - zeroZ;

const float pnSxW_X = 4453608.57f - zeroX;
const float pnSxW_Z = 5876893.72f - zeroZ;

const float pnNxW_X = 5312358.31f - zeroX; 
const float pnNxW_Z = 5812349.53f - zeroZ;

const float pnSxE_X = 44735608.57f - zeroX;
const float pnSxE_Z = 7278906.20f - zeroZ;

const float pnNxE_X = 5351258.31f - zeroX; 
const float pnNxE_Z = 7176850.00f - zeroZ;

// расстояния от центра окружности до широт 48 и 40 гр
const double lenNorth = sqrt((pnNxW_X-centerX)*(pnNxW_X-centerX) + (pnNxW_Z-centerZ)*(pnNxW_Z-centerZ));
const double lenSouth = sqrt((pnSxW_X-centerX)*(pnSxW_X-centerX) + (pnSxW_Z-centerZ)*(pnSxW_Z-centerZ));
const double lenN_S = lenSouth - lenNorth;

const double RealAngleMaxLongitude = atan (((double)pnSxW_Z - centerZ)/(pnSxW_X - centerX)) * 180.f / PI;
const float EndWest = 26.f;
const float EndEast = 46.f;
const float EndNorth = 46.f;
const float EndSouth = 46.f;
const float MiddleLongitude = (EndWest + EndEast) / 2;
const float ToLengthN_S = (float)((EndNorth - EndSouth) / lenN_S);
const double ToAngleW_E = (MiddleLongitude - EndWest) / RealAngleMaxLongitude;

POINT Rotate(POINT &pts, double angle, int smx, int smy)
{
	POINT ret;

	ret.x = (int)(pts.x * cos(angle) - pts.y * sin(angle))+smx;
	ret.y = (int)(pts.x * sin(angle) + pts.y * cos(angle))+smy;

	return ret;
}

POINT Rotate(int x, int y, double angle, int smx, int smy)
{
	POINT ret;

	ret.x = (int)(x * cos(angle) - y * sin(angle))+smx;
	ret.y = (int)(x * sin(angle) + y * cos(angle))+smy;

	return ret;
}

void Rotate(long &resx, long &resy, double x, double y, double angle, long smx, long smy)
{
	resx = (long)(x * cos(angle) - y * sin(angle))+smx;
	resy = (long)(x * sin(angle) + y * cos(angle))+smy;
}