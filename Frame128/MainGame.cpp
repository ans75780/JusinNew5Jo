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
#include "UserDefineHeaders.h"
#include "RandomMgr.h"
#include "Camera.h"
#include "SoundMgr.h"
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


	MGR(CDevice)->Set_BufferSize({ WINCX, WINCY });

	if (FAILED(MGR(CDevice)->Init()))
	{
		assert(false);
	}
	if (FAILED(MGR(CTextureMgr)->InsertTexture(L"../Image/Background/Background.png", TEX_SINGLE, L"Background")))
	{
		assert(false);
		return;
	}
	if (FAILED(MGR(CTextureMgr)->InsertTexture(L"../Image/Bullet.png", TEX_SINGLE, L"Bullet")))
	{
		assert(false);
		return;
	}

	if (FAILED(MGR(CTextureMgr)->InsertTexture(L"../Image/Player/Pistol/Idle/survivor-idle_handgun_%d.png", TEX_MULTI, L"Pistol", L"Idle", 20)))
	{
		assert(false);
		return;
	}
	if (FAILED(MGR(CTextureMgr)->InsertTexture(L"../Image/Coin%d.png", TEX_MULTI, L"Item", L"Coin", 2)))
	{
		assert(false);
		return;
	}
	MGR(SoundMgr)->Init();
	MGR(SoundMgr)->AddSound("Bgm", "../Sound/Bgm.mp3",  true, true);
	MGR(SoundMgr)->AddSound("Walk", "../Sound/Walk.mp3", false,true);
	MGR(SoundMgr)->AddSound("Zombie_Dead", "../Sound/Zombie_Dead.mp3");
	MGR(SoundMgr)->AddSound("Pistol_Shoot", "../Sound/Pistol_Shoot.mp3");
	MGR(SoundMgr)->AddSound("SMG_Shoot", "../Sound/SMG_Shoot.mp3");
	MGR(SoundMgr)->AddSound("Shotgun_Shoot", "../Sound/Shotgun_Shoot.mp3");



	//TIMEMANAGER은 windowcpp에서 초기화함(화면 루프 때문에)
	MGR(CKeyMgr)->init();
	MGR(CSceneMgr)->Init();
	MGR(CSceneMgr)->AddScene("Stage", new CStage);
	MGR(CSceneMgr)->ChangeScene("Stage");

	

	

	

	/*m_pSingle = new CSingleTexture;
	m_pSingle->InsertTexture(L"../Texture/Cube.png");*/

	

	/*if (FAILED(MGR(CTextureMgr)->InsertTexture(L"../Texture/Cube.png", TEX_SINGLE, L"Cube")))
	{
		assert(false);
		return;
	}*/

	

}

void CMainGame::Update(void)
{
	MGR(CSceneMgr)->Update();
}

void CMainGame::Late_Update(void)
{
	MGR(CSceneMgr)->Late_Update();
	MGR(SoundMgr)->Update();
}

void CMainGame::Render(void)
{
	MGR(CDevice)->Render_Begin();
	
	MGR(CSceneMgr)->Render(nullptr);

	MGR(CDevice)->Render_End();
}

void CMainGame::Release(void)
{
	MGR(CSceneMgr)->ReleaseSingleton();
	ReleaseDC(g_hWnd, m_DC);
	CBmpMgr::Destroy_Instance();
	MGR(CObjMgr)->ReleaseSingleton();
	MGR(CKeyMgr)->ReleaseSingleton();
	MGR(CTimeMgr)->ReleaseSingleton();
	MGR(SoundMgr)->ReleaseSingleton();
	MGR(CCollisionMgr)->ReleaseSingleton();
	MGR(CDevice)->ReleaseSingleton();
	MGR(CTextureMgr)->ReleaseSingleton();

	CScrollMgr::Destroy_Instance();
}
