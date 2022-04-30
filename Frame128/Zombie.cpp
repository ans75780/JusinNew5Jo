#include "stdafx.h"
#include "Zombie.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "CBullet_Pistol.h"

#include "AbstractFactory.h"
#include "Hand.h"
#include "UserDefineHeaders.h"

CZombie::CZombie()
{
}

CZombie::~CZombie()
{
	Release();
}

void CZombie::Init(void)
{
	m_vPos = { 400, 100, 0.f };
	m_vScale = { 50.f, 50.f, 0.f };

	m_vPoint[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	m_vPoint[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };

	m_fSpeed = 25;

	m_bActive = true;
	m_eID = OBJID::OBJ_MONSTER;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Zombie";

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotZ);
	D3DXMatrixIdentity(&m_matTrans);

	CreateCollider();
	FindTarget();
	CHand* hand = new CHand(this, DXV3(45, -15, 0));
	MGR(CObjMgr)->AddObject(OBJ_MONSTER, hand);
	hand = new CHand(this, DXV3(45, 15, 0));
	MGR(CObjMgr)->AddObject(OBJ_MONSTER, hand);

}

int CZombie::Update(void)
{
	SetRadianToPlayer();
	//m_fRadian = D3DXToRadian(90.f);
	CalcMat();
	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);
	m_vMoveSize = m_vWorldDir * m_fSpeed * DT;

	m_vPos += m_vMoveSize;
	int a = 10;


    return 0;
}

void CZombie::Render(HDC hDC)
{
	MoveToEx(hDC
		, int(m_vWorldPoint[0].x)
		, int(m_vWorldPoint[0].y)
		, nullptr);

	for (int i(1); i < sizeof(4); ++i)
	{
		LineTo(hDC
			, int(m_vWorldPoint[i].x)
			, int(m_vWorldPoint[i].y));
	}

	LineTo(hDC
		, int(m_vWorldPoint[0].x)
		, int(m_vWorldPoint[0].y));

	EllipseDrawCenter(hDC, m_vWorldPoint[1].x, m_vWorldPoint[1].y, 10, 10);
	EllipseDrawCenter(hDC, m_vWorldPoint[2].x, m_vWorldPoint[2].y, 10, 10);
	m_vecComponents[0]->Render(hDC);
}

void CZombie::Release(void)
{
}

void CZombie::Set_Active(bool _isActive)
{
	CObj::Set_Active(_isActive);

	if (!_isActive)
	{
		CObj* Coin = CAbstractFactory<CCoin>::Create();
		Coin->Set_Pos(m_vPos);
		MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin);
	}
}
