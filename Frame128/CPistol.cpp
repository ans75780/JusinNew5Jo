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
}

int CPistol::Update()
{
	// 좌표는 플레이어 좌표에 고정하자
	MGR(CObjMgr)->Get_Player()->Get_Pos();
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
