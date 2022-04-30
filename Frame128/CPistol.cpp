#include "stdafx.h"
#include "CPistol.h"

#include "AbstractFactory.h"

#include "ObjMgr.h"
#include "UserDefineHeaders.h"

CPistol::CPistol()
{
}

CPistol::~CPistol()
{
}

void CPistol::Init()
{
	dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->set_gun(this);
	m_vPos = { 0.f, 0.f, 0.f };
	m_vScale = { 30.f, 10.f, 0.f };

	m_strName = L"Pistol";

	Set_Initial_Points();
	m_fShootInterval = 0.1f;

	m_bActive = true;
	m_eID = OBJID::OBJ_GUN;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_eType = GUN_TYPE::PISTOL;

	Set_Matrix_to_Identity();
}

int CPistol::Update()
{
	if (false == m_bActive)
		return OBJ_DEAD;

	float	PlayerRadian = MGR(CObjMgr)->Get_Player()->Get_Radian();

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, PlayerRadian);
	D3DXMatrixTranslation(&m_matTrans
		, MGR(CObjMgr)->Get_Player()->Get_Pos().x + 45.f * cosf(PlayerRadian)
		, MGR(CObjMgr)->Get_Player()->Get_Pos().y - 45.f * -sinf(PlayerRadian)
		, 0.f);
	
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	if (dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->shoot())
	{
		MGR(CObjMgr)->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<CBullet_Pistol>::Create());
	}
	return OBJ_NOEVENT;
}

void CPistol::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
}

void CPistol::Release()
{
}

void CPistol::OnCollision(CCollider * _pOther)
{
}

void CPistol::OnCollisionEnter(CCollider * _pOther)
{
}

void CPistol::OnCollisionExit(CCollider * _pOther)
{
}

void CPistol::OnTrigger(CCollider * _pOther)
{
}

void CPistol::OnTriggerEnter(CCollider * _pOther)
{
}

void CPistol::OnTriggerExit(CCollider * _pOther)
{
}
