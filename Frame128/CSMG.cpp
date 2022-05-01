#include "stdafx.h"
#include "CSMG.h"

#include "Device.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "Player.h"
#include "CBullet_SMG.h"


CSMG::CSMG()
{
}

CSMG::~CSMG()
{
}

void CSMG::Init()
{
	dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->set_gun(this);
	m_vScale = { 40.f, 15.f, 0.f };

	m_iMaxLoad = 1000;
	m_iCurLoad = m_iMaxLoad;

	m_strName = L"SMG";

	Set_Initial_Points();
	m_fShootInterval = 0.05f;

	m_bActive = true;
	m_eID = OBJID::OBJ_GUN;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_eType = GUN_TYPE::SMG;

	Set_Matrix_to_Identity();
}

int CSMG::Update()
{
	if (m_iCurLoad == 0)
		return OBJ_DEAD;

	float player_Radian = MGR(CObjMgr)->Get_Player()->Get_Radian();
	DXV3	player_Pos = MGR(CObjMgr)->Get_Player()->Get_Pos();

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, player_Radian);
	D3DXMatrixTranslation(&m_matTrans,
		player_Pos.x + 45.f * cos(player_Radian),
		player_Pos.y - 45.f * -sinf(player_Radian),
		0.f);

	m_matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	if (dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->shoot())
	{
		if (!MGR(SoundMgr)->IsPlaySound("SMG_Shoot"))
			MGR(SoundMgr)->Play("SMG_Shoot");
	
		MGR(CObjMgr)->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<CBullet_SMG>::Create());
		--m_iCurLoad;
	}

	return OBJ_NOEVENT;
}

void CSMG::Release()
{
}

void CSMG::OnCollision(CCollider * _pOther)
{
}

void CSMG::OnCollisionEnter(CCollider * _pOther)
{
}

void CSMG::OnCollisionExit(CCollider * _pOther)
{
}

void CSMG::OnTrigger(CCollider * _pOther)
{
}

void CSMG::OnTriggerEnter(CCollider * _pOther)
{
}

void CSMG::OnTriggerExit(CCollider * _pOther)
{
}
