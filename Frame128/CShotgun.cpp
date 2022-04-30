#include "stdafx.h"
#include "CShotgun.h"

#include "Device.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

#include "Player.h"
#include "CBullet_Shotgun.h"

CShotgun::CShotgun()
{
}

CShotgun::~CShotgun()
{
}

void CShotgun::Init()
{
	dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->set_gun(this);
	m_vPos = { 0.f, 0.f, 0.f };
	m_vScale = { 70.f, 50.f, 0.f };

	m_iMaxLoad = 50;
	m_iCurLoad = m_iMaxLoad;

	m_strName = L"Shotgun";

	Set_Initial_Points();
	m_fShootInterval = 0.2f;

	m_bActive = true;
	m_eID = OBJID::OBJ_GUN;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_eType = GUN_TYPE::SHOTGUN;

	Set_Matrix_to_Identity();
}

int CShotgun::Update()
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
		MGR(CObjMgr)->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<CBullet_Shotgun>::Create());
		--m_iCurLoad;
	}

	return OBJ_NOEVENT;
}

void CShotgun::Render(HDC hDC)
{
}

void CShotgun::Release()
{
}

void CShotgun::OnCollision(CCollider * _pOther)
{
}

void CShotgun::OnCollisionEnter(CCollider * _pOther)
{
}

void CShotgun::OnCollisionExit(CCollider * _pOther)
{
}

void CShotgun::OnTrigger(CCollider * _pOther)
{
}

void CShotgun::OnTriggerEnter(CCollider * _pOther)
{
}

void CShotgun::OnTriggerExit(CCollider * _pOther)
{
}