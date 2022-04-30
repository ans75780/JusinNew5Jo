#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "CBullet_Pistol.h"
#include "Device.h"
#include "AbstractFactory.h"
#include "CGun.h"
#include "CPistol.h"
#include "CSMG.h"
#include "CShotgun.h"
#include "AbstractFactory.h"

CPlayer::CPlayer()
	: tik(0.f), time(0.f), bPressSpace(false), bShoot(false)
{
}

CPlayer::~CPlayer() { Release(); }

void CPlayer::Init(void)
{
	m_vPos = { WINCX / 2.f, WINCY / 2.f, 0.f };
	m_vScale = { 50.f, 50.f, 0.f };

	m_vPoint[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	m_vPoint[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };

	m_fSpeed = 100.f;

	m_bActive = true;
	m_eID = OBJID::OBJ_PLAYER;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Player";

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotZ);
	D3DXMatrixIdentity(&m_matTrans);

	CreateCollider();

	m_fRadian = D3DXToRadian(-90.f);

	time = 0.06f;
}

int CPlayer::Update(void)
{
	if (false == m_bActive)
		return OBJ_DEAD;

	key_input();
	player_direction(m_eDirection);
	CalcMat();

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	m_vMoveSize = m_vWorldDir * m_fSpeed * DT;

	m_vPos += m_vMoveSize;

	return OBJ_NOEVENT;
}

void CPlayer::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));

	EllipseDrawCenter(hDC
		, int(m_vWorldPoint[1].x)
		, int(m_vWorldPoint[1].y), 10, 10);

	EllipseDrawCenter(hDC
		, int(m_vWorldPoint[2].x)
		, int(m_vWorldPoint[2].y)
		, 10, 10);

	for (auto& iter : m_vecComponents)
        iter->Render(hDC);
}

void CPlayer::Release(void)
{
    
}

void CPlayer::key_input()
{
	m_fSpeed = 100.f;

	player_movement();
	player_change_gun();


	if (KEYHOLD(E))
	{
		bShoot = false;
		tik += DT;
		if (tik >= time)
		{
			bShoot = true;
			tik = 0.f;
		}
	}

	if (KEYAWAY(E))
	{
		tik = 0.f;
		bShoot = false;
	}


	CalcMat();
}

void CPlayer::player_movement()
{
	if (KEYHOLD(UP))
	{
		m_eDirection = DIRECTION::UP;

		if (KEYHOLD(LEFT))
			m_eDirection = DIRECTION::UPLEFT;
		else if (KEYHOLD(RIGHT))
			m_eDirection = DIRECTION::UPRIGHT;
	}
	else if (KEYHOLD(DOWN))
	{
		m_eDirection = DIRECTION::DOWN;

		if (KEYHOLD(LEFT))
			m_eDirection = DIRECTION::DOWNLEFT;
		else if (KEYHOLD(RIGHT))
			m_eDirection = DIRECTION::DOWNRIGHT;
	}
	else if (KEYHOLD(LEFT))
		m_eDirection = DIRECTION::LEFT;
	else if (KEYHOLD(RIGHT))
		m_eDirection = DIRECTION::RIGHT;

	else
	{
		m_eDirection = DIRECTION::NONE;
		m_fSpeed = 0.f;
	}

	CalcMat();
}

void CPlayer::player_change_gun()
{
	if (KEYAWAY(Q))
	{
		if (nullptr != m_pGun) m_pGun->Set_Active(false);

		m_ePlayerGun = GUN_TYPE::PISTOL;
		MGR(CObjMgr)->AddObject(OBJID::OBJ_GUN, CAbstractFactory<CPistol>::Create());
		time = m_pGun->Get_ShotInterval();
	}
		

	if (KEYAWAY(W))
	{
		if (nullptr != m_pGun)
			m_pGun->Set_Active(false);
		else if (nullptr == m_pGun)

		m_ePlayerGun = GUN_TYPE::SMG;
		MGR(CObjMgr)->AddObject(OBJID::OBJ_GUN, CAbstractFactory<CSMG>::Create());
		time = m_pGun->Get_ShotInterval();
	}
}

void CPlayer::player_direction(DIRECTION _eDir)
{
	switch (_eDir)
	{

	case DIRECTION::UP:
		m_fRadian = D3DXToRadian(-90);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWN:
		m_fRadian = D3DXToRadian(90);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::LEFT:
		m_fRadian = D3DXToRadian(-180);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::RIGHT:
		m_fRadian = D3DXToRadian(0);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::UPLEFT:
		m_fRadian = D3DXToRadian(-135);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::UPRIGHT:
		m_fRadian = D3DXToRadian(-45);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNLEFT:
		m_fRadian = D3DXToRadian(135);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNRIGHT:
		m_fRadian = D3DXToRadian(45);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}
}

void CPlayer::OnCollision(CCollider * _pOther)
{
}

void CPlayer::OnCollisionEnter(CCollider * _pOther)
{
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
}

void CPlayer::OnTrigger(CCollider * _pOther)
{
}

void CPlayer::OnTriggerEnter(CCollider * _pOther)
{
}

void CPlayer::OnTriggerExit(CCollider * _pOther)
{
}
