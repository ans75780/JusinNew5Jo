#include "stdafx.h"
#include "CBullet_Shotgun.h"

#include "Collider.h"
#include "Device.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Stat.h"
#include "Monster.h"
#include "TextureMgr.h"

CBullet_Shotgun::CBullet_Shotgun()
	: m_fReduceRate(0.f), m_fBulletSizeRate(1.f)
{
}

CBullet_Shotgun::~CBullet_Shotgun()
{
}

void CBullet_Shotgun::Init()
{
	m_vPos = { MGR(CObjMgr)->Get_Player()->Get_Pos().x
		, MGR(CObjMgr)->Get_Player()->Get_Pos().y
		, 0.f };
	m_fRadian = MGR(CObjMgr)->Get_Player()->Get_Radian();
	m_vScale = { 10, 10.f, 0.f };

	m_fAtk = 10.f;

	Set_Initial_Points();

	m_fSpeed = 1600.;

	m_bActive = true;
	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Bullet_Shotgun";

	Set_Matrix_to_Identity();
	CreateCollider();
	

	m_iSpreadRate = 50;
	m_fSpreadX = create_x_spread();
	m_fSpreadY = create_y_spread();

	set_bullet_dir(dynamic_cast<CPlayer*>(MGR(CObjMgr)->Get_Player())->get_eDir());

	m_bNowAppear = true;
	m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Bullet");
	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);
}

int CBullet_Shotgun::Update()
{
	if (m_fLifeTime >= 3)
		return OBJ_DEAD;

	if (false == m_bActive)
		return OBJ_DEAD;

	m_fBulletSizeRate -= 0.04f;
	if (m_fBulletSizeRate <= 0)
		return OBJ_DEAD;
	m_bNowAppear = false;
	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = m_matScale  * m_matTrans;


	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	m_vPos += m_vWorldDir * m_fSpeed * DT;

	return OBJ_NOEVENT;
}

void CBullet_Shotgun::Render(HDC hDC)
{

	//DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
	if (m_bNowAppear)
		return;
	//DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
	MGR(CDevice)->Get_Sprite()->SetTransform(&m_matWorld);
	MGR(CDevice)->Get_Sprite()->Draw(m_pTexInfo->pTexture, // 텍스처 객체
		nullptr,	// 출력할 이미지 영역에 대한 렉트 구조체 포인터, null인 경우 이미지의 0, 0기준으로 출력
		&D3DXVECTOR3(m_pTexInfo->tImgInfo.Width / 2, m_pTexInfo->tImgInfo.Height / 2, 0.f),	// 출력할 이미지의 중심 축에 대한 vec3 구조체 포인터, null인 경우 0, 0이 중심 좌표
		nullptr,	// 위치 좌표에 대한 vec3 구조체 포인터, null인 경우 스크린 상 0,0,에 좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBullet_Shotgun::OnCollision(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnCollisionEnter(CCollider * _pOther)
{
	if (_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_MONSTER)
	{
		if (_pOther->Get_Owner()->Get_Name() == L"Zombie")
		{
			dynamic_cast<CMonster*>(_pOther->Get_Owner())->Get_Stat().Damaged(m_fAtk);
		}
		m_bActive = false;
	}
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
