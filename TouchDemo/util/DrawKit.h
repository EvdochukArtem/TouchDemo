#pragma once

#define MAX_COLOR		2

class CDrawKit
{
public:

	static void	Prepare(){CleanUp();Create();};
	static void	CleanUp();
	static const COLORREF &GetWhiteColor(){return ActualColorWhite;};
	static const COLORREF &GetBlueColor(){return ActualColorBlue;};
	static const COLORREF &GetRedColor(){return ActualColorRed;};
	static const COLORREF &GetOrangeColor(){return ActualColorOrange;};
	static const COLORREF &GetGreenColor(){return ActualColorGreen;};
	static const COLORREF &GetYellowColor(){return ActualColorYellow;};
	static const COLORREF &GetGreyColor(){return ActualColorGrey;};
	static const COLORREF &GetLightGreyColor(){return ActualColorLightGrey;};
	static const COLORREF &GetBlackColor(){return ActualColorBlack;};

	static HBRUSH	BlackBrush;
	static HBRUSH	WhiteBrush;
	static HBRUSH	YellowBrush;
	static HBRUSH	RedBrush;
	static HBRUSH	OrangeBrush;
	static HBRUSH	GreenBrush;
	static HBRUSH	BlueBrush;
	static HBRUSH	GreyBrush;
	static HBRUSH	LightGreyBrush;
	static HBRUSH   NullBrush;

	static HPEN		BluePen;
	static HPEN		BluePen2;
	static HPEN		YellowPen;
	static HPEN		YellowPen2;
	static HPEN		YellowPen3;
	static HPEN		RedPen;
	static HPEN		RedPen2;
    static HPEN		RedPen3;
	static HPEN		WhitePen;
	static HPEN		WhitePen2;
	static HPEN		WhitePen3;
	static HPEN		OrangePen;
	static HPEN		OrangePen2;
	static HPEN		OrangePen3;
	static HPEN		BlackPen;
	static HPEN		BlackPen2;
	static HPEN     BlackPen3;
	static HPEN		GreenPen;
	static HPEN		GreenPen2;
	static HPEN		GreenPen3;
	static HPEN		GreyPen;
    static HPEN		GreyPen2;
    static HPEN		GreyPen3;
	
	static HFONT	BorderFont;
	static HFONT	Arial16;
	static HFONT	Arial13;
	static HFONT	Arial12;

private:
	CDrawKit() {};
	~CDrawKit() {};
	static BOOL	Create();
	friend class CUtil; 

	static void		SwapColorInd(){ColorInd^=0x0001;};
	static void		DeleteDrawKitObject(IN HGDIOBJ *Obj);
	static int		ColorInd;

	static const COLORREF	ColorsWhite[MAX_COLOR];
	static  COLORREF	ActualColorWhite;
	static const COLORREF	ColorsYellow[MAX_COLOR];
	static  COLORREF	ActualColorYellow;
	static const COLORREF	ColorsGreen[MAX_COLOR];
	static  COLORREF	ActualColorGreen;
	static const COLORREF	ColorsBlue[MAX_COLOR];
	static  COLORREF	ActualColorBlue;
	static const COLORREF	ColorsOrange[MAX_COLOR];
	static  COLORREF	ActualColorOrange;
	static const COLORREF	ColorsGrey[MAX_COLOR];
	static  COLORREF	ActualColorGrey;
	static const COLORREF	ColorsLightGrey[MAX_COLOR];
	static  COLORREF	ActualColorLightGrey;
	static const COLORREF	ColorsBlack[MAX_COLOR];
	static  COLORREF	ActualColorBlack;
	static const COLORREF	ColorsRed[MAX_COLOR];
	static  COLORREF	ActualColorRed;
};