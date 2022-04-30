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

			//out 받을 float 두 개. 
			float _w;
			float _h;
			if (IsOBBCollision(pDestCol, pSourCol))//CollisionCheckStart
			{
				//현재 충돌중이다.
				if (iter->second)
				{
					//이전에도 충돌 중이다.(OnCollision)
					if (pDestCol->Get_IsTriger())
						pDestCol->OnTrigger(pSourCol);
					else
						pDestCol->OnCollision(pSourCol);

					if (pSourCol->Get_IsTriger())
						pSourCol->OnTrigger(pDestCol);
					else
						pSourCol->OnCollision(pDestCol);

				}
				else
				{
					//이전에는충돌하지않았다.(OnTrigerEnter)
					if (pDestCol->Get_IsTriger())
						pDestCol->OnTriggerEnter(pSourCol);
					else
						pDestCol->OnCollisionEnter(pSourCol);

					if (pSourCol->Get_IsTriger())
						pSourCol->OnTriggerEnter(pDestCol);
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
						pDestCol->OnTriggerExit(pSourCol);
					else
						pDestCol->OnCollisionExit(pSourCol);

					if (pSourCol->Get_IsTriger())
						pSourCol->OnTriggerExit(pDestCol);
					else
						pSourCol->OnCollisionExit(pDestCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(float* _outW, float* _outH, CCollider* DestCollider, CCollider* SourCollider)
{
	DXV3 vDestPos = DestCollider->Get_FinalPos();
	DXV3 vDestScale = DestCollider->Get_Scale();

	DXV3 vSourPos = SourCollider->Get_FinalPos();
	DXV3 vSourScale = SourCollider->Get_Scale();

	float		fWidth = abs(vSourPos.x - vDestPos.x);
	float		fWRadius = (vDestScale.x + vSourScale.x) * 0.5f;
	float		fHeight = abs(vSourPos.y - vDestPos.y);
	float		fHRadius = (vDestScale.x + vSourScale.x) * 0.5f;

	if (fWRadius > fWidth &&
		fHRadius > fHeight)
	{
		float fX = fWRadius - fWidth;
		float fY = fHRadius - fHeight;

		*_outW = fX;
		*_outH = fY;

		//둘다 물리충돌을 지원할 
		return true;
	}
	return false;
}

bool CCollisionMgr::IsOBBCollision(CCollider* DestCollider, CCollider* SourCollider)
{

	DXV3 vDestPos = DestCollider->Get_FinalPos();
	DXV3 vDestSize = DestCollider->Get_Scale() * 0.5f;
	DXV3 vDest_H_Dir = DestCollider->Get_Dir();
	DXV3 vDest_W_Dir;
	D3DXVec3Cross(&vDest_W_Dir, &vDest_H_Dir, &DXV3(0.f, 0.f, 1.0f));
	//vDest_W_Dir *= -1;

	DXV3 vSourPos = SourCollider->Get_FinalPos();
	DXV3 vSourSize = SourCollider->Get_Scale() * 0.5f;
	DXV3 vSour_H_Dir = SourCollider->Get_Dir();
	DXV3 vSour_W_Dir;
	D3DXVec3Cross(&vSour_W_Dir, &vSour_H_Dir, &DXV3(0.f, 0.f, 1.0f));
	//vSour_W_Dir *= -1;

	DXV3 vDistance = DestCollider->Get_FinalPos() - SourCollider->Get_FinalPos();

	DXV3 v[4] = {};

	v[0] = (vDestSize.y * vDest_H_Dir); //D의 높이방향 벡터
	v[1] = (vDestSize.x * vDest_W_Dir); //D의 좌방향 벡터
	v[2] = (vSourSize.y * vSour_H_Dir); //S의 높이방향 벡터
	v[3] = (vSourSize.x * vSour_W_Dir); //S의 좌방향 벡터

	for (int i = 0; i < 4; i++) {
		float sum = 0;
		DXV3 vNormal;
		D3DXVec3Normalize(&vNormal, &v[i]);

		for (int j = 0; j < 4; j++) 
		{
			float fAbsDot = fabsf(D3DXVec3Dot(&v[j], &vNormal));

			sum += fAbsDot;
		}
		float result = fabsf(D3DXVec3Dot(&vDistance, &vNormal));

		if (result > sum) {
			return false;
		}
	}
	return true;
}

void CCollisionMgr::ClearColInfo()
{
	m_mapColInfo.clear();
	CCollider::Reset_Collider_ID();
}


