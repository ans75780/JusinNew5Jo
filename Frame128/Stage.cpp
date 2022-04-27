#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "Feature.h"
#include "CollisionMgr.h"

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

	OBJMANAGER->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	OBJMANAGER->AddObject(OBJ_FEATURE, CAbstractFactory<CFeature>::Create(100,100,0));


	return S_OK;
}

void CStage::Update(void)
{
	OBJMANAGER->Update();
}

void CStage::Late_Update(void)
{
	OBJMANAGER->Late_Update();
	//面倒贸府 诀单捞飘
	COLLISIONMANAGER->CollisionUpdate
	(
		OBJMANAGER->Get_ObjList(OBJ_PLAYER),
		OBJMANAGER->Get_ObjList(OBJ_MONSTER)
	);

	COLLISIONMANAGER->CollisionUpdate
	(
		OBJMANAGER->Get_ObjList(OBJ_PLAYER),
		OBJMANAGER->Get_ObjList(OBJ_FEATURE)
	);

	COLLISIONMANAGER->CollisionUpdate
	(
		OBJMANAGER->Get_ObjList(OBJID::OBJ_BULLET),
		OBJMANAGER->Get_ObjList(OBJ_FEATURE)
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
	OBJMANAGER->Render(hDC);
}

void CStage::Release(void)
{
	OBJMANAGER->Delete_ID(OBJ_PLAYER);
	OBJMANAGER->Delete_ID(OBJ_MONSTER);
	OBJMANAGER->Delete_ID(OBJ_FEATURE);
	COLLISIONMANAGER->ClearColInfo();
}




