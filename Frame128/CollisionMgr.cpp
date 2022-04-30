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

			//out ���� float �� ��. 
			float _w;
			float _h;
			if (IsOBBCollision(pDestCol, pSourCol))//CollisionCheckStart
			{
				//���� �浹���̴�.
				if (iter->second)
				{
					//�������� �浹 ���̴�.(OnCollision)
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
					//���������浹�����ʾҴ�.(OnTrigerEnter)
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
				//��ü�� �浹���� �ʾҴٸ�
				if (iter->second)//�������� �浹�ϰ��־���.
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

		//�Ѵ� �����浹�� ������ 
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

	v[0] = (vDestSize.y * vDest_H_Dir); //D�� ���̹��� ����
	v[1] = (vDestSize.x * vDest_W_Dir); //D�� �¹��� ����
	v[2] = (vSourSize.y * vSour_H_Dir); //S�� ���̹��� ����
	v[3] = (vSourSize.x * vSour_W_Dir); //S�� �¹��� ����

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


