#include "stdafx.h"
#include "CBullet_SMG.h"

#include "Collider.h"
#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Stat.h"
#include "Monster.h"


CBullet_SMG::CBullet_SMG()
{
}

CBullet_SMG::~CBullet_SMG()
{
}

void CBullet_SMG::Init()
{
	m_vPos = { MGR(CObjMgr)->Get_Player()->Get_Pos().x
		, MGR(CObjMgr)->Get_Player()->Get_Pos().y
		, 0.f };

	m_vScale = { 12.f, 12.f, 0.f };

	m_fAtk = 1.f;

	Set_Initial_Points();

	m_fSpeed = 500.f;
	
	m_bActive = true;
	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Bullet_SMG";

	Set_Matrix_to_Identity();
	CreateCollider();

	m_iSpreadRate = 30.f;
	m_fSpreadX = create_x_spread();
	m_fSpreadY = create_y_spread();

	set_bullet_dir(dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->get_eDir());
}

int CBullet_SMG::Update()
{
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

void CBullet_SMG::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));

	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}

void CBullet_SMG::Release()
{
	for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
	m_vecComponents.clear();
	m_strName.clear();
}

void CBullet_SMG::OnCollision(CCollider * _pOther)
{
}

void CBullet_SMG::OnCollisionEnter(CCollider * _pOther)
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
