#include "stdafx.h"
#include "CBullet_Shotgun.h"

#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"

CBullet_Shotgun::CBullet_Shotgun()
	: m_fReduceRate(0.f), m_fBulletSizeRate(1.f)
{
}

CBullet_Shotgun::~CBullet_Shotgun()
{
}

void CBullet_Shotgun::Init()
{
	m_vPos = { 0.f, 0.f, 0.f };
	m_vScale = { 20.f, 20.f, 0.f };

	m_strName = L"Bullet_Shotgun";

	Set_Initial_Points();

	m_bActive = true;

	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;

	Set_Matrix_to_Identity();

	m_fSpeed = 1000.f;

	m_iSpreadRate = 30.f;
	m_fSpreadX = create_x_spread();
	m_fSpreadY = create_y_spread();

	set_bullet_dir(dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->get_eDir());

	vInitPos = MGR(CObjMgr)->Get_Player()->Get_Pos();
	m_fRadian = MGR(CObjMgr)->Get_Player()->Get_Radian();

	CreateCollider();

	m_vLocalPos = m_vPos;
}

int CBullet_Shotgun::Update()
{
	m_fLifeTime += DT;

	if (false == m_bActive)
		return OBJ_DEAD;

	if (m_fLifeTime >= 3)
		return OBJ_DEAD;

	m_vPos += m_vDir * m_fSpeed * DT;
	m_vLocalPos += m_vDir * m_fSpeed * DT;

	m_fBulletSizeRate -= 0.01f;
	
	if (0 >= m_fBulletSizeRate)
		return OBJ_DEAD;

	D3DXMatrixScaling(&m_matScale
		, m_fBulletSizeRate
		, m_fBulletSizeRate
		, 0.f);

	D3DXMatrixTranslation(&m_matPos
		, m_vLocalPos.x
		, m_vLocalPos.y, 0.f);

	D3DXMatrixTranslation(&m_matTrans
		, vInitPos.x + 50.f * cosf(m_fRadian)
		, vInitPos.y - 45.f * sinf(m_fRadian)
		, 0.f);

	m_matWorld = m_matPos * m_matScale * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	return OBJ_NOEVENT;
}

void CBullet_Shotgun::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));

	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}

void CBullet_Shotgun::Release()
{
	for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
	m_vecComponents.clear();
	m_strName.clear();
}

void CBullet_Shotgun::OnCollision(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnCollisionEnter(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTrigger(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTriggerExit(CCollider * _pOther)
{
}
