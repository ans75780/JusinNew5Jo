#include "stdafx.h"
#include "CBullet_Boss3.h"

#include "Collider.h"
#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Stat.h"
#include "Monster.h"

CBullet_Boss3::CBullet_Boss3()
{}

CBullet_Boss3::~CBullet_Boss3() { Release(); }

void CBullet_Boss3::Init()
{
	m_vPos = {
		MGR(CObjMgr)->Get_Boss1()->Get_Pos().x,
		MGR(CObjMgr)->Get_Boss1()->Get_Pos().y,
		0.f
	};

	m_vScale = { 10.f, 10.f, 0.f };

	m_fAtk = 50.f;

	Set_Initial_Points();

	m_fSpeed = 240.f;

	m_bActive = true;

	m_eID = OBJID::OBJ_BOSS_BULLET3;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Boss_hyde_bullet3";

	Set_Matrix_to_Identity();
	CreateCollider();

	m_iSpreadRate = 10;
	m_fSpreadX = create_x_spread();
	m_fSpreadY = create_y_spread();

	FindTarget();
	SetRadianToPlayer();
}

int CBullet_Boss3::Update()
{
	m_bNowAppear = false;

	m_fLifeTime += DT;

	if (m_fLifeTime >= 3)
		return OBJ_DEAD;

	if (false == m_bActive)
		return OBJ_DEAD;

	m_fBulletSizeRate += 0.05f;
	if (m_fBulletSizeRate >= 3.f)
		return OBJ_DEAD;



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

void CBullet_Boss3::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
}

void CBullet_Boss3::OnCollision(CCollider * _pOther)
{
}

void CBullet_Boss3::OnCollisionEnter(CCollider * _pOther)
{
}

void CBullet_Boss3::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet_Boss3::OnTrigger(CCollider * _pOther)
{
}

void CBullet_Boss3::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet_Boss3::OnTriggerExit(CCollider * _pOther)
{
}
