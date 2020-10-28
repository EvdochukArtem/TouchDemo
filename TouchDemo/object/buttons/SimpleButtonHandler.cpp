#include "stdafx.h"
#include "SimpleButtonHandler.h"

void CALLBACK CSimpleButtonHandler::OnPZKPress(BUTTON_EVENT bEvent, CSimpleButton* btn)
{
	MessageBox(NULL, _T("PZK pressed"), L"", MB_OK);
}

void CALLBACK CSimpleButtonHandler::OnMFMPress(BUTTON_EVENT bEvent, CSimpleButton* btn)
{
	MessageBox(NULL, _T("MFM pressed"), L"", MB_OK);
}

void CALLBACK CSimpleButtonHandler::OnSimpleButtonPress(BUTTON_EVENT bEvent, CSimpleButton* btn)
{
	MessageBox(NULL, _T("Simple button pressed"), L"", MB_OK);
}
