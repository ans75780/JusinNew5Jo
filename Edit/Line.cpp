#include "stdafx.h"
#include "Line.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"


CLine::CLine()
	: m_tInfo()
{
}


CLine::CLine(POINTPOS& tLeft, POINTPOS& tRight)
	: m_tInfo(tLeft, tRight)
{

}

CLine::CLine(LINEINFO& tLine)
	: m_tInfo(tLine)
{

}

CLine::~CLine()
{
}

void CLine::Update(void)
{


	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);
}

void CLine::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tInfo.tLeftPoint.fX + iScrollX, (int)m_tInfo.tLeftPoint.fY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRightPoint.fX + iScrollX, (int)m_tInfo.tRightPoint.fY);
}

