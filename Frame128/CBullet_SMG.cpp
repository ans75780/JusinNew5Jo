#include "stdafx.h"
#include "CBullet_SMG.h"

#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"

CBullet_SMG::CBullet_SMG() {}

CBullet_SMG::~CBullet_SMG() { Release(); }

void CBullet_SMG::Init()
{
	m_vPos = { MGR(CObjMgr)->Get_Player()->Get_Pos().x + 45.f * cosf(MGR(CObjMgr)->Get_Player()->Get_Angle())
		, MGR(CObjMgr)->Get_Player()->Get_Pos().y - 45.f * sinf(MGR(CObjMgr)->Get_Player()->Get_Angle())
		, 0.f };
	m_vScale = { 10.f, 10.f, 0.f };

	m_strName = L"Bullet_SMG";

	Set_Initial_Points();

	m_bActive = true;
	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;

	Set_Matrix_to_Identity();

	m_fSpeed = 500.f;

	switch (dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->get_eDir())
	{
	case DIRECTION::UP:
	{
		float tempx = float(rand() % 15) / 100.f;
		int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
		float x_final = float(tempx) * tempx2;
		m_vDir = { x_final, -1.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}


	case DIRECTION::DOWN:
	{
		float tempx = float(rand() % 15) / 100.f;
		int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
		float x_final = float(tempx) * tempx2;
		m_vDir = { x_final, 1.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}


	case DIRECTION::LEFT:
	{
		float tempx = float(rand() % 15) / 100.f;
		int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
		float x_final = float(tempx) * tempx2;
		m_vDir = { -1.f, x_final, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}


	case DIRECTION::RIGHT:
	{
		float tempx = float(rand() % 15) / 100.f;
		int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
		float x_final = float(tempx) * tempx2;
		m_vDir = { 1.f, x_final, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}


	case DIRECTION::UPLEFT:
	{
		float tempx = float(rand() % 15) / 100.f;
		int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
		float x_final = float(tempx) * tempx2;

		float tempy = float(rand() % 15) / 100.f;
		int tempy2 = ((rand() % 2) == 0) ? 1 : -1;
		float y_final = float(tempy) * tempy2;

		m_vDir = { -1.f + x_final, -1.f + y_final, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}


	case DIRECTION::UPRIGHT:
	{
		float tempx = float(rand() % 15) / 100.f;
		int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
		float x_final = float(tempx) * tempx2;

		float tempy = float(rand() % 15) / 100.f;
		int tempy2 = ((rand() % 2) == 0) ? 1 : -1;
		float y_final = float(tempy) * tempy2;

		m_vDir = { 1.f + x_final, -1.f + y_final, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}


	case DIRECTION::DOWNLEFT:
	{
		float tempx = float(rand() % 15) / 100.f;
		int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
		float x_final = float(tempx) * tempx2;

		float tempy = float(rand() % 15) / 100.f;
		int tempy2 = ((rand() % 2) == 0) ? 1 : -1;
		float y_final = float(tempy) * tempy2;

		m_vDir = { -1.f + x_final, 1.f + y_final, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}


	case DIRECTION::DOWNRIGHT:
	{
		float tempx = float(rand() % 15) / 100.f;
		int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
		float x_final = float(tempx) * tempx2;

		float tempy = float(rand() % 15) / 100.f;
		int tempy2 = ((rand() % 2) == 0) ? 1 : -1;
		float y_final = float(tempy) * tempy2;

		m_vDir = { 1.f + x_final, 1.f + y_final, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}
	}

	CreateCollider();
}

int CBullet_SMG::Update()
{
	return 0;
}

void CBullet_SMG::Render(HDC hDC)
{
}

void CBullet_SMG::Release()
{
}

void CBullet_SMG::OnCollision(CCollider * _pOther)
{
}

void CBullet_SMG::OnCollisionEnter(CCollider * _pOther)
{
}

void CBullet_SMG::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet_SMG::OnTrigger(CCollider * _pOther)
{
}

void CBullet_SMG::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet_SMG::OnTriggerExit(CCollider * _pOther)
{
}
