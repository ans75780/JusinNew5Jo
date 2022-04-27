#include "stdafx.h"
#include "ObjMgr.h"
#include "Feature.h"
CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;
	float	fDistance = 0.f;

	for (auto& Iter : m_ObjList[eID])
	{
		if(Iter->Get_Active())
			continue;

		float fWidth = fabs(Iter->Get_Pos().x - pObj->Get_Pos().x);
		float fHeight = fabs(Iter->Get_Pos().x - pObj->Get_Pos().y);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = Iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::AddObject(OBJID eID, CObj * pObj)
{
	if ((OBJ_END <= eID) || (pObj == nullptr))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto& iter = m_ObjList[i].begin();

		for (; iter != m_ObjList[i].end();)
		{
			int	iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID eRender = iter->Get_RenderID();
			m_RenderSort[eRender].push_back(iter);
		}
	}
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]);
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])
			iter->Render(hDC);

		m_RenderSort[i].clear();
	}
	
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete<CObj*>(iter);

	m_ObjList[eID].clear();

}

void CObjMgr::LoadFeature(const char* strData)
{
	
}
