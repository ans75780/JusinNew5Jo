#include "stdafx.h"
#include "Stage.h"

#include "UserDefineHeaders.h"

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

	MGR(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	MGR(CObjMgr)->AddObject(OBJ_FEATURE, CAbstractFactory<CFeature>::Create(100,100,0));
	
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

	MGR(CTimeMgr)->AddLoopEvent(2.f, this, 0);
	MGR(CTimeMgr)->AddLoopEvent(1.5f, this, 1);

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
		SpawnItem();
	}

}

void CStage::SpawnZombie()
{
	MGR(CObjMgr)->AddObject(OBJID::OBJ_MONSTER, CAbstractFactory<CZombie>::Create(WINCX + rand() % 400, WINCY + rand() % 400, 0));

}

void CStage::SpawnItem()
{
	CObj* Coin = CAbstractFactory<CCoin>::Create();
	Coin->Set_Pos(DXV3(rand() % WINCX, rand() % WINCY, 0.f));
	MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin);

}




