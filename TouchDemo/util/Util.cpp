#include "StdAfx.h"
#include "util/Util.h"
#include <cassert>

bool CUtil::created = false;

CUtil& CUtil::Instance()
{
	static CUtil util;
	if (!CUtil::created)
		assert(util.Create());
	return util;
}

BOOL CUtil::Create()
{
	CUtil::created = true;

	if (!drawKit.Create())
	{
		CUtil::created = false;
		return FALSE;
	}

	if (!gestureEngine.Create())
	{
		CUtil::created = false;
		return FALSE;
	}

	if (!gestureEngineEmulator.Create())
	{
		CUtil::created = false;
		return FALSE;
	}

	if (!drawEngine.Create())
	{
		CUtil::created = false;
		return FALSE;
	}

	if (!EkranHandler.Create())
	{
		CUtil::created = false;
		return FALSE;
	}

	return TRUE;
}

POINT CUtil::Rotate(POINT &pts, float angle, int smx, int smy)
{
	POINT ret;

	ret.x = (int)(pts.x * cos(angle) - pts.y * sin(angle))+smx;
	ret.y = (int)(pts.x * sin(angle) + pts.y * cos(angle))+smy;

	return ret;
}

POINT CUtil::Rotate(int x, int y, float angle, int smx, int smy)
{
	POINT ret;

	ret.x = (int)(x * cos(angle) - y * sin(angle))+smx;
	ret.y = (int)(x * sin(angle) + y * cos(angle))+smy;

	return ret;
}