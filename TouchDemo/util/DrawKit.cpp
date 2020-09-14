#include "StdAfx.h"
#include "util/DrawKit.h"


#define START_COLOR		1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HBRUSH		CDrawKit::BlackBrush		= NULL;
HBRUSH		CDrawKit::WhiteBrush		= NULL;
HBRUSH		CDrawKit::LightGreyBrush	= NULL;
HBRUSH		CDrawKit::YellowBrush		= NULL;
HBRUSH		CDrawKit::NullBrush			= NULL;
HPEN		CDrawKit::BlackPen			= NULL;
HPEN		CDrawKit::BlackPen2			= NULL;
HPEN		CDrawKit::GreenPen2			= NULL;
HPEN		CDrawKit::BluePen2			= NULL;
HPEN		CDrawKit::RedPen2			= NULL;
HFONT		CDrawKit::Arial16			= NULL;

int			CDrawKit::ColorInd			= START_COLOR;

const COLORREF CDrawKit::ColorsBlack[MAX_COLOR]		=	{RGB(0,   0,     0), RGB(0,     0,   0)};
 COLORREF CDrawKit::ActualColorBlack				=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsWhite[MAX_COLOR]		=	{RGB(192, 192, 192), RGB(255, 255, 255)};
 COLORREF CDrawKit::ActualColorWhite				=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsYellow[MAX_COLOR] = { RGB(192, 192,   0), RGB(255, 255,   0) };
COLORREF CDrawKit::ActualColorYellow = RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsLightGrey[MAX_COLOR]	=	{RGB(128, 128, 128), RGB(192, 192, 192)};
 COLORREF CDrawKit::ActualColorLightGrey			=	RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsGreen[MAX_COLOR] = { RGB(0  , 192,   0), RGB(0,   255,  50) };
COLORREF CDrawKit::ActualColorGreen = RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsBlue[MAX_COLOR] = { RGB(0,   0,   200), RGB(0,   0,   255) };
COLORREF CDrawKit::ActualColorBlue = RGB(255, 255, 255);
const COLORREF CDrawKit::ColorsRed[MAX_COLOR] = { RGB(255, 0,     0), RGB(255,   0,   0) };
COLORREF CDrawKit::ActualColorRed = RGB(255, 255, 255);

BOOL CDrawKit::Create()
{
	ActualColorBlack		= ColorsBlack[ColorInd];
	ActualColorWhite		= ColorsWhite[ColorInd];
	ActualColorYellow		= ColorsYellow[ColorInd];
	ActualColorLightGrey	= ColorsLightGrey[ColorInd];
	ActualColorGreen		= ColorsGreen[ColorInd];
	ActualColorBlue			= ColorsBlue[ColorInd];
	ActualColorRed			= ColorsRed[ColorInd];

	BlackBrush		= ::CreateSolidBrush(ColorsBlack[ColorInd]);
	WhiteBrush		= ::CreateSolidBrush(ColorsWhite[ColorInd]);
	YellowBrush		= ::CreateSolidBrush(ColorsYellow[ColorInd]);
	LightGreyBrush	= ::CreateSolidBrush(ColorsLightGrey[ColorInd]);
	NullBrush		= ::CreateSolidBrush(NULL);
	
	BlackPen		=	::CreatePen(PS_SOLID, 1, ColorsBlack[ColorInd]);
	GreenPen2		=	::CreatePen(PS_SOLID, 2, ColorsGreen[ColorInd]);
	BluePen2		=	::CreatePen(PS_SOLID, 2, ColorsBlue[ColorInd]);
	BlackPen2		=	::CreatePen(PS_SOLID, 2, ColorsBlack[ColorInd]);
	RedPen2			= ::CreatePen(PS_SOLID, 2, ColorsRed[ColorInd]);
	
	int size = (int)(HEIGHTPX/44.0*1.5);
	Arial16			=	::CreateFont(int(size*16.0/18.0), 0, 0, 0, FW_NORMAL,
								FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY, DEFAULT_PITCH, (L"ARIAL"));
	return TRUE;
}

void CDrawKit::CleanUp()
{
	DeleteDrawKitObject((void **)&BlackBrush);
	DeleteDrawKitObject((void **)&WhiteBrush);
	DeleteDrawKitObject((void **)&LightGreyBrush);
	DeleteDrawKitObject((void **)&YellowBrush);
	DeleteDrawKitObject((void **)&GreenPen2);
	DeleteDrawKitObject((void **)&BluePen2);
	DeleteDrawKitObject((void **)&RedPen2);
	DeleteDrawKitObject((void **)&NullBrush);
	DeleteDrawKitObject((void **)&Arial16);
}

void CDrawKit::DeleteDrawKitObject(IN HGDIOBJ *Obj)
{
	if (*Obj)
	{
		::DeleteObject(*Obj);
		*Obj	= NULL;
	}
}
