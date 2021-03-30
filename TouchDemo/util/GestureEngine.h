/*
*	Класс получает и обрабатывает сообщения с данными о жестах из главного файла программы.
*/
#pragma once


class CGestureEngine
{
public:
	
	LRESULT WndProc(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void ProcessPressAndTap(const POINT firstTouchCoord);
    void ProcessTwoFingerTap(const POINT firstTouchCoord);
    void ProcessZoom(const POINT firstTouchCoord, const double dZoomFactor, const POINT zoomCenter);
    void ProcessMove(const POINT beginCoord, const POINT startCoord, const POINT delta);
    void ProcessSwipe(const POINT firstTouchCoord, const POINT secondTouchCoord);
    void ProcessRotate(const POINT firstTouchCoord, const double dAngle, const POINT rotateCenter);
	void HandleZoom(HWND hWnd, GESTUREINFO gi);
	void HandlePan(HWND hWnd, GESTUREINFO gi);
	void HandleRotate(HWND hWnd, GESTUREINFO gi);
	void HandleTwoFingerTap(HWND hWnd, GESTUREINFO gi);
	void HandlePressAndTap(HWND hWnd, GESTUREINFO gi);

private:
	CGestureEngine();
	~CGestureEngine() {};
	BOOL Create();
	BOOL CleanUp();

	friend class CUtil;

    POINT _ptFirst;        // first significant point of the gesture
    POINT _ptSecond;       // second significant point of the gesture
	POINT _ptBegin;
    DWORD _dwArguments;    // 4 bytes long argument
    bool TouchInKadrSpace(const POINT touchCoord);
	bool panIsComplete;
	static CGestureEngine *pGestureEngine;
	static void CALLBACK PanTimerProc (HWND hwnd, // handle to window for timer messages
								UINT message, // WM_TIMER message
								UINT idTimer, // timer identifier
								DWORD dwTime);
};