#pragma once

enum DRAWOBJ_PRIOR
{
	MIN, MID, MAX,
};

class CDrawingObject
{
public:
	CDrawingObject();
	~CDrawingObject();
	virtual void Draw(HDC hdc) = 0;
	virtual void DrawBackground() = 0;
	virtual bool PointIsMine(const POINT touchCoord) final;
	virtual DRAWOBJ_PRIOR getPrior() final { return _prior; };

protected:
	UINT _x;								//x координата верхнего левого угла
	UINT _y;								//y координата верхнего левого угла
	UINT _cx;								//ширина
	UINT _cy;								//высота
	DRAWOBJ_PRIOR _prior;
	HPEN oldPen;
	HBRUSH oldBrush;
	UINT oldTextAlign;
	COLORREF oldColor;
	_TCHAR buf[128];						//буфер для текста
	virtual void DrawBorders(HDC hdc) final;
private:
	void RegisterDrawingObject();
	void DeleteDrawingObject();
};