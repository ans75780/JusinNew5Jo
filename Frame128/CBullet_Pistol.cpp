#include "stdafx.h"
#include "CBullet_Pistol.h"
#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
CBullet_Pistol::CBullet_Pistol()
{
}

CBullet_Pistol::~CBullet_Pistol()
{
}

void CBullet_Pistol::Init()
{
	m_vPos = { 0.f, 0.f, 0.f };
	m_vScale = { 10.f, 10.f, 0.f };

	m_strName = L"Bullet_Pistol";

	Set_Initial_Points();

	m_bActive = true;
	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;

	Set_Matrix_to_Identity();

	m_fSpeed = 300.f;

	m_iSpreadRate = 10.f;
	m_fSpreadX = create_x_spread();
	m_fSpreadY = create_y_spread();

	set_bullet_dir(dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->get_eDir());

	vInitPos = MGR(CObjMgr)->Get_Player()->Get_Pos();

	CreateCollider();

	m_vLocalPos = m_vPos;
}
	
int CBullet_Pistol::Update()
{
		m_fLifeTime += DT;

		if (false == m_bActive)
			return OBJ_DEAD;

		if (m_fLifeTime >= 3)
			return OBJ_DEAD;

		m_vPos += m_vDir * m_fSpeed * DT;
		m_vLocalPos += m_vDir * m_fSpeed * DT;

		D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);

		D3DXMatrixTranslation(&m_matTrans
			, m_vPos.x
			, m_vPos.y, 0.f);

		D3DXMatrixTranslation(&m_matPos
			, m_vLocalPos.x
			, m_vLocalPos.y, 0.f);

		D3DXMatrixScaling(&m_matScale
			, 1.f
			, 1.f
			, 0.f);

		D3DXMatrixTranslation(&m_matTrans
			, vInitPos.x
			, vInitPos.y
			, 0.f);

		m_matWorld = m_matPos * m_matScale * m_matTrans;

		for (int i(0); i < 4; ++i)
		{
			D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
		}
		return OBJ_NOEVENT;
	}

void CBullet_Pistol::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));

	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}


void CBullet_Pistol::Release()
{
	for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
	m_vecComponents.clear();
	m_strName.clear();
}

void CBullet_Pistol::OnCollision(CCollider * _pOther)
{
}

void CBullet_Pistol::OnCollisionEnter(CCollider * _pOther)
{

	int a = 1;
}

void CBullet_Pistol::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet_Pistol::OnTrigger(CCollider * _pOther)
{
}

void CBullet_Pistol::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet_Pistol::OnTriggerExit(CCollider * _pOther)
{
}
