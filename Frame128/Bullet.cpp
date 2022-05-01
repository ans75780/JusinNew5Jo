#include "stdafx.h"
#include "Bullet.h"

#include "Device.h"
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

int CBullet::Update()
{
	float tempDT = DT;
	m_fLifeTime += DT;
	if (m_fLifeTime >= 3)
		return OBJ_DEAD;

	if (false == m_bActive)
		return OBJ_DEAD;

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);

	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = m_matScale * m_matTrans;


	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	m_vPos += m_vWorldDir * m_fSpeed * DT;

	return OBJ_NOEVENT;
}

void CBullet::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));

	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}

void CBullet::Release()
{
	for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
	m_vecComponents.clear();
	m_strName.clear();
}

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
