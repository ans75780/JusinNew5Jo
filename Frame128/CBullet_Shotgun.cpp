#include "stdafx.h"
#include "CBullet_Shotgun.h"

#include "Collider.h"
#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Stat.h"
#include "Monster.h"

CBullet_Shotgun::CBullet_Shotgun()
	: m_fReduceRate(0.f), m_fBulletSizeRate(1.f)
{
}

CBullet_Shotgun::~CBullet_Shotgun()
{
}

void CBullet_Shotgun::Init()
{
	m_vPos = { MGR(CObjMgr)->Get_Player()->Get_Pos().x
		, MGR(CObjMgr)->Get_Player()->Get_Pos().y
		, 0.f };

	m_vScale = { 30.f, 30.f, 0.f };

	m_fAtk = 10.f;

	Set_Initial_Points();

	m_fSpeed = 800.f;

	m_bActive = true;
	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Bullet_Shotgun";

	Set_Matrix_to_Identity();
	CreateCollider();
	

	m_iSpreadRate = 50;
	m_fSpreadX = create_x_spread();
	m_fSpreadY = create_y_spread();

	set_bullet_dir(dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->get_eDir());
}

int CBullet_Shotgun::Update()
{
	if (m_fLifeTime >= 3)
		return OBJ_DEAD;

	if (false == m_bActive)
		return OBJ_DEAD;

	m_fBulletSizeRate -= 0.04f;
	if (m_fBulletSizeRate <= 0)
		return OBJ_DEAD;

	D3DXMatrixScaling(&m_matScale, m_fBulletSizeRate, m_fBulletSizeRate, 0.f);

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

void CBullet_Shotgun::OnCollision(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnCollisionEnter(CCollider * _pOther)
{
	if (_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_MONSTER)
	{
		if (_pOther->Get_Owner()->Get_Name() == L"Zombie")
		{
			dynamic_cast<CMonster*>(_pOther->Get_Owner())->Get_Stat().Damaged(m_fAtk);
		}
		m_bActive = false;
	}
}

void CBullet_Shotgun::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTrigger(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTriggerExit(CCollider * _pOther)
{
}
