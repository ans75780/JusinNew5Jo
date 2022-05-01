#include "stdafx.h"
#include "Stage.h"

#include "UserDefineHeaders.h"
#include "CBoss_hyde.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

HRESULT CStage::Init(void)
{
	srand(unsigned(time(NULL)));
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"BackGround");

	if (FAILED(MGR(CTextureMgr)->InsertTexture(L"../Image/Monster/skeleton-move_%d.png", TEX_MULTI, L"Monster", L"Zombie", 16)))
	{
		assert(false);
		return S_OK;
	}

	MGR(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	MGR(CObjMgr)->AddObject(OBJ_BOSS, CAbstractFactory<CBoss_hyde>::Create());
	MGR(CObjMgr)->AddObject(OBJ_FEATURE, CAbstractFactory<CFeature>::Create(100,100,0));
	mapSize.x = float(MGR(CTextureMgr)->Get_Texture(L"Background")->tImgInfo.Width);
	mapSize.y = 600.f;
	mapSize.z = 0;
	pt = { 0,0,0 };
	/*for (int i = 0; i < 500 ; i++)
	{
		MGR(CObjMgr)->AddObject(OBJID::OBJ_MONSTER, CAbstractFactory<CZombie>::Create(WINCX + rand() % 400, WINCY + rand () % 400, 0));
	}*/
	/*CObj* Coin = CAbstractFactory<CCoin>::Create();
	Coin->Set_Pos(DXV3(300.f, 100.f, 0.f));
	MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin);

	CObj* Coin2 = CAbstractFactory<CCoin>::Create();
	Coin2->Set_Pos(DXV3(600.f, 300.f, 0.f));
	MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin2);

	CObj* Coin3 = CAbstractFactory<CCoin>::Create();
	Coin3->Set_Pos(DXV3(200.f, 300.f, 0.f));
	MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin3);*/

	MGR(CObjMgr)->AddObject(OBJID::OBJ_MONSTER
		, CAbstractFactory<CGiantZombie>::Create(float(WINCX / 2 + rand() % 400), float(WINCY / 2 + rand() % 400), 0.f));

	MGR(CTimeMgr)->AddLoopEvent(2.f, this, 0);
	MGR(CTimeMgr)->AddLoopEvent(7.f, this, 1);

	return S_OK;
}

void CStage::Update(void)
{  
	MGR(CObjMgr)->Update();
	MGR(CKeyMgr)->update();
	MGR(CTimeMgr)->Update();
}

void CStage::Late_Update(void)
{
	MGR(CObjMgr)->Late_Update();
	
	//충돌처리 업데이트
	MGR(CCollisionMgr)->CollisionUpdate
	(
		MGR(CObjMgr)->Get_ObjList(OBJ_PLAYER),
		MGR(CObjMgr)->Get_ObjList(OBJ_MONSTER)
	);

	MGR(CCollisionMgr)->CollisionUpdate
	(
		MGR(CObjMgr)->Get_ObjList(OBJ_PLAYER),
		MGR(CObjMgr)->Get_ObjList(OBJ_FEATURE)
	);

	MGR(CCollisionMgr)->CollisionUpdate
	(
		MGR(CObjMgr)->Get_ObjList(OBJ_PLAYER),
		MGR(CObjMgr)->Get_ObjList(OBJ_ITEM)
	);

	MGR(CCollisionMgr)->CollisionUpdate
	(
		MGR(CObjMgr)->Get_ObjList(OBJID::OBJ_BULLET),
		MGR(CObjMgr)->Get_ObjList(OBJ_FEATURE)
	);
	MGR(CCollisionMgr)->CollisionUpdate
	(
		MGR(CObjMgr)->Get_ObjList(OBJID::OBJ_BULLET),
		MGR(CObjMgr)->Get_ObjList(OBJ_MONSTER)
	);

	MGR(CCollisionMgr)->CollisionUpdate
	(
		MGR(CObjMgr)->Get_ObjList(OBJID::OBJ_MONSTER),
		MGR(CObjMgr)->Get_ObjList(OBJID::OBJ_MONSTER)
	);

	pt = MGR(CObjMgr)->Get_Player()->Get_Pos();
	if (pt.x + WINCX_HALF >= mapSize.x)
		pt.x = mapSize.x - WINCX_HALF;
	else if (pt.x - WINCX_HALF < 0)
		pt.x = WINCX_HALF;

	if (pt.y + WINCY_HALF >= mapSize.y)
		pt.y = mapSize.y - WINCY_HALF;
	else if (pt.y - WINCY_HALF < 0)
		pt.y = WINCY_HALF;

	rc.left = long(pt.x - WINCX_HALF);
	rc.right = long(pt.x + WINCX_HALF);
	rc.top = long(pt.y - WINCY_HALF);
	rc.bottom = long(pt.y + WINCY_HALF);
}

