#include "stdafx.h"
#include "Feature.h"
#include "Collider.h"

CFeature::CFeature()
{

}

CFeature::~CFeature()
{
	Release();
}

void CFeature::Init(void)
{
	m_vScale.x = 64;
	m_vScale.y = 64;
	m_vDir = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	m_vPoint[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };

	m_bActive = true;
	m_eID = OBJ_FEATURE;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Feature";
	CreateCollider();
}

int CFeature::Update(void)
{
	if (false == m_bActive)
		return OBJ_DEAD;

	for (auto& iter : m_vecComponents)
		iter->Update();

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fRadian);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = m_matScale * m_matRotZ * m_matTrans;
	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	return 0;
}

void CFeature::Render(HDC hDC)
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

void CFeature::Release(void)
{
	for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
	m_vecComponents.clear();
	m_strName.clear();
}

void CFeature::OnCollision(CCollider * _pOther)
{
}

void CFeature::OnCollisionEnter(CCollider * _pOther)
{
	if (_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_BULLET)
	{
		Set_Active(false);
	}
}

void CFeature::OnCollisionExit(CCollider * _pOther)
{
}

void CFeature::OnTrigger(CCollider * _pOther)
{
}

void CFeature::OnTriggerEnter(CCollider * _pOther)
{
}

void CFeature::OnTriggerExit(CCollider * _pOther)
{
}

