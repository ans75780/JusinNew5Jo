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
	
	for (int i = 0; i < 2; i++)
	{
		MGR(CObjMgr)->AddObject(OBJID::OBJ_MONSTER, CAbstractFactory<CZombie>::Create(WINCX + rand() % 400, WINCY + rand () % 400, 0));
	}

	CObj* Coin = CAbstractFactory<CCoin>::Create();
	Coin->Set_Pos(DXV3(300.f, 100.f, 0.f));
	MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin);

	CObj* Coin2 = CAbstractFactory<CCoin>::Create();
	Coin2->Set_Pos(DXV3(600.f, 300.f, 0.f));
	MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin2);

	CObj* Coin3 = CAbstractFactory<CCoin>::Create();
	Coin3->Set_Pos(DXV3(200.f, 300.f, 0.f));
	MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin3);



	return S_OK;
}

void CStage::Update(void)
{
	MGR(CObjMgr)->Update();
	MGR(CKeyMgr)->update();
}

void CStage::Late_Update(void)
{
	MGR(CObjMgr)->Late_Update();
	
	//面倒贸府 诀单捞飘
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
	MGR(CObjMgr)->Render(hDC);
}

void CStage::Release(void)
{
	MGR(CObjMgr)->Delete_ID(OBJ_PLAYER);
	MGR(CObjMgr)->Delete_ID(OBJ_MONSTER);
	MGR(CObjMgr)->Delete_ID(OBJ_FEATURE);
	MGR(CCollisionMgr)->ClearColInfo();
}