void CStage::Render(HDC hDC)
{
	/*
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC img = CBmpMgr::Get_Instance()->Find_Image(L"Background");
	BitBlt(hDC,
		iScrollX,
		iScrollY,
		TILECX * TILEX,
		TILECY * TILEY,
		img,
		0,
		0,
		SRCCOPY);
	*/
	//백그라운드 출력
	DXMAT matWorld;
	D3DXMatrixTranslation(&matWorld, mapSize.x / 2, mapSize.y / 2, 0);
	DEVICE->Get_Sprite()->SetTransform(&matWorld);
	DEVICE->Get_Sprite()->Draw(MGR(CTextureMgr)->Get_Texture(L"Background")->pTexture, // 텍스처 객체
	&rc,	// 출력할 이미지 영역에 대한 렉트 구조체 포인터, null인 경우 이미지의 0, 0기준으로 출력
	&D3DXVECTOR3(mapSize.x / 2, mapSize.y / 2, -1),	// 출력할 이미지의 중심 축에 대한 vec3 구조체 포인터, null인 경우 0, 0이 중심 좌표
	&D3DXVECTOR3(0, 0, 0),	// 위치 좌표에 대한 vec3 구조체 포인터, null인 경우 스크린 상 0,0,에 좌표 출력
	D3DCOLOR_ARGB(255, 255, 255, 255));	// 출력할 원본 이미지와 섞을 색상 값, 0xffffffff 값을 넣어주면 원본색 유지
	//백그라운드 출력 끝
	MGR(CObjMgr)->Render(hDC);
	RECT rc = { 100,0,0,0 };
	TCHAR	str[MAX_STR];
	int zombieCount = 0;
	list<CObj*> monster_List = MGR(CObjMgr)->Get_ObjList(OBJ_MONSTER);
	for_each(monster_List.begin(), monster_List.end(),
		[&](CObj* monster)
		{
			if (monster->Get_Name() == L"Zombie")
				zombieCount++;
		}
	);
	swprintf_s(str, L"남은 좀비 : %d", zombieCount);
	DEVICE->Get_Font()->DrawTextW(nullptr, str, -1, &rc, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CStage::Release(void)
{
	MGR(CObjMgr)->Delete_ID(OBJ_PLAYER);
	MGR(CObjMgr)->Delete_ID(OBJ_MONSTER);
	MGR(CObjMgr)->Delete_ID(OBJ_FEATURE);
	MGR(CCollisionMgr)->ClearColInfo();
}

void CStage::OnTimerEvent(int _iEventNum)
{
	if (_iEventNum == 0)
	{
		SpawnZombie();
	}

	else if(_iEventNum == 1)
	{
		SpawnRageZombie();
	}

}

void CStage::SpawnZombie()
{
	MGR(CObjMgr)->AddObject(OBJID::OBJ_MONSTER, CAbstractFactory<CZombie>::Create(float(WINCX /2 + rand() % 400), float(WINCY / 2 + rand() % 400), 0.f));

}

void CStage::SpawnRageZombie()
{
	MGR(CObjMgr)->AddObject(OBJID::OBJ_MONSTER, CAbstractFactory<CGiantZombie>::Create(float(WINCX / 2  + rand() % 400), float(WINCY / 2 + rand() % 400), 0.f));
}

void CStage::SpawnItem()
{
	CObj* Coin = CAbstractFactory<CCoin>::Create();
	Coin->Set_Pos(DXV3(float(rand() % WINCX), float(rand() % WINCY), 0.f));
	MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin);

}




