#pragma once

#define MAX_COLOR		2

class CDrawKit
{
public:
	
	static void	Prepare(){CleanUp();Create();};
	static void	CleanUp();

	static const COLORREF &GetWhiteColor(){return ActualColorWhite;};
	static const COLORREF &GetBackgroundColor(){return ActualColorBackground;};
	static const COLORREF &GetBlueColor(){return ActualColorBlue;};
    static const COLORREF &GetLightCyanColor(){return ActualColorLightCyan;};
	static const COLORREF &GetRedColor(){return ActualColorRed;};
	static const COLORREF &GetDarkRedColor(){return ActualColorDarkRed;};
    static const COLORREF &GetLightOrangeColor(){return ActualColorLightOrange;};
	static const COLORREF &GetOrangeColor(){return ActualColorOrange;};
	static const COLORREF &GetDarkOrangeColor(){return ActualColorDarkOrange;};
	static const COLORREF &GetGreenColor(){return ActualColorGreen;};
	static const COLORREF &GetDarkGreenColor(){return ActualColorDarkGreen;};
	static const COLORREF &GetYellowColor(){return ActualColorYellow;};
	static const COLORREF &GetLightYellowColor(){return ActualColorLightYellow;};
	static const COLORREF &GetDarkYellowColor(){return ActualColorDarkYellow;};
	static const COLORREF &GetLightBlueColor(){return ActualColorLightBlue;};
	static const COLORREF &GetDarkBlueColor(){return ActualColorDarkBlue;};
	static const COLORREF &GetDarkBrownColor(){return ActualColorDarkBrown;};
	static const COLORREF &GetLightBrownColor(){return ActualColorLightBrown;};
	static const COLORREF &GetDarkGreyColor(){return ActualColorDarkGrey;};
	static const COLORREF &GetGreyColor(){return ActualColorGrey;};
	static const COLORREF &GetPurpleColor(){return ActualColorPurple;};
	static const COLORREF &GetLightGreyColor(){return ActualColorLightGrey;};
	static const COLORREF &GetBlackColor(){return ActualColorBlack;};
	static const COLORREF &GetSuperDarkBlueColor(){return ActualColorSuperDarkBlue;};
	static const COLORREF &GetCyanColor(){return ActualColorCyan;};
	static const COLORREF &GetActiveButtonColor(){return ActualColorActiveButton;};

	static HBRUSH	BlackBrush;
	static HBRUSH	WhiteBrush;
	static HBRUSH	YellowBrush;
	static HBRUSH	LightYellowBrush;
	static HBRUSH	DarkYellowBrush;
	static HBRUSH	RedBrush;
    static HBRUSH	DarkRedBrush;
	static HBRUSH	OrangeBrush;
	static HBRUSH	GreenBrush;
	static HBRUSH	DarkGreenBrush;
	static HBRUSH	BorderBrush;
	static HBRUSH	BrushBackground;
	static HBRUSH	BlueBrush;
    static HBRUSH	CyanBrush;
    static HBRUSH	LightCyanBrush;
	static HBRUSH	LightBlueBrush;
	static HBRUSH	DarkBlueBrush;
	static HBRUSH	SuperDarkBlueBrush;
	static HBRUSH	DarkBrownBrush;
	static HBRUSH	LightBrownBrush;
	static HBRUSH	DarkGreyBrush;
	static HBRUSH	GreyBrush;
	static HBRUSH	PurpleBrush;
	static HBRUSH	LightGreyBrush;
	static HBRUSH	ActiveButtonBrush;
	static HBRUSH   NullBrush;

    static HPEN		PenBackground;
	static HPEN		LightBluePen;
	static HPEN		LightBluePen2;
	static HPEN     DashLightBluePen;
	static HPEN     DashLightBrownPen;
	static HPEN		BluePen;
	static HPEN		BluePen2;
	static HPEN		YellowPen;
	static HPEN		YellowPen2;
	static HPEN		YellowPen3;
    static HPEN		YellowPen7;
	static HPEN		DarkYellowPen;
	static HPEN		RedPen;
	static HPEN		RedPen2;
    static HPEN		RedPen3;
    static HPEN		RedPen4;
    static HPEN		RedPen5;
	static HPEN		RedPen7;
	static HPEN		RedPen13;
    static HPEN		DarkRedPen;
	static HPEN		DarkRedPen2;
    static HPEN		DarkRedPen3;
	static HPEN		WhitePen;
	static HPEN		WhitePen2;
	static HPEN		WhitePen3;
    static HPEN		WhitePen5;
    static HPEN		LightOrangePen;
    static HPEN		LightOrangePen2;
    static HPEN		LightOrangePen3;
	static HPEN		OrangePen;
	static HPEN		OrangePen2;
	static HPEN		OrangePen3;
	static HPEN		DarkOrangePen;
	static HPEN		BlackPen;
	static HPEN		BlackPen2;
	static HPEN     BlackPen3;
	static HPEN     BlackPen4;
	static HPEN     BlackPen5;
    static HPEN     BlackPen9;
	static HPEN		GreenPen;
	static HPEN		GreenPen2;
	static HPEN		GreenPen3;
	static HPEN		DarkGreenPen;
    static HPEN		DarkGreenPen2;
    static HPEN		DarkGreenPen3;
	static HPEN		GreyPen;
    static HPEN		GreyPen2;
    static HPEN		GreyPen3;
    static HPEN		GreyPen5;
	static HPEN		GreyPen7;
	static HPEN		GreyPen13;
	static HPEN		DarkBluePen2;
	static HPEN		PurplePen;
	static HPEN     PurplePen2;
	static HPEN     PurplePen3;
	static HPEN		LightPurplePen;
	static HPEN		DarkBrownPen;
	static HPEN		LightBrownPen;
	static HPEN		LightBrownPen2;
	static HPEN		LightBrownPen5;
	static HPEN		DashGreyPen;
	static HPEN		DashRedPen;
	static HPEN		DashGreenPen;
	static HPEN		DashGreenPen2;
	static HPEN		DashYellowPen;
	static HPEN		DashPurplePen;
	static HPEN		DashBluePen;
	static HPEN		DotGreyPen;
	static HPEN		DotBluePen;
	static HPEN		DotPurplePen;
	static HPEN		DashPurplePen2;
	static HPEN		DarkGreyPen;
	static HPEN		CyanPen;
    static HPEN		CyanPen2;
    static HPEN		CyanPen3;
    static HPEN		LightCyanPen;
    static HPEN		LightCyanPen2;
    static HPEN		LightCyanPen3;
    static HPEN		LightGreyPen;
    static HPEN		LightGreyPen2;


	static HFONT	BorderFont;
	static HFONT	Arial23;
	static HFONT	Arial16;
	static HFONT	Arial13;
	static HFONT	Arial12;
	static HFONT	Courier23;

    // Зоопарк шрифтов для Су-35

    static HFONT	Arial14;
    static HFONT	Arial18;
    static HFONT	Arial20;
    static HFONT	Arial22;

    static HFONT	Arial14b;
    static HFONT	Arial18b;
    static HFONT	Arial20b;
    static HFONT	Arial22b;

    static HFONT	Arial10b;

protected:
	static void		SwitchDayNight(){SwapColorInd();Prepare();};

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
	static const COLORREF	ColorsLightYellow[MAX_COLOR];
	static  COLORREF	ActualColorLightYellow;
	static const COLORREF	ColorsDarkYellow[MAX_COLOR];
	static  COLORREF	ActualColorDarkYellow;
	static const COLORREF	ColorsBorder[MAX_COLOR];
	static  COLORREF	ActualColorBorder;
	static const COLORREF	ColorsBackground[MAX_COLOR];
	static  COLORREF	ActualColorBackground;
	static const COLORREF	ColorsGreen[MAX_COLOR];
	static  COLORREF	ActualColorGreen;
	static const COLORREF	ColorsBlue[MAX_COLOR];
	static  COLORREF	ActualColorBlue;
	static const COLORREF	ColorsDarkBlue[MAX_COLOR];
	static  COLORREF	ActualColorDarkBlue;
	static const COLORREF	ColorsSuperDarkBlue[MAX_COLOR];///
	static  COLORREF	ActualColorSuperDarkBlue;///
	static const COLORREF	ColorsLightBlue[MAX_COLOR];
	static  COLORREF	ActualColorLightBlue;
	static const COLORREF	ColorsDarkBrown[MAX_COLOR];
	static  COLORREF	ActualColorDarkBrown;
	static const COLORREF	ColorsLightBrown[MAX_COLOR];
	static  COLORREF	ActualColorLightBrown;
    static const COLORREF	ColorsLightOrange[MAX_COLOR];
    static  COLORREF	ActualColorLightOrange;
	static const COLORREF	ColorsOrange[MAX_COLOR];
	static  COLORREF	ActualColorOrange;
	static const COLORREF	ColorsDarkOrange[MAX_COLOR];
	static  COLORREF	ActualColorDarkOrange;
	static const COLORREF	ColorsDarkGreen[MAX_COLOR];
	static  COLORREF	ActualColorDarkGreen;
	static const COLORREF	ColorsDarkGrey[MAX_COLOR];
	static  COLORREF	ActualColorDarkGrey;
	static const COLORREF	ColorsGrey[MAX_COLOR];
	static  COLORREF	ActualColorGrey;
	static const COLORREF	ColorsPurple[MAX_COLOR];
	static  COLORREF	ActualColorPurple;
	static const COLORREF	ColorsLightPurple[MAX_COLOR];
	static  COLORREF	ActualColorLightPurple;
	static const COLORREF	ColorsLightGrey[MAX_COLOR];
	static  COLORREF	ActualColorLightGrey;
	static const COLORREF	ColorsBlack[MAX_COLOR];
	static  COLORREF	ActualColorBlack;
	static const COLORREF	ColorsRed[MAX_COLOR];
	static  COLORREF	ActualColorRed;
	static const COLORREF	ColorsDarkRed[MAX_COLOR];
	static  COLORREF	ActualColorDarkRed;
	static const COLORREF	ColorsCyan[MAX_COLOR];
    static  COLORREF	ActualColorCyan;
    static const COLORREF	ColorsLightCyan[MAX_COLOR];
    static  COLORREF	ActualColorLightCyan;
    static const COLORREF	ColorsActiveButton[MAX_COLOR];
    static  COLORREF	ActualColorActiveButton;
};