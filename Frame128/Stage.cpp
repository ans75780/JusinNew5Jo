#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "Feature.h"
#include "CollisionMgr.h"

#include "CPistol.h"

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

	return S_OK;
}

void CStage::Update(void)
{
	MGR(CObjMgr)->Update();
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
		MGR(CObjMgr)->Get_ObjList(OBJID::OBJ_BULLET),
		MGR(CObjMgr)->Get_ObjList(OBJ_FEATURE)
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




