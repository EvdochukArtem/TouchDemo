#pragma once

#define MAX_COLOR		2

class CDrawKit
{
public:	
	static void	Prepare(){CleanUp(); Create();};
	static void	CleanUp();

	static const COLORREF &GetBlackColor(){return ActualColorBlack;};
	static const COLORREF &GetWhiteColor(){return ActualColorWhite;};
	static const COLORREF &GetYellowColor() { return ActualColorYellow; };
	static const COLORREF &GetLightGreyColor(){return ActualColorLightGrey;};
	static const COLORREF &GetGreenColor() { return ActualColorGreen; };
	static const COLORREF &GetBlueColor() { return ActualColorBlue; };
	static const COLORREF &GetRedColor() { return ActualColorRed; };

	static HBRUSH	BlackBrush;
	static HBRUSH	WhiteBrush;
	static HBRUSH	YellowBrush;
	static HBRUSH	LightGreyBrush;
	static HBRUSH   NullBrush;

	static HPEN		BlackPen;
	static HPEN		BlackPen2;
	static HPEN		BluePen2;
	static HPEN		GreenPen2;
	static HPEN		RedPen2;

	static HFONT	Arial16;

private:
	CDrawKit() {};
	~CDrawKit() {};
	static BOOL	Create();

	friend class CUtil;

	static void		DeleteDrawKitObject(IN HGDIOBJ *Obj);
	static int		ColorInd;

	static const COLORREF	ColorsBlack[MAX_COLOR];
	static  COLORREF	ActualColorBlack;
	static const COLORREF	ColorsWhite[MAX_COLOR];
	static  COLORREF	ActualColorWhite;
	static const COLORREF	ColorsYellow[MAX_COLOR];
	static  COLORREF	ActualColorYellow;
	static const COLORREF	ColorsLightGrey[MAX_COLOR];	
	static  COLORREF	ActualColorLightGrey;
	static const COLORREF	ColorsGreen[MAX_COLOR];
	static  COLORREF	ActualColorGreen;
	static const COLORREF	ColorsBlue[MAX_COLOR];
	static  COLORREF	ActualColorBlue;
	static const COLORREF	ColorsRed[MAX_COLOR];
	static  COLORREF	ActualColorRed;
};