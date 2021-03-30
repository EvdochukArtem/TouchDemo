#include "StdAfx.h"
#include "util/DrawKit.h"


#define START_COLOR		1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HBRUSH		CDrawKit::BlackBrush		= NULL;
HBRUSH		CDrawKit::WhiteBrush		= NULL;
HBRUSH		CDrawKit::YellowBrush		= NULL;
HBRUSH		CDrawKit::RedBrush			= NULL;
HBRUSH		CDrawKit::OrangeBrush		= NULL;
HBRUSH		CDrawKit::GreenBrush		= NULL;
HBRUSH		CDrawKit::BlueBrush			= NULL;
HBRUSH		CDrawKit::GreyBrush			= NULL;
HBRUSH		CDrawKit::LightGreyBrush	= NULL;
HBRUSH		CDrawKit::ActiveButtonBrush = NULL;
HBRUSH		CDrawKit::NullBrush			= NULL;

HPEN		CDrawKit::ActiveButtonPen	= NULL;
HPEN		CDrawKit::BluePen			= NULL;
HPEN		CDrawKit::BluePen2			= NULL;
HPEN		CDrawKit::YellowPen			= NULL;
HPEN		CDrawKit::YellowPen2		= NULL;
HPEN		CDrawKit::YellowPen3		= NULL;
HPEN		CDrawKit::RedPen			= NULL;
HPEN		CDrawKit::RedPen2			= NULL;
HPEN		CDrawKit::RedPen3			= NULL;
HPEN		CDrawKit::WhitePen			= NULL;
HPEN		CDrawKit::WhitePen2			= NULL;
HPEN		CDrawKit::WhitePen3			= NULL;
HPEN		CDrawKit::OrangePen			= NULL;
HPEN		CDrawKit::OrangePen2		= NULL;
HPEN		CDrawKit::OrangePen3		= NULL;
HPEN		CDrawKit::BlackPen			= NULL;
HPEN		CDrawKit::BlackPen2			= NULL;
HPEN		CDrawKit::BlackPen3			= NULL;
HPEN		CDrawKit::GreenPen			= NULL;
HPEN		CDrawKit::GreenPen2			= NULL;
HPEN		CDrawKit::GreenPen3			= NULL;
HPEN		CDrawKit::GreyPen			= NULL;
HPEN		CDrawKit::GreyPen2			= NULL;
HPEN		CDrawKit::GreyPen3			= NULL;


HFONT		CDrawKit::BorderFont		= NULL; 
HFONT		CDrawKit::Arial23			= NULL;
HFONT		CDrawKit::Arial16			= NULL;
HFONT		CDrawKit::Arial13			= NULL;
HFONT		CDrawKit::Arial12			= NULL; 
HFONT		CDrawKit::Arial14			= NULL;
HFONT		CDrawKit::Arial10b			= NULL;

int			CDrawKit::ColorInd			= START_COLOR;

const COLORREF CDrawKit::ColorsWhite[MAX_COLOR]		=	{RGB(192, 192, 192), RGB(255, 255, 255)};
 COLORREF CDrawKit::ActualColorWhite				=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsGreen[MAX_COLOR]		=	{RGB(0  , 192,   0), RGB(0,   255,  50)};
 COLORREF CDrawKit::ActualColorGreen				=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsYellow[MAX_COLOR]	=	{RGB(192, 192,   0), RGB(255, 255,   0)};
 COLORREF CDrawKit::ActualColorYellow				=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsBlue[MAX_COLOR]		=	{RGB(0,   0,   200), RGB(0,   0,   255)};
 COLORREF CDrawKit::ActualColorBlue					=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsOrange[MAX_COLOR]	=	{RGB(192, 96,   48), RGB(255, 128,  64)};
 COLORREF CDrawKit::ActualColorOrange				=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsGrey[MAX_COLOR]		=	{RGB(96 , 96,   96), RGB(144, 144, 144)};
 COLORREF CDrawKit::ActualColorGrey					=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsLightGrey[MAX_COLOR]	=	{RGB(128, 128, 128), RGB(192, 192, 192)};
 COLORREF CDrawKit::ActualColorLightGrey			=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsBlack[MAX_COLOR]		=	{RGB(0,   0,     0), RGB(0,     0,   0)};
 COLORREF CDrawKit::ActualColorBlack				=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsRed[MAX_COLOR]		=	{RGB(255, 0,     0), RGB(255,   0,   0)};
 COLORREF CDrawKit::ActualColorRed					=	RGB(255, 255, 255);
 const COLORREF CDrawKit::ColorsActiveButton[MAX_COLOR] = { RGB(63,  135, 135), RGB(0,   64,   64) };
 COLORREF CDrawKit::ActualColorActiveButton = NULL;


 BOOL CDrawKit::Create()
{
	ActualColorWhite		= ColorsWhite[ColorInd];
	ActualColorYellow		= ColorsYellow[ColorInd];
	ActualColorGreen		= ColorsGreen[ColorInd];
	ActualColorBlue			= ColorsBlue[ColorInd];
	ActualColorOrange		= ColorsOrange[ColorInd];
	ActualColorGrey			= ColorsGrey[ColorInd];
	ActualColorLightGrey	= ColorsLightGrey[ColorInd];
	ActualColorBlack		= ColorsBlack[ColorInd];
	ActualColorRed			= ColorsRed[ColorInd];
	ActualColorActiveButton = ColorsActiveButton[ColorInd];
	BlackBrush		= ::CreateSolidBrush(ColorsBlack[ColorInd]);
	RedBrush		= ::CreateSolidBrush(ColorsRed[ColorInd]);
	OrangeBrush		= ::CreateSolidBrush(ColorsOrange[ColorInd]);
	WhiteBrush		= ::CreateSolidBrush(ColorsWhite[ColorInd]);
	YellowBrush		= ::CreateSolidBrush(ColorsYellow[ColorInd]);
	GreenBrush		= ::CreateSolidBrush(ColorsGreen[ColorInd]);
	BlueBrush		= ::CreateSolidBrush(ColorsBlue[ColorInd]);
	GreyBrush		= ::CreateSolidBrush(ColorsGrey[ColorInd]);
	LightGreyBrush	= ::CreateSolidBrush(ColorsLightGrey[ColorInd]);
	ActiveButtonBrush = CreateSolidBrush(ColorsActiveButton[ColorInd]);
	NullBrush		= ::CreateSolidBrush(NULL);
	
	LOGBRUSH redLog;
	redLog.lbColor = ColorsRed[ColorInd];
	redLog.lbHatch = DIB_RGB_COLORS;
	redLog.lbStyle = BS_SOLID;

	LOGBRUSH greyLog;
	greyLog.lbColor = ColorsGrey[ColorInd];
	greyLog.lbHatch = DIB_RGB_COLORS;
	greyLog.lbStyle = BS_SOLID;

	ActiveButtonPen = CreatePen(PS_SOLID, 1, ColorsActiveButton[ColorInd]);
	BluePen			=	::CreatePen(PS_SOLID, 1, ColorsBlue[ColorInd]);
    BluePen2		=	::CreatePen(PS_SOLID, 2, ColorsBlue[ColorInd]);
	YellowPen		=	::CreatePen(PS_SOLID, 1, ColorsYellow[ColorInd]);
	YellowPen2		=	::CreatePen(PS_SOLID, 2, ColorsYellow[ColorInd]);
	YellowPen3		=	::CreatePen(PS_SOLID, 3, ColorsYellow[ColorInd]);
	RedPen			=	::CreatePen(PS_SOLID, 1, ColorsRed[ColorInd]);
	RedPen2			=	::CreatePen(PS_SOLID, 2, ColorsRed[ColorInd]);
	RedPen3			=	::CreatePen(PS_SOLID, 3, ColorsRed[ColorInd]);
	WhitePen		=	::CreatePen(PS_SOLID, 1, ColorsWhite[ColorInd]);
	WhitePen2		=	::CreatePen(PS_SOLID, 2, ColorsWhite[ColorInd]);
	WhitePen3		=	::CreatePen(PS_SOLID, 3, ColorsWhite[ColorInd]);
	OrangePen		=	::CreatePen(PS_SOLID, 1, ColorsOrange[ColorInd]);
	OrangePen2		=	::CreatePen(PS_SOLID, 2, ColorsOrange[ColorInd]);
	OrangePen3		=	::CreatePen(PS_SOLID, 3, ColorsOrange[ColorInd]);
	BlackPen		=	::CreatePen(PS_SOLID, 1, ColorsBlack[ColorInd]);
	BlackPen2		=	::CreatePen(PS_SOLID, 2, ColorsBlack[ColorInd]);
	BlackPen3		=	::CreatePen(PS_SOLID, 3, ColorsBlack[ColorInd]);
	GreenPen		=	::CreatePen(PS_SOLID, 1, ColorsGreen[ColorInd]);
	GreenPen2		=	::CreatePen(PS_SOLID, 2, ColorsGreen[ColorInd]);
	GreenPen3		=	::CreatePen(PS_SOLID, 3, ColorsGreen[ColorInd]);
	GreyPen			=	::CreatePen(PS_SOLID, 1, ColorsGrey[ColorInd]);
    GreyPen2		=	::CreatePen(PS_SOLID, 2, ColorsGrey[ColorInd]);
    GreyPen3		=	::CreatePen(PS_SOLID, 3, ColorsGrey[ColorInd]);



	int size = (int)(HEIGHTPX/44.0*1.5);

	BorderFont		=	CreateFont(size, 0, 0, 0, FW_BOLD,
								FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH, (L"COURIER NEW"));
	Arial23 =			CreateFont(int(size * 23.0 / 18.0), 0, 0, 0, FW_NORMAL,
								FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH, (L"ARIAL"));
	Arial16			=	CreateFont(int(size*16.0/18.0), 0, 0, 0, FW_NORMAL,
								FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH, (L"ARIAL"));
	Arial13			=	CreateFont(int(size*13.0/18.0), 0, 0, 0, FW_SEMIBOLD,
								FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH, (L"ARIAL"));
	Arial12			=	CreateFont(int(size*12.0/18.0), 0, 0, 0, FW_NORMAL,
								FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH, (L"ARIAL"));
	Arial14 = CreateFont(int(size * 14.0 / 18.0), 0, 0, 0, FW_NORMAL,
								FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH, (L"ARIAL"));
	Arial10b		=	CreateFont(int(size * 10.0 / 18.0), 0, 0, 0, FW_SEMIBOLD,
								FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH, (L"ARIAL"));
	return TRUE;
}

