#include "stdafx.h"
#include "Bullet.h"

#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Collider.h"

CBullet::CBullet()
	: m_fLifeTime(0.f), m_iSpreadRate(0),
	m_fSpreadX(0.f), m_fSpreadY(0.f),
	m_fAtk(0.f)
{
	D3DXMatrixIdentity(&m_matPos);
	ZeroMemory(&m_vWorldPos, sizeof(DXV3));
	ZeroMemory(&m_vLocalPos, sizeof(DXV3));
}

CBullet::~CBullet() {}

float CBullet::create_x_spread()
{
	float tempx = float(rand() % m_iSpreadRate) / 100.f;
	int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
	float x_final = float(tempx) * tempx2;

	return x_final;
}

float CBullet::create_y_spread()
{
	float tempy = float(rand() % m_iSpreadRate) / 100.f;
	int tempy2 = ((rand() % 2) == 0) ? 1 : -1;
	float y_final = float(tempy) * tempy2;

	return y_final;
}

void CBullet::set_bullet_dir(DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIRECTION::UP:
		m_vDir = { m_fSpreadX, -1.f, 0.f };
		break;
	case DIRECTION::DOWN:
		m_vDir = { m_fSpreadX, 1.f, 0.f };
		break;
	case DIRECTION::LEFT:
		m_vDir = { -1.f, m_fSpreadY, 0.f };
		break;
	case DIRECTION::RIGHT:
		m_vDir = { 1.f, m_fSpreadY, 0.f };
		break;
	case DIRECTION::UPLEFT:
		m_vDir = { -1.f + m_fSpreadX, -1.f + m_fSpreadY, 0.f };
		break;
	case DIRECTION::UPRIGHT:
		m_vDir = { 1.f + m_fSpreadX, -1.f + m_fSpreadY, 0.f };
		break;
	case DIRECTION::DOWNLEFT:
		m_vDir = { -1.f + m_fSpreadX, 1.f + m_fSpreadY, 0.f };
		break;
	case DIRECTION::DOWNRIGHT:
		m_vDir = { 1.f + m_fSpreadX, 1.f + m_fSpreadY, 0.f };
		break;
	}

	D3DXVec3Normalize(&m_vDir, &m_vDir);
}
