#include "stdafx.h"
#include "CGun.h"

#include "Device.h"


CGun::CGun():
	m_fShootInterval(0.f)
	, m_iCurLoad(0)
	, m_iMaxLoad(0)
{}

CGun::~CGun() {}

int CGun::Update()
{
	return 0;
}

void CGun::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
}
