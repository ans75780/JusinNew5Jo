#include "stdafx.h"
#include "Collider.h"
#include "Obj.h"
#include "UserDefineHeaders.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()	
	:m_iID(g_iNextID++), m_vOffsetPos(0,0, 0),m_vScale(0, 0, 0)
{
	m_strName = L"Collider";
	m_bIsTriger = false;
}

CCollider::~CCollider()
{
	Release();
}

CCollider::CCollider(const CCollider& _origin)
	: m_vOffsetPos(_origin.m_vOffsetPos), 
	m_vScale(_origin.m_vScale), 
	m_vFinalPos(_origin.m_vFinalPos), 
	m_iID(g_iNextID++)
{
	TCHAR* temp = new TCHAR[_origin.m_strName.size() + 2];
	lstrcpy(temp, _origin.m_strName.c_str());
	m_strName.clear();
	m_strName = temp;
}

void CCollider::Init()
{

}

void CCollider::Release()
{
	m_strName.clear();
}

void CCollider::Update()
{
}

void CCollider::Late_Update()
{
	SyncOwnerPos();
}

void CCollider::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	HPEN myPen, oldPen;
	myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	myPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));	// 선 스타일, 굵기, 색상
	oldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)myPen);	// 펜 선택
	RectDrawCenter(hDC, int(m_vFinalPos.x), int(m_vFinalPos.y), (int)m_vScale.x, (int)m_vScale.y);
	myPen = (HPEN)::SelectObject(hDC, oldPen);	// 기존의 펜 다시 선택
	SelectObject(hDC, oldBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);
	DeleteObject(myBrush);
}

void CCollider::Set_Owner(CObj* pObj)
{
	m_pOwner = pObj;
}

void CCollider::OnCollision(CCollider* _pOther)
{
	CalcCollision(_pOther);

	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	CalcCollision(_pOther);

	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	CalcCollision(_pOther);

	m_pOwner->OnCollisionExit(_pOther);

}

void CCollider::OnTrigger(CCollider* _pOther)
{
	m_pOwner->OnTrigger(_pOther);

}

void CCollider::OnTriggerEnter(CCollider* _pOther)
{
	m_pOwner->OnTriggerEnter(_pOther);
}

void CCollider::OnTriggerExit(CCollider* _pOther)
{
	m_pOwner->OnTriggerExit(_pOther);
}

void CCollider::CalcCollision(CCollider* _pOther)
{
	if (this->Get_Owner()->Get_ID() == OBJID::OBJ_FEATURE)
	{
		return;
	}


	float _W = 0;
	float _H = 0;

	MGR(CCollisionMgr)->IsCollision(&_W, &_H, this, _pOther);

	if (_W > _H)
	{
		if (this->m_pOwner->Get_Pos().y < _pOther->m_pOwner->Get_Pos().y)
		{
			this->m_pOwner->Add_Pos(DXV3(0.f, -_H, 0));
			
		}

		else
		{
			this->m_pOwner->Add_Pos(DXV3(0.f, _H, 0));

			//_pOther->m_pOwner->Add_Pos(DXV3(0.f, -_H));

			//_Other->GetOwner()->GetTransform()->Move_Position(CPOINT(0.f, -OffsetY));
		}
	}

	else
	{
		if (this->m_pOwner->Get_Pos().x < _pOther->m_pOwner->Get_Pos().x)
		{

			this->m_pOwner->Add_Pos(DXV3(-_W, 0.f, 0));

			//_pOther->m_pOwner->Add_Pos(DXV3(_W, 0.f));

			//_Other->GetOwner()->GetTransform()->Move_Position(CPOINT(OffsetX, 0.f));
		}

		else
		{
			this->m_pOwner->Add_Pos(DXV3(_W, 0.f, 0));

			//_pOther->m_pOwner->Add_Pos(DXV3(-_W, 0.f));
			//_Other->GetOwner()->GetTransform()->Move_Position(CPOINT(-OffsetX, 0.f));
		}
	}

	SyncOwnerPos();

}

void CCollider::SyncOwnerPos()
{
	DXV3 OwnerPos = m_pOwner->Get_Pos();
	m_vFinalPos = OwnerPos + m_vOffsetPos;
}
