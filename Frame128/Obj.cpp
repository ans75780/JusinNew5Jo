#include "stdafx.h"
#include "Obj.h"
#include "ComponentBase.h"
#include "Collider.h"

CObj::CObj()
	:m_bActive(true), m_fRadian(0.f), m_vPos(0, 0,0 ), m_vScale(0, 0, 0),m_strName(L"")
{
	D3DXMatrixIdentity(&m_matLocal);
}

CObj::~CObj()
{
}

void CObj::Late_Update(void)
{
	for (auto& iter : m_vecComponents)
		iter->Late_Update();
}

CComponent* CObj::Get_Component(const TCHAR* ComponentName)
{
	auto& iter = find_if(m_vecComponents.begin(),
		m_vecComponents.end(),
		[&ComponentName](auto& DestIter)-> bool
		{
			if (!DestIter->Get_Name().compare(ComponentName))
				return true;
			else
				return false;
		});
	if (iter != m_vecComponents.end())
		return *iter;
	return nullptr;
}

void CObj::CreateCollider()
{
	CComponent* Collider = new  CCollider();
	Collider->Init();
	Collider->Set_Owner(this);
	static_cast<CCollider*>(Collider)->Set_Scale(m_vScale);
	m_vecComponents.push_back(Collider);
}

CCollider* CObj::Get_Collider()
{
	CComponent* component = nullptr;

	component = Get_Component(L"Collider");
	if (component)
		return static_cast<CCollider*>(component);
	return nullptr;
}
