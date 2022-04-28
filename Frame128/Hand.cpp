#include "stdafx.h"
#include "Hand.h"
#include "Collider.h"
#include "Obj.h"
CHand::CHand(CObj* _pTarget, DXV3 _vOffset)
{
	m_pTarget = _pTarget;
	m_vPos = { 0.f, 0.f, 0.f };
	m_vScale = { 30.f, 20.f, 0.f };
	m_vOffset = _vOffset;
	m_strName = L"Hand";
	Set_Initial_Points();
	m_bActive = true;
	m_eID = _pTarget->Get_ID();//플레이어,몬스터에 따라 타입 변경
	m_eRenderID = RENDERID::RENDER_OBJ;
	Set_Matrix_to_Identity();
	CreateCollider();
	CCollider* collider = dynamic_cast<CCollider*>(m_vecComponents[0]);
	collider->SetOffsetPos(m_vOffset);
	collider->SetTriger(true);
}

CHand::~CHand()
{
	Release();
}

void CHand::Init(void)
{
}

int CHand::Update(void)
{
	if (false == m_bActive)
		return OBJ_DEAD;


	float	PlayerRadian =m_pTarget->Get_Radian();
	DXV3 TargetPos = m_pTarget->Get_Pos();
	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, PlayerRadian);
	D3DXMatrixTranslation(&m_matTrans
		, TargetPos.x
		, TargetPos.y
		, 0.f);

	m_matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &(m_vPoint[i] + m_vOffset), &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);
	
	float minX = 5000.f;
	float minY = 5000.f;
	for (int i = 0; i < 4; i++)
	{
		if (minX > m_vWorldPoint[i].x)
			minX = m_vWorldPoint[i].x;
		if (minY > m_vWorldPoint[i].y)
			minY = m_vWorldPoint[i].y;
	}
	m_vPos.x = minX + m_vScale.x * 0.5;
	m_vPos.y = minY + m_vScale.y * 0.5;
	return OBJ_NOEVENT;
}

void CHand::Render(HDC hDC)
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
	m_vecComponents[0]->Render(hDC);
	EllipseDrawCenter(hDC, m_vPos.x , m_vPos.y, 10, 10);
}

void CHand::Release(void)
{
}

void CHand::OnCollision(CCollider* _pOther)
{
}

void CHand::OnCollisionEnter(CCollider* _pOther)
{
}

void CHand::OnCollisionExit(CCollider* _pOther)
{
}

void CHand::OnTrigger(CCollider* _pOther)
{
}

void CHand::OnTriggerEnter(CCollider* _pOther)
{
	if (_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_PLAYER)
	{
	 m_bActive = false;
	}
}

void CHand::OnTriggerExit(CCollider* _pOther)
{
}
