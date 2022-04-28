#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "Feature.h"
#include "CollisionMgr.h"
#include "Zombie.h"
#include "CPistol.h"
#include "Hand.h"
CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

HRESULT CStage::Init(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"BackGround");

	MGR(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	MGR(CObjMgr)->AddObject(OBJ_FEATURE, CAbstractFactory<CFeature>::Create(100,100,0));
	MGR(CObjMgr)->AddObject(OBJID::OBJ_GUN, CAbstractFactory<CPistol>::Create());

	CObj* zombie = CAbstractFactory<CZombie>::Create();
	MGR(CObjMgr)->AddObject(OBJID::OBJ_MONSTER, zombie);
	CHand* hand = new CHand(zombie, DXV3(45, -15, 0));
	MGR(CObjMgr)->AddObject(OBJ_MONSTER, hand);
	hand = new CHand(zombie, DXV3(45, 15, 0));
	MGR(CObjMgr)->AddObject(OBJ_MONSTER, hand);


	return S_OK;
}

void CStage::Update(void)
{
	MGR(CObjMgr)->Update();
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
	HDC img = CBmpMgr::Get_Instance()->Find_Image(L"BackGround");
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




