#include "stdafx.h"
#include "TimeMgr.h"
#include "../Header/Define.h"
CTimeMgr::CTimeMgr()
{
}

CTimeMgr::~CTimeMgr()
{
	Release();
}

HRESULT CTimeMgr::Init()
{
	m_pTimer = new CTimer;
	m_pTimer->Init();
	return S_OK;
}

void CTimeMgr::Release()
{
	if (m_pTimer != nullptr)
	{
		SAFE_DELETE(m_pTimer);
		m_pTimer = nullptr;
	}
}

void CTimeMgr::Update(float lock)
{
	if (m_pTimer != nullptr)
	{
		m_pTimer->Tick(lock);
	}
}

void CTimeMgr::Render(HDC hdc)
{
	TCHAR str[MAX_STR];
	string strFrame;
	//글자 배경모드
	SetBkMode(hdc, TRANSPARENT);
	//글자 색상
	SetTextColor(hdc, RGB(0, 0, 255));

#ifdef _DEBUG
	if (m_pTimer != nullptr)
	{
		//FPS
		wsprintf(str, L"FPS: %d", m_pTimer->GetFrameRate());
		TextOut(hdc, 0, 0, str, lstrlen(str));

		//전체경과시간
		wsprintf(str, L"worldTime: %f", m_pTimer->GetWorldTime());
		TextOut(hdc, 0, 20, str, lstrlen(str));

		//한프레임당 경과시간
		wsprintf(str, L"ElapsedTime: %f", m_pTimer->GetElapsedTime());
		TextOut(hdc, 0, 40, str, lstrlen(str));
	}
#else
	if (m_pTimer != nullptr)
	{
		//FPS
		wsprintf(str, "FPS : %d", m_pTimer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}

void CTimeMgr::Render(HWND hWnd)
{
	TCHAR str[MAX_STR];
	wsprintf(str, L"FPS: %d", m_pTimer->GetFrameRate());
	SetWindowText(g_hWnd, str);
}
