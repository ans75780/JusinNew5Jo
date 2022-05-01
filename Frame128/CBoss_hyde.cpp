#include "stdafx.h"
#include "CBoss_hyde.h"

#include "CBullet_Pistol.h"

#include "AbstractFactory.h"
#include "Hand.h"
#include "UserDefineHeaders.h"
#include "Stat.h"

CBoss_hyde::CBoss_hyde()
{
}

CBoss_hyde::~CBoss_hyde()
{
}

void CBoss_hyde::Init(void)
{
	m_UnitStat.Set_Atk(20.f);
	m_UnitStat.Set_Hp(500.f);
	m_UnitStat.Set_MaxHp(500.f);

	m_vPos = { 400.f, 100.f, 0.f };
	m_vScale = { 200.f, 200.f, 0.f };

	Set_Initial_Points();

	m_fSpeed = 300.f;

	m_bActive = true;
	m_eID = OBJID::OBJ_BOSS;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Boss_hyde";

	Set_Matrix_to_Identity();

	CreateCollider();
	FindTarget();

}

int CBoss_hyde::Update(void)
{
	if (m_UnitStat.Get_Hp() < 1)
	{
		Set_Active(false);
	}
	if (m_bActive == false)
	{
		return OBJ_DEAD;
	}
	if (KEYTAP(R))
	{
		m_UnitStat.Damaged(100);
	}

	SetRadianToPlayer();

	CalcMat();

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	m_vPos += m_vWorldDir * m_fSpeed * DT;
	return OBJ_NOEVENT;
}

void CBoss_hyde::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));

	EllipseDrawCenter(hDC
		, int(m_vWorldPoint[1].x)
		, int(m_vWorldPoint[1].y), 10, 10);

	EllipseDrawCenter(hDC
		, int(m_vWorldPoint[2].x)
		, int(m_vWorldPoint[2].y)
		, 10, 10);

	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}

void CBoss_hyde::Release(void)
{
}
