#include "stdafx.h"
#include "CollisionMgr.h"

CCollisionMgr::CCollisionMgr()
{

}

CCollisionMgr::~CCollisionMgr()
{
	ClearColInfo();
}

void CCollisionMgr::CollisionUpdate(list<CObj*>& Dest, list<CObj*>& Sour)
{
	map<ULONGLONG, bool>::iterator iter;
	CCollider* pDestCol = nullptr;
	CCollider* pSourCol = nullptr;
	for (auto& DestIter : Dest)
	{
		if (nullptr == DestIter->Get_Collider())
		{
			continue;
		}
		pDestCol = DestIter->Get_Collider();
		for (auto& SourIter : Sour)
		{
			if (nullptr == SourIter->Get_Collider() || &(*SourIter) == &(*DestIter))//컬라이더가 없거나, 만약에 자기 자신과의 충돌이라면 
			{
				continue;
			}
			pSourCol = SourIter->Get_Collider();
			COLLIDER_ID ID;
			ID.Left_id = pDestCol->Get_Collider_ID();
			ID.Right_id = pSourCol->Get_Collider_ID();
			ID.ID;//두 충돌체의 ID값이 합쳐져 나온 고유한ID값.

			iter = m_mapColInfo.find(ID.ID); 
			//충돌 정보가 미등록 상태인 경우(충돌한 적이 없는 경우)
			if (m_mapColInfo.end() == iter)//이전에 충돌한 적이 없다면
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));//이전에 충돌한 적이 없으니까 false로
				iter = m_mapColInfo.find(ID.ID);
			}
			if (IsCollision(pDestCol, pSourCol))//CollisionCheckStart
			{
				//현재 충돌중이다.
				if (iter->second)
				{
					//이전에도 충돌 중이다.(OnCollision)
					if (pDestCol->Get_IsTriger())
						pDestCol->OnTriger(pSourCol);
					else
						pDestCol->OnCollision(pSourCol);

					if (pSourCol->Get_IsTriger())
						pSourCol->OnTriger(pDestCol);
					else
						pSourCol->OnCollision(pDestCol);

				}
				else
				{
					//이전에는충돌하지않았다.(OnTrigerEnter)
					if (pDestCol->Get_IsTriger())
						pDestCol->OnTrigerEnter(pSourCol);
					else
						pDestCol->OnCollisionEnter(pSourCol);

					if (pSourCol->Get_IsTriger())
						pSourCol->OnTrigerEnter(pDestCol);
					else
						pSourCol->OnCollisionEnter(pDestCol);
					iter->second = true;
				}
			}//CollisionCheckEnd;
			else
			{
				//물체가 충돌하지 않았다면
				if (iter->second)//이전에는 충돌하고있었다.
				{
					if (pDestCol->Get_IsTriger())
						pDestCol->OnTrigerExit(pSourCol);
					else
						pDestCol->OnCollisionExit(pSourCol);

					if (pSourCol->Get_IsTriger())
						pSourCol->OnTrigerExit(pDestCol);
					else
						pSourCol->OnCollisionExit(pDestCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* DestCollider, CCollider* SourCollider)
{
	VECTOR2 vDestPos = DestCollider->Get_FinalPos();
	VECTOR2 vDestScale = DestCollider->Get_Scale();

	VECTOR2 vSourPos = SourCollider->Get_FinalPos();
	VECTOR2 vSourScale = SourCollider->Get_Scale();

	float		fWidth = abs(vSourPos.x - vDestPos.x);
	float		fWRadius = (vDestScale.x + vSourScale.x) * 0.5f;
	float		fHeight = abs(vSourPos.y - vDestPos.y);
	float		fHRadius = (vDestScale.x + vSourScale.x) * 0.5f;

	if (fWRadius > fWidth &&
		fHRadius > fHeight)
	{
		float fX = fWRadius - fWidth;
		float fY = fHRadius - fHeight;
		//둘다 물리충돌을 지원할 
		return true;
	}
	return false;
}

void CCollisionMgr::ClearColInfo()
{
	m_mapColInfo.clear();
	CCollider::Reset_Collider_ID();
}


