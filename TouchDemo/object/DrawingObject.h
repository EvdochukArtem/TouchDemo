/*
*	������������ ����� ��� ���� �������� ������� ������ ���� ����������. �������� �������
*	��� ���� �������� �������� ��������� (���. ����������, ������, �����, ��������� � ��.)
*	� ��������� ������� ������.
*/
#pragma once

enum DRAWOBJ_PRIOR
{
	PRIOR_MIN, PRIOR_MID,
	//���� MAP:
	PRIOR_MAP, PRIOR_SCALE, PRIOR_PLANE,
	//
	PRIOR_MAX, PRIOR_BUTTONS, PRIOR_ACTIVE, PRIOR_SOI,
};

class CDrawingObject
{
public:
	CDrawingObject(DRAWOBJ_PRIOR prior);
	~CDrawingObject();

	virtual void Draw(HDC& hdc) = 0;
	virtual void DrawBackground() = 0;

	virtual bool PointIsMine(const POINT& touchCoord);
	virtual DRAWOBJ_PRIOR GetPrior() final { return _prior; };
	virtual void DrawBorders(HDC& hdc);
	virtual void Hide(bool hidden) { _hidden = hidden; };

protected:
	int _x;								//x ���������� �������� ������ ���� ������������ �������
	int _y;								//y ���������� �������� ������ ���� ������������ �������
	int _cx;							//������ ������������ �������
	int _cy;							//������ ������������ �������
	DRAWOBJ_PRIOR _prior;				//��������� ���������
	bool _hidden;
	HPEN oldPen;
	HBRUSH oldBrush;
	UINT oldTextAlign;
	COLORREF oldColor;
	HFONT oldFont;
	COLORREF oldBkColor;
	TCHAR buf[128];							//����� ��� ������

	virtual void Place() = 0;

private:
	void RegisterDrawingObject();
	void DeleteDrawingObject();
};