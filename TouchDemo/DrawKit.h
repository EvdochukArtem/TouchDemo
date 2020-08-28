#pragma once
#include "StdAfx.h"

#define MAX_COLOR		2

class CDrawKit
{
public:
	CDrawKit() {};
	~CDrawKit() {};
	
	static void	Prepare(){CleanUp();Init();};
	static void	Init();
	static void	CleanUp();

	static const COLORREF &GetWhiteColor(){return ActualColorWhite;};
	static const COLORREF &GetLightGreyColor(){return ActualColorLightGrey;};
	static const COLORREF &GetBlackColor(){return ActualColorBlack;};

	static HBRUSH	BlackBrush;
	static HBRUSH	WhiteBrush;
	static HBRUSH	LightGreyBrush;
	static HBRUSH   NullBrush;

	static HPEN		BlackPen;
	static HPEN		BlackPen2;

	static HFONT	Arial16;

private:
	static void		DeleteDrawKitObject(IN HGDIOBJ *Obj);
	static int		ColorInd;

	static const COLORREF	ColorsWhite[MAX_COLOR];
	static  COLORREF	ActualColorWhite;
	static const COLORREF	ColorsLightGrey[MAX_COLOR];
	static  COLORREF	ActualColorLightGrey;
	static const COLORREF	ColorsBlack[MAX_COLOR];
	static  COLORREF	ActualColorBlack;
};