#include "stdafx.h"
#include "Collider.h"
#include "Obj.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()	
	:m_iID(g_iNextID++), m_vOffsetPos(0,0),m_vScale(0,0)
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
	VECTOR2 OwnerPos = m_pOwner->Get_Pos();
	m_vFinalPos = OwnerPos + m_vOffsetPos;
}

void CCollider::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	HPEN myPen, oldPen;
	myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	myPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));	// �� ��Ÿ��, ����, ����
	oldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)myPen);	// �� ����
	RectDrawCenter(hDC, m_vFinalPos.x, m_vFinalPos.y, (int)m_vScale.x, (int)m_vScale.y);
	myPen = (HPEN)::SelectObject(hDC, oldPen);	// ������ �� �ٽ� ����
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

void CCollider::OnTriger(CCollider* _pOther)
{
	m_pOwner->OnTriger(_pOther);

}

void CCollider::OnTrigerEnter(CCollider* _pOther)
{
	m_pOwner->OnTrigerEnter(_pOther);
}

void CCollider::OnTrigerExit(CCollider* _pOther)
{
	m_pOwner->OnTrigerExit(_pOther);
}

void CCollider::CalcCollision(CCollider* _pOther)
{
	
}
