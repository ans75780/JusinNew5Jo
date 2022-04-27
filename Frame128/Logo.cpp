#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

HRESULT CLogo::Init(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");


	return S_OK;
}

void CLogo::Update(void)
{
	
}

void CLogo::Late_Update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->ChangeScene("menu");
		return;
	}
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release(void)
{
	
}
