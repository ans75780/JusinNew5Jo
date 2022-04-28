#include "stdafx.h"
#include "CBullet_Pistol.h"

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
	m_vDir = { 0.f, -1.f, 0.f };

	Set_Initial_Points();

	m_bActive = true;
	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;

	Set_Matrix_to_Identity();

	D3DXMatrixTranslation(&m_matTrans
		, MGR(CObjMgr)->Get_Player()->Get_Pos().x
		, MGR(CObjMgr)->Get_Player()->Get_Pos().y
		, 0.f);

	CreateCollider();
}

int CBullet_Pistol::Update()
{
	m_fLifeTime += DT;

	if (false == m_bActive)
		return OBJ_DEAD;

	if (m_fLifeTime >= 3)
		return OBJ_DEAD;

	m_fRadian = MGR(CObjMgr)->Get_Player()->Get_Angle();

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fRadian);
	D3DXMatrixTranslation(&m_matTrans
		, m_vPos.x
		, m_vPos.y
		, 0.f);


	// 총알이 나가게 할건데
	m_vPos.x += cosf(m_fRadian) * m_fSpeed * DT;
	m_vPos.y -= sinf(m_fRadian) * m_fSpeed * DT;
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);
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
}


void CBullet_Pistol::Release()
{
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
