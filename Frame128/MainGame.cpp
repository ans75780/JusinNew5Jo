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
	MGR(CKeyMgr)->init();
	MGR(CSceneMgr)->Init();
	MGR(CSceneMgr)->AddScene("Stage", new CStage);
	MGR(CSceneMgr)->ChangeScene("Stage");
	MGR(CSoundMgr)->Init();

	MGR(CDevice)->Set_BufferSize({ WINCX, WINCY });

	if (FAILED(MGR(CDevice)->Init()))
	{
		assert(false);
	}

	/*m_pSingle = new CSingleTexture;
	m_pSingle->InsertTexture(L"../Texture/Cube.png");*/

	

	/*if (FAILED(MGR(CTextureMgr)->InsertTexture(L"../Texture/Cube.png", TEX_SINGLE, L"Cube")))
	{
		assert(false);
		return;
	}

	if (FAILED(MGR(CTextureMgr)->InsertTexture(L"../Texture/Stage/Terrain/Tile/Tile%d.png", TEX_MULTI, L"Terrain", L"Tile", 36)))
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
	MGR(CSoundMgr)->ReleaseSingleton();
	MGR(CCollisionMgr)->ReleaseSingleton();
	MGR(CDevice)->ReleaseSingleton();
	MGR(CTextureMgr)->ReleaseSingleton();

	CScrollMgr::Destroy_Instance();
}
