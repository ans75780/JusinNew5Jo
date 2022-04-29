#include "stdafx.h"
#include "Coin.h"
#include "UserDefineHeaders.h"

CCoin::CCoin()
{
	m_vPos = { 0.f, 0.f, 0.f };
	m_vDir = { 0.f, -1.f, 0.f };
	m_vScale = { 25.f, 25.f, 0.f };
	m_vPoint[LT] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[RT] = {  m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[RB] = {  m_vScale.x * 0.5f,  m_vScale.y * 0.5f, 0.f };
	m_vPoint[LB] = { -m_vScale.x * 0.5f,  m_vScale.y * 0.5f, 0.f };

	m_bActive = true;
	m_eID = OBJID::OBJ_ITEM;
	m_eRenderID = RENDERID::RENDER_OBJ;

	CreateCollider();
}

CCoin::~CCoin()
{
}

void CCoin::Init(void)
{
}

int CCoin::Update(void)
{
	if (false == m_bActive)
		return OBJ_DEAD;

	D3DXMATRIX TransMat;
	D3DXMatrixTranslation(&TransMat, m_vPos.x, m_vPos.y, 0.f);

	D3DXMATRIX WorldMat;

	WorldMat = TransMat;

	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &WorldMat);
	}

	m_pTarget = MGR(CObjMgr)->Get_Player();

	AddMagnetic();

	return OBJ_NOEVENT;
}

void CCoin::Render(HDC hDC)
{
	MoveToEx(hDC
		, int(m_vWorldPoint[0].x)
		, int(m_vWorldPoint[0].y)
		, nullptr);

	for (int i(1); i < sizeof(4); ++i)
	{
		LineTo(hDC
			, int(m_vWorldPoint[i].x)
			, int(m_vWorldPoint[i].y));
	}

	LineTo(hDC
		, int(m_vWorldPoint[0].x)
		, int(m_vWorldPoint[0].y));

	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}

void CCoin::Release(void)
{
}

void CCoin::OnCollision(CCollider* _pOther)
{
}

void CCoin::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_PLAYER)
	{
		m_bActive = false;
	}

}

void CCoin::OnCollisionExit(CCollider* _pOther)
{
}

void CCoin::OnTrigger(CCollider* _pOther)
{
}

void CCoin::OnTriggerEnter(CCollider* _pOther)
{
}

void CCoin::OnTriggerExit(CCollider* _pOther)
{
}
