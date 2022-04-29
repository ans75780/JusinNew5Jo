#include "stdafx.h"
#include "CBullet_Pistol.h"

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
	m_vPos = { MGR(CObjMgr)->Get_Player()->Get_Pos().x + 45.f * cosf(MGR(CObjMgr)->Get_Player()->Get_Angle())
		, MGR(CObjMgr)->Get_Player()->Get_Pos().y - 45.f * sinf(MGR(CObjMgr)->Get_Player()->Get_Angle())
		, 0.f };
	m_vScale = { 10.f, 10.f, 0.f };

	m_strName = L"Bullet_Pistol";
	m_vDir = { 0.f, 1.f, 0.f };

	Set_Initial_Points();

	m_bActive = true;
	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;

	Set_Matrix_to_Identity();

	m_fSpeed = 300.f;

	m_fRadian = MGR(CObjMgr)->Get_Player()->Get_Radian();

	switch (dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->get_eDir())
	{
	case DIRECTION::UP:
		m_vDir = { 0.f, -1.f, 0.f };
		break;

	case DIRECTION::DOWN:
		m_vDir = { 0.f, 1.f, 0.f };
		break;

	case DIRECTION::LEFT:
		m_vDir = { -1.f, 0.f, 0.f };
		break;

	case DIRECTION::RIGHT:
		m_vDir = { 1.f, 0.f, 0.f };
		break;

	case DIRECTION::UPLEFT:
		m_vDir = { -1.f, -1.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::UPRIGHT:
		m_vDir = { 1.f, -1.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNLEFT:
		m_vDir = { -1.f, 1.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNRIGHT:
		m_vDir = { 1.f, 1.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}

	CreateCollider();
}

int CBullet_Pistol::Update()
{
	m_fLifeTime += DT;

	if (false == m_bActive)
		return OBJ_DEAD;

	if (m_fLifeTime >= 3)
		return OBJ_DEAD;
	
	
	

	m_vPos += m_vDir * m_fSpeed * DT;

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	// D3DXMatrixRotationZ(&m_matRotZ, m_fRadian);
	D3DXMatrixTranslation(&m_matTrans
		, m_vPos.x
		, m_vPos.y
		, 0.f);


	// 총알이 나가게 할건데
	
	m_matWorld = m_matScale/* * m_matRotZ */* m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	// D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	
	
	return OBJ_NOEVENT;
}

void CBullet_Pistol::Render(HDC hDC)
{
	MoveToEx(hDC
		, int(m_vWorldPoint[0].x)
		, int(m_vWorldPoint[0].y)
		, nullptr);

	for (int i(1); i < 4; ++i)
	{
		LineTo(hDC
			, int(m_vWorldPoint[i].x)
			, int(m_vWorldPoint[i].y));
	}

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
