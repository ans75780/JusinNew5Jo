#include "stdafx.h"
#include "CBullet_Boss.h"

#include "Collider.h"
#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Stat.h"
#include "Monster.h"

CBullet_Boss::CBullet_Boss()
	: m_fReduceRate(0.f), m_fBulletSizeRate(1.f)
{}

CBullet_Boss::~CBullet_Boss() { Release(); }

void CBullet_Boss::Init()
{
	m_vPos = {
		MGR(CObjMgr)->Get_Boss1()->Get_Pos().x,
		MGR(CObjMgr)->Get_Boss1()->Get_Pos().y,
		0.f
	};

	m_vScale = { 50.f, 50.f, 0.f };

	m_fAtk = 50.f;

	Set_Initial_Points();

	m_fSpeed = 300.f;

	m_bActive = true;

	m_eID = OBJID::OBJ_BOSS_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Boss_hyde_bullet";

	Set_Matrix_to_Identity();
	CreateCollider();

	m_iSpreadRate = 30;
	m_fSpreadX = create_x_spread();
	m_fSpreadY = create_y_spread();

	FindTarget();
	SetRadianToPlayer();
}

int CBullet_Boss::Update()
{
	if (m_fLifeTime >= 3)
		return OBJ_DEAD;

	if (false == m_bActive)
		return OBJ_DEAD;

	m_fBulletSizeRate -= 0.01f;
	if (m_fBulletSizeRate <= 0)
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

void CBullet_Boss::OnCollision(CCollider * _pOther)
{
}

void CBullet_Boss::OnCollisionEnter(CCollider * _pOther)
{
}

void CBullet_Boss::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet_Boss::OnTrigger(CCollider * _pOther)
{
}

void CBullet_Boss::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet_Boss::OnTriggerExit(CCollider * _pOther)
{
}

void CBullet_Boss::FindTarget()
{
	m_pTarget = MGR(CObjMgr)->Get_Player();
}

void CBullet_Boss::SetRadianToPlayer()
{
	//플레이어에서 자신의 위치를 빼서 방향벡터를 만들고, 정규화시켜줌
	D3DXVECTOR3 dirVec = m_pTarget->Get_Pos() - m_vPos;
	D3DXVec3Normalize(&dirVec, &dirVec);//정규화된 벡터나옴.
	//룩 벡터랑(가로) 정규화된 방향 벡터랑 내적한 값(코사인)을 아크코사인에 넣어 라디안값으로변경
	m_fRadian = acosf(D3DXVec3Dot(&m_vDir, &dirVec));
	if (m_vPos.y > m_pTarget->Get_Pos().y)
	{
		m_fRadian = PI2 - m_fRadian;
	}
}
