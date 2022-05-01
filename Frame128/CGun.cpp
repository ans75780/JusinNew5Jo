#include "stdafx.h"
#include "CGun.h"

#include "Device.h"
#include "ObjMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "GunsInclude.h"

CGun::CGun():
	m_fShootInterval(0.f)
	, m_iCurLoad(0)
	, m_iMaxLoad(0)
{}

CGun::~CGun() {}

void CGun::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
}