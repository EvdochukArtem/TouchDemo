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
