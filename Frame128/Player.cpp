#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "CBullet_Pistol.h"
#include "CBullet_SMG.h"

#include "AbstractFactory.h"

CPlayer::CPlayer()
	: tik(0.f), time(1.f), bFire(true)
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

}

int CPlayer::Update(void)
{
	if (false == m_bActive)
		return OBJ_DEAD;

	key_input();
	player_direction(m_eDirection);
	CalcMat();//이동과 회전 관련 매트릭스 처리를 관리하는 함수
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

	EllipseDrawCenter(hDC
		, int(m_vWorldPoint[1].x)
		, int(m_vWorldPoint[1].y)
		, 10, 10);

	EllipseDrawCenter(hDC, m_vWorldPoint[2].x, m_vWorldPoint[2].y, 10, 10);

	for (auto& iter : m_vecComponents)
        iter->Render(hDC);
}

void CPlayer::Release(void)
{
    for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
    m_vecComponents.clear();
    m_strName.clear();
}

void CPlayer::key_input()
{
	m_fSpeed = 100.f;
	player_movement();
	player_change_gun();


		if (MGR(CKeyMgr)->isStayKeyDown(VK_SPACE))
		{
			if (bFire == true)
			{
				bFire = false;

				tik += DT;

				if (tik >= time)
				{
					tik = 0;
					bFire = true;
				}
			}
		}
	
	
	
	


	CalcMat();
}

void CPlayer::player_movement()
{
	if (MGR(CKeyMgr)->isStayKeyDown(VK_UP))
	{
		m_eDirection = DIRECTION::UP;

		if (MGR(CKeyMgr)->isStayKeyDown(VK_LEFT))
			m_eDirection = DIRECTION::UPLEFT;
		else if (MGR(CKeyMgr)->isStayKeyDown(VK_RIGHT))
			m_eDirection = DIRECTION::UPRIGHT;
	}

	else if (MGR(CKeyMgr)->isStayKeyDown(VK_DOWN))
	{
		m_eDirection = DIRECTION::DOWN;

		if (MGR(CKeyMgr)->isStayKeyDown(VK_LEFT))
			m_eDirection = DIRECTION::DOWNLEFT;
		else if (MGR(CKeyMgr)->isStayKeyDown(VK_RIGHT))
			m_eDirection = DIRECTION::DOWNRIGHT;
	}

	else if (MGR(CKeyMgr)->isStayKeyDown(VK_LEFT))
		m_eDirection = DIRECTION::LEFT;

	else if (MGR(CKeyMgr)->isStayKeyDown(VK_RIGHT))
		m_eDirection = DIRECTION::RIGHT;

	else
	{
		m_eDirection = DIRECTION::NONE;
		m_fSpeed = 0.f;
	}
}

void CPlayer::player_change_gun()
{
	if (MGR(CKeyMgr)->isOnceKeyUp('M'))
		m_ePlayerGun = GUN_TYPE::PISTOL;

	if (MGR(CKeyMgr)->isOnceKeyUp('N'))
		m_ePlayerGun = GUN_TYPE::SMG;
}

void CPlayer::player_direction(DIRECTION _eDir)
{
	switch (_eDir)
	{

	case DIRECTION::UP:
		// m_vDir = { 0.f, -1.f, 0.f };
		m_fRadian = D3DXToRadian(-90);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWN:
		// m_vDir = { 0.f, 1.f, 0.f };
		m_fRadian = D3DXToRadian(90);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::LEFT:
		// m_vDir = { -1.f, 0.f, 0.f };
		m_fRadian = D3DXToRadian(-180);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::RIGHT:
		// m_vDir = { 1.f, 0.f, 0.f };
		m_fRadian = D3DXToRadian(0);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::UPLEFT:
		m_fRadian = D3DXToRadian(-135);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::UPRIGHT:
		// m_vDir = { 1.f, -1.f, 0.f };
		m_fRadian = D3DXToRadian(-45);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNLEFT:
		// m_vDir = { -1.f, 1.f, 0.f };
		m_fRadian = D3DXToRadian(135);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNRIGHT:
		// m_vDir = { 1.f, 1.f, 0.f };
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
