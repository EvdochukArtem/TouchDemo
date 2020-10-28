/*
*	������������ ����� ��� ���� �������� ������� ������ ���� ����������. �������� �������
*	��� ���� �������� �������� ��������� (���. ����������, ������, �����, ��������� � ��.)
*	� ��������� ������� ������.
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
	UINT _x;								//x ���������� �������� ������ ����
	UINT _y;								//y ���������� �������� ������ ����
	UINT _cx;								//������
	UINT _cy;								//������
	DRAWOBJ_PRIOR _prior;					//��������� ���������
	bool _hidden;
	HPEN oldPen;
	HBRUSH oldBrush;
	UINT oldTextAlign;
	COLORREF oldColor;
	TCHAR buf[128];							//����� ��� ������

private:
	void RegisterDrawingObject();
	void DeleteDrawingObject();
};