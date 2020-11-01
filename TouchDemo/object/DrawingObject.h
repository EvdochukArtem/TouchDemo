/*
*	–одительский класс дл€ всех объектов которые должны быть отрисованы. —одержит базовые
*	дл€ всех дочерних объектов параметры (нач. координаты, ширина, длина, приоритет и др.)
*	и некоторые базовые методы.
*/
#pragma once

enum DRAWOBJ_PRIOR
{
	MIN, MID, MAX, ACTIVE, SOI,
};

class CDrawingObject
{
public:
	CDrawingObject(DRAWOBJ_PRIOR prior);
	~CDrawingObject();

	virtual void Draw(HDC& hdc) = 0;
	virtual void DrawBackground() = 0;

	virtual bool PointIsMine(const POINT& touchCoord) final;
	virtual DRAWOBJ_PRIOR GetPrior() final { return _prior; };
	virtual void DrawBorders(HDC& hdc);
	virtual void Hide(bool hidden) { _hidden = hidden; };

protected:
	int _x;								//x координата верхнего левого угла
	int _y;								//y координата верхнего левого угла
	int _cx;								//ширина
	int _cy;								//высота
	DRAWOBJ_PRIOR _prior;					//приоритет отрисовки
	bool _hidden;
	HPEN oldPen;
	HBRUSH oldBrush;
	UINT oldTextAlign;
	COLORREF oldColor;
	HFONT oldFont;
	TCHAR buf[128];							//буфер дл€ текста

private:
	void RegisterDrawingObject();
	void DeleteDrawingObject();
};