#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTile::CTile()
{
}

CTile::~CTile()
{
	Release();
}

void CTile::Init(void)
{
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile.bmp", L"Tile");
}

int CTile::Update(void)
{


	return OBJ_NOEVENT;
}

void CTile::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	POINT pos = m_vPos.To_Int();
	POINT scale = m_vScale.To_Int();
	if (m_iDrawID != 0)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");
		RECT rc = RectMakeCenter(pos.x, pos.y, scale.x, scale.y);
		BitBlt(hDC,
			rc.left + iScrollX,
			rc.top + iScrollY,
			scale.x,
			scale.y,
			hMemDC,
			m_iDrawID * scale.y,
			0,
			SRCCOPY);
	}
	if (m_iDrawID == 0)
		swprintf_s(m_strType, L"¶¥");
	else if (m_iDrawID == 1)
		swprintf_s(m_strType, L"º®");
	TextOut(hDC, pos.x + iScrollX, pos.y + iScrollY, m_strType, lstrlen(m_strType));

}

void CTile::Release(void)
{
	
}

void CTile::OnCollision(CCollider * _pOther)
{
}

void CTile::OnCollisionEnter(CCollider * _pOther)
{
}

void CTile::OnCollisionExit(CCollider * _pOther)
{
}

void CTile::OnTrigger(CCollider * _pOther)
{
}

void CTile::OnTriggerEnter(CCollider * _pOther)
{
}

void CTile::OnTriggerExit(CCollider * _pOther)
{
}
