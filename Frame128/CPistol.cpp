#include "stdafx.h"
#include "CPistol.h"

#include "Device.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

#include "Player.h"
#include "CBullet_Pistol.h"
#include "SoundMgr.h"
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
	m_fShootInterval = 0.5f;

	m_bActive = true;
	m_eID = OBJID::OBJ_GUN;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_eType = GUN_TYPE::PISTOL;

	Set_Matrix_to_Identity();
}

int CPistol::Update()
{
	float	player_Radian = MGR(CObjMgr)->Get_Player()->Get_Radian();
	DXV3	player_Pos = MGR(CObjMgr)->Get_Player()->Get_Pos();

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, player_Radian);
	D3DXMatrixTranslation(&m_matTrans
		, player_Pos.x + 45.f * cosf(player_Radian)
		, player_Pos.y - 45.f * -sinf(player_Radian)
		, 0.f);
	
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	if (dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->shoot())
	{
		MGR(SoundMgr)->Play("Pistol_Shoot");
		MGR(CObjMgr)->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<CBullet_Pistol>::Create());
	}
	return OBJ_NOEVENT;
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
