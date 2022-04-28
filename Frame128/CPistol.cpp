#include "stdafx.h"
#include "CPistol.h"

#include "ObjMgr.h"

CPistol::CPistol()
{
}

CPistol::~CPistol()
{
}

void CPistol::Init()
{
	m_vPos = { 0.f, 0.f, 0.f };
	m_vScale = { 10.f, 30.f, 0.f };

	m_strName = L"Pistol";
	m_vDir = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	m_vPoint[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };

	m_bActive = true;
	m_eID = OBJID::OBJ_GUN;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_eType = GUN_TYPE::PISTOL;

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotZ);
	D3DXMatrixIdentity(&m_matTrans);
}

int CPistol::Update()
{
	if (false == m_bActive)
		return OBJ_DEAD;

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, MGR(CObjMgr)->Get_Player()->Get_Angle());
	D3DXMatrixTranslation(&m_matTrans
		, MGR(CObjMgr)->Get_Player()->Get_Pos().x + 30.f * sinf(MGR(CObjMgr)->Get_Player()->Get_Angle())
		, MGR(CObjMgr)->Get_Player()->Get_Pos().y - 30.f * cosf(MGR(CObjMgr)->Get_Player()->Get_Angle())
		, 0.f);
	
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);
	return OBJ_NOEVENT;
}

void CPistol::Render(HDC hDC)
{
	MoveToEx(hDC, m_vWorldPoint[0].x, m_vWorldPoint[0].y, nullptr);
	for (int i(1); i < 4; ++i)
	{
		LineTo(hDC, m_vWorldPoint[i].x, m_vWorldPoint[i].y);
	}
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
