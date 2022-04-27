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
	m_bActive = true;
	m_eID = OBJ_FEATURE;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Feature";
	CreateCollider();
}

int CFeature::Update(void)
{
	for (auto& iter : m_vecComponents)
		iter->Update();

	return 0;
}

void CFeature::Render(HDC hDC)
{
	RectDrawCenter(hDC, m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y);
	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}

void CFeature::Release(void)
{
	for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
	m_vecComponents.clear();
	m_strName.clear();
}

