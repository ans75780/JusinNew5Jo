#include "stdafx.h"
#include "MainGame.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	
	CLineMgr::Get_Instance()->Initialize();

}

void CMainGame::Update(void)
{
	CLineMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	
}

void CMainGame::Render(void)
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	
	CLineMgr::Get_Instance()->Render(m_DC);
}

void CMainGame::Release(void)
{
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
