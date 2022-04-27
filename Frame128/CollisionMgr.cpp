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
			if (nullptr == SourIter->Get_Collider() || &(*SourIter) == &(*DestIter))//�ö��̴��� ���ų�, ���࿡ �ڱ� �ڽŰ��� �浹�̶�� 
			{
				continue;
			}
			pSourCol = SourIter->Get_Collider();
			COLLIDER_ID ID;
			ID.Left_id = pDestCol->Get_Collider_ID();
			ID.Right_id = pSourCol->Get_Collider_ID();
			ID.ID;//�� �浹ü�� ID���� ������ ���� ������ID��.

			iter = m_mapColInfo.find(ID.ID); 
			//�浹 ������ �̵�� ������ ���(�浹�� ���� ���� ���)
			if (m_mapColInfo.end() == iter)//������ �浹�� ���� ���ٸ�
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));//������ �浹�� ���� �����ϱ� false��
				iter = m_mapColInfo.find(ID.ID);
			}
			if (IsCollision(pDestCol, pSourCol))//CollisionCheckStart
			{
				//���� �浹���̴�.
				if (iter->second)
				{
					//�������� �浹 ���̴�.(OnCollision)
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
					//���������浹�����ʾҴ�.(OnTrigerEnter)
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
				//��ü�� �浹���� �ʾҴٸ�
				if (iter->second)//�������� �浹�ϰ��־���.
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
		//�Ѵ� �����浹�� ������ 
		return true;
	}
	return false;
}

void CCollisionMgr::ClearColInfo()
{
	m_mapColInfo.clear();
	CCollider::Reset_Collider_ID();
}


