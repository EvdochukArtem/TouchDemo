#include "StdAfx.h"
#include "util/Util.h"

CUtil& CUtil::Instance()
{
	static CUtil util;
	return util;
}

BOOL CUtil::Create()
{

	if (!drawKit.Create())
		return FALSE;

	if (!gestureEngine.Create())
		return FALSE;

	if (!gestureEngineEmulator.Create())
		return FALSE;

	if (!drawEngine.Create())
		return FALSE;

	if (!ekranHandler.Create())
		return FALSE;

	return TRUE;
}

BOOL CUtil::CleanUp()
{
	if (!drawKit.CleanUp())
		return FALSE;

	if (!gestureEngine.CleanUp())
		return FALSE;

	if (!gestureEngineEmulator.CleanUp())
		return FALSE;

	if (!drawEngine.CleanUp())
		return FALSE;

	if (!ekranHandler.CleanUp())
		return FALSE;

	return TRUE;
}