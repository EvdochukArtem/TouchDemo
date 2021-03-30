#pragma once
#include "../AbstractButton.h"

enum PBTN_VALUE_TYPE
{
	PBTN_VTYPE_INT,
	PBTN_VTYPE_LONG,
	PBTN_VTYPE_FLOAT,
	PBTN_VTYPE_DOUBLE,
};

class CRotaryButton;
const int PARAM_BUTTON_ACTIVE_TIMER = 10000;

class CParamButton : public CAbstractButton
{
public:

	class Value;

	CParamButton(int x, int y, int cx, int cy, LPCTSTR caption, Value value,
				 void(CALLBACK* rotaryHandler)(MOUSE_EVNT, CRotaryButton*));
	CParamButton(int x, int y, int cx, int cy, LPCTSTR caption, std::vector <Value>& value,
				 void(CALLBACK* rotaryHandler)(MOUSE_EVNT, CRotaryButton*));
	~CParamButton();

	void Draw(HDC& hdc);
	void DrawBackground();
	void LeftClickHandle();

	Value& GetActiveValue() { return values.at(activeValue); };
	void ActivateNextValue();
	void UpdateActivityTime();

protected:
	bool enabled;

private:
	void(CALLBACK* _handler)(MOUSE_EVNT, CParamButton*);
	void(CALLBACK* rotaryHandler)(MOUSE_EVNT, CRotaryButton*);
	
	int activeValue;
	std::vector <Value> values;
	long lastActivityTime;
	
	friend class CRotaryButton;
	friend class CParamButtonHandler;

	static std::vector<CParamButton*> allParamButtons;
};

class CParamButton::Value
{
public:
	Value(void* value, PBTN_VALUE_TYPE type, int decimalPoint, double valueStep);
	~Value() { value = nullptr; };
	
	void DecrimentValue();
	void IncrimentValue();

	LPCTSTR ToString();

private:
	void*			value;
	PBTN_VALUE_TYPE	vType;
	int				decimalPoint;
	double			valueStep;
	
	TCHAR buf [10];
};