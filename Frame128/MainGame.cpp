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
	KEYMANAGER->Init();
	SCENEMANAGER->Init();
	SCENEMANAGER->AddScene("Stage", new CStage);
	SCENEMANAGER->ChangeScene("Stage");
	SOUNDMANAGER->Init();

}

void CMainGame::Update(void)
{
	SCENEMANAGER->Update();
}

void CMainGame::Late_Update(void)
{
	SCENEMANAGER->Late_Update();
}

void CMainGame::Render(void)
{
	TIMEMANAGER->Render(g_hWnd);
	HDC		hBackBufferDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	SCENEMANAGER->Render(hBackBufferDC);
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBufferDC, 0, 0, SRCCOPY);

}

void CMainGame::Release(void)
{
	SCENEMANAGER->ReleaseSingleton();
	ReleaseDC(g_hWnd, m_DC);
	CBmpMgr::Destroy_Instance();
	OBJMANAGER->ReleaseSingleton();
	KEYMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	SOUNDMANAGER->ReleaseSingleton();
	COLLISIONMANAGER->ReleaseSingleton();
	CScrollMgr::Destroy_Instance();
}
