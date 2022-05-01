#include "stdafx.h"
#include "Collider.h"
#include "Obj.h"
#include "UserDefineHeaders.h"
#include "Device.h"
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
	/*
	HBRUSH myBrush, oldBrush;
	HPEN myPen, oldPen;
	myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	myPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));	// 선 스타일, 굵기, 색상
	oldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)myPen);	// 펜 선택
	//RectDrawCenter(hDC, int(m_vFinalPos.x), int(m_vFinalPos.y), (int)m_vScale.x, (int)m_vScale.y);
	
	MoveToEx(hDC
		, int(m_vWheels[0].x)
		, int(m_vWheels[0].y)
		, nullptr);

	for (int i(1); i < sizeof(4); ++i)
	{
		LineTo(hDC
			, int(m_vWheels[i].x)
			, int(m_vWheels[i].y));
	}

	LineTo(hDC
		, int(m_vWheels[0].x)
		, int(m_vWheels[0].y));
	myPen = (HPEN)::SelectObject(hDC, oldPen);	// 기존의 펜 다시 선택
	SelectObject(hDC, oldBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);
	DeleteObject(myBrush);
	*/
	DEVICE->Draw_Line(m_vWheels, 5, D3DCOLOR_ARGB(255,0,255,0));
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
	wstring myStr = this->Get_Owner()->Get_Name();
	wstring otherStr = _pOther->Get_Owner()->Get_Name();

	int i = 0;

	if (this->Get_Owner()->Get_ID() == OBJID::OBJ_FEATURE)
	{
		return;
	}

	if (this->Get_Owner()->Get_ID() == OBJID::OBJ_MONSTER &&
		_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_MONSTER)
	{
		if (this->Get_Owner()->Get_Name() == L"Zombie" &&
			_pOther->Get_Owner()->Get_Name() == L"Zombie")
		{
			DXV3 Dir = m_vFinalPos - _pOther->Get_FinalPos();
			D3DXVec3Normalize(&Dir, &Dir);
			//Dir *= 10000.f * DT;

			this->Get_Owner()->Add_Pos(Dir);
		}
	}

	if (this->Get_Owner()->Get_ID() == OBJID::OBJ_MONSTER &&
		_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_BULLET)
	{
		DXV3 Dir = m_vFinalPos - _pOther->Get_FinalPos();
		D3DXVec3Normalize(&Dir, &Dir);
		//Dir *= 100000.f * DT;

		this->Get_Owner()->Add_Pos(Dir);
	}

	else if (this->Get_Owner()->Get_ID() == OBJID::OBJ_BULLET &&
		_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_MONSTER)
	{
		DXV3 Dir = _pOther->Get_FinalPos() - m_vFinalPos;
		D3DXVec3Normalize(&Dir, &Dir);
		//Dir *= 100000.f * DT;

		_pOther->Get_Owner()->Add_Pos(Dir);
	}

	else if (this->Get_Owner()->Get_ID() == OBJID::OBJ_PLAYER &&
		_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_MONSTER)
	{
		DXV3 Dir = m_vFinalPos - _pOther->Get_FinalPos();
		D3DXVec3Normalize(&Dir, &Dir);

		//Dir *= 10000.f * DT;
		this->Get_Owner()->Add_Pos(Dir);
	}

	SyncOwnerPos();

}

void CCollider::SyncOwnerPos()
{	
	m_vFinalPos = m_pOwner->Get_Pos();
	m_vScale = m_pOwner->Get_Scale();
	m_vWheels = m_pOwner->Get_Wheels();
	m_vDir = m_pOwner->Get_Dir();
	// m_vMoveSize = m_pOwner->Get_MoveSize();
}
