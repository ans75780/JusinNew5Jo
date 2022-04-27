#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_eDir(END), m_bDead(false), m_fAngle(0.f), m_fDiagonal(0.f)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tInfo, sizeof(INFO));
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left  = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top   = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
