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

int CGun::Update()
{
	if (m_iCurLoad == 0)
		return OBJ_DEAD;

	float player_Radian = MGR(CObjMgr)->Get_Player()->Get_Radian();
	DXV3	player_Pos = MGR(CObjMgr)->Get_Player()->Get_Pos();

	D3DXMatrixScaling(&m_matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, player_Radian);
	D3DXMatrixTranslation(&m_matTrans,
		player_Pos.x + 45.f * cos(player_Radian),
		player_Pos.y - 45.f * -sinf(player_Radian),
		0.f);

	m_matWorld = m_matScale * m_matRotZ * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	Create_Bullet();

	return OBJ_NOEVENT;
}

void CGun::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
}

void CGun::Create_Bullet()
{
	if (dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->shoot())
	{
		switch (m_eType)
		{
		case GUN_TYPE::PISTOL:
			CreateBullet(CPistol);
			break;

		case GUN_TYPE::SMG:
			CreateBullet(CSMG);
			break;

		case GUN_TYPE::SHOTGUN:
			CreateBullet(CShotgun);
			break;
		}
		--m_iCurLoad;
	}
}