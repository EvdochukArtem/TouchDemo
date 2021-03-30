/*
*	Родительский класс для страниц кадра. Страница представляет собой
*	сборник различных приборов относящихся только к данной странице.
*/

#pragma once

enum PAGE_TYPE
{
	//Страницы кадра CAM
	PAGE_CAM1,
	PAGE_CAM2,
	PAGE_CAM3,
	PAGE_CAM4,
	PAGE_CAM5,
	//Страницы кадра MAP
	PAGE_BD, //База данных
	PAGE_MAP, //Основная карта
	//Страницы кадра SYS
};

class CPage
{
public:
	CPage(PAGE_TYPE pType) { pageType = pType; _hidden = false; };
	virtual ~CPage() {};

	PAGE_TYPE GetPageType() { return pageType; };

	virtual void CreatePribors() = 0;
	virtual void DeletePribors() = 0;
	virtual void DisposePribors() = 0;

	virtual void LeftClickHandle(POINT pt) = 0;
	virtual void Hide(bool blockStatus) = 0;
	virtual bool IsHidden() { return _hidden; };

protected:
	PAGE_TYPE pageType;
	bool _hidden;
};