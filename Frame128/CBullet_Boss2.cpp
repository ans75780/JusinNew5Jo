#include "stdafx.h"
#include "CBullet_Boss2.h"

#include "Collider.h"
#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Stat.h"
#include "Monster.h"

CBullet_Boss2::CBullet_Boss2() {}

CBullet_Boss2::~CBullet_Boss2() { Release(); }

void CBullet_Boss2::Init()
{
	m_vPos = {
		MGR(CObjMgr)->Get_Boss1()->Get_Pos().x,
		MGR(CObjMgr)->Get_Boss1()->Get_Pos().y,
		0.f
	};

	m_vScale = { 300.f, 10.f, 0.f };

	m_fAtk = 50.f;

	Set_Initial_Points();

	m_fSpeed = 100.f;

	m_bActive = true;

	m_eID = OBJID::OBJ_BOSS_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Boss_hyde_bullet2";

	Set_Matrix_to_Identity();
	CreateCollider();

	m_iSpreadRate = 50;
	m_fSpreadX = create_x_spread();
	m_fSpreadY = create_y_spread();

	FindTarget();
}

int CBullet_Boss2::Update()
{
	if (m_fLifeTime >= 2)
		return OBJ_DEAD;

	if (false == m_bActive)
		return OBJ_DEAD;

	m_fBulletSizeRate -= 0.1f;
	if (m_fBulletSizeRate <= 0)
		return OBJ_DEAD;


	SetRadianToPlayer();

	D3DXMatrixScaling(&m_matScale, m_fBulletSizeRate, m_fBulletSizeRate, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fRadian);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	m_vPos += m_vWorldDir * m_fSpeed * DT;

	return OBJ_NOEVENT;
}

void CBullet_Boss2::OnCollision(CCollider * _pOther)
{
}

void CBullet_Boss2::OnCollisionEnter(CCollider * _pOther)
{
}

void CBullet_Boss2::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet_Boss2::OnTrigger(CCollider * _pOther)
{
}

void CBullet_Boss2::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet_Boss2::OnTriggerExit(CCollider * _pOther)
{
}