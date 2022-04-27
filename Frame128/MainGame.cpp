#include "stdafx.h"
#include "MainGame.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"
#include "Stage.h"
#include "MyEditor.h"
#include "CollisionMgr.h"


CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"BackBuffer");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Background.bmp", L"Background");

	//TIMEMANAGER은 windowcpp에서 초기화함(화면 루프 때문에)
	MGR(CKeyMgr)->Init();
	MGR(CSceneMgr)->Init();
	MGR(CSceneMgr)->AddScene("Stage", new CStage);
	MGR(CSceneMgr)->ChangeScene("Stage");
	MGR(CSoundMgr)->Init();

}

void CMainGame::Update(void)
{
	MGR(CSceneMgr)->Update();
}

void CMainGame::Late_Update(void)
{
	MGR(CSceneMgr)->Late_Update();
}

void CMainGame::Render(void)
{
	MGR(CTimeMgr)->Render(g_hWnd);
	HDC		hBackBufferDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	MGR(CSceneMgr)->Render(hBackBufferDC);
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBufferDC, 0, 0, SRCCOPY);

}

void CMainGame::Release(void)
{
	MGR(CSceneMgr)->ReleaseSingleton();
	ReleaseDC(g_hWnd, m_DC);
	CBmpMgr::Destroy_Instance();
	MGR(CObjMgr)->ReleaseSingleton();
	MGR(CKeyMgr)->ReleaseSingleton();
	MGR(CTimeMgr)->ReleaseSingleton();
	MGR(CSoundMgr)->ReleaseSingleton();
	MGR(CCollisionMgr)->ReleaseSingleton();
	CScrollMgr::Destroy_Instance();
}