BOOL CDrawKit::CleanUp()
{
	DeleteDrawKitObject((void **)&BlackBrush);
	DeleteDrawKitObject((void **)&RedBrush);
	DeleteDrawKitObject((void **)&OrangeBrush);
	DeleteDrawKitObject((void **)&YellowBrush);
	DeleteDrawKitObject((void **)&WhiteBrush);
	DeleteDrawKitObject((void **)&GreenBrush);
	DeleteDrawKitObject((void **)&BlueBrush);
	DeleteDrawKitObject((void **)&GreyBrush);
	DeleteDrawKitObject((void **)&LightGreyBrush);
	DeleteDrawKitObject((void**)&ActiveButtonBrush);
	DeleteDrawKitObject((void **)&NullBrush);
	DeleteDrawKitObject((void**)&ActiveButtonPen);
	DeleteDrawKitObject((void **)&BluePen);
    DeleteDrawKitObject((void **)&BluePen2);
	DeleteDrawKitObject((void **)&YellowPen);
	DeleteDrawKitObject((void **)&YellowPen2);
	DeleteDrawKitObject((void **)&YellowPen3);
	DeleteDrawKitObject((void **)&RedPen);
	DeleteDrawKitObject((void **)&RedPen2);
	DeleteDrawKitObject((void **)&RedPen3);
	DeleteDrawKitObject((void **)&WhitePen);
	DeleteDrawKitObject((void **)&WhitePen2);
	DeleteDrawKitObject((void **)&OrangePen);
	DeleteDrawKitObject((void **)&OrangePen2);
	DeleteDrawKitObject((void **)&OrangePen3);
	DeleteDrawKitObject((void **)&BlackPen);
	DeleteDrawKitObject((void **)&BlackPen2);
	DeleteDrawKitObject((void **)&BlackPen3);
	DeleteDrawKitObject((void **)&GreenPen);
	DeleteDrawKitObject((void **)&GreenPen2);
	DeleteDrawKitObject((void **)&GreenPen3);
	DeleteDrawKitObject((void **)&GreyPen);
	DeleteDrawKitObject((void **)&GreyPen2);
	DeleteDrawKitObject((void **)&GreyPen3);
	DeleteDrawKitObject((void **)&BorderFont);
	DeleteDrawKitObject((void**)&Arial23);
	DeleteDrawKitObject((void **)&Arial16);
	DeleteDrawKitObject((void**)&Arial14);
	DeleteDrawKitObject((void **)&Arial13);
	DeleteDrawKitObject((void **)&Arial12);
	DeleteDrawKitObject((void**)&Arial10b);

	return TRUE;
}

void CDrawKit::DeleteDrawKitObject(IN HGDIOBJ *Obj)
{
	if (*Obj)
	{
		::DeleteObject(*Obj);
		*Obj	= NULL;
	}
}
