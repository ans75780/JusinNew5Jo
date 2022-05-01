#include "stdafx.h"
#include "Zombie.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "CBullet_Pistol.h"

#include "AbstractFactory.h"
#include "Hand.h"
#include "UserDefineHeaders.h"
#include "Stat.h"

CZombie::CZombie()
{
}

CZombie::~CZombie()
{
	Release();
}

void CZombie::Init(void)
{
	m_UnitStat.Set_Atk(15.f);
	m_UnitStat.Set_Hp(10.f);
	m_UnitStat.Set_MaxHp(10.f);

	m_vPos = { 400, 100, 0.f };
	m_vScale = { 50.f, 50.f, 0.f };

	m_vPoint[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	m_vPoint[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };

	m_fSpeed = 25;

	m_bActive = true;
	m_eID = OBJID::OBJ_MONSTER;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Zombie";

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotZ);
	D3DXMatrixIdentity(&m_matTrans);

	CreateCollider();
	FindTarget();
	CHand* hand = new CHand(this, DXV3(45, -15, 0));
	MGR(CObjMgr)->AddObject(OBJ_MONSTER, hand);
	hand = new CHand(this, DXV3(45, 15, 0));
	MGR(CObjMgr)->AddObject(OBJ_MONSTER, hand);

	m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Monster", L"Zombie", m_iTexIndex);

	m_fCurTime = 0.75;
	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fRadian);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;
	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);
}

int CZombie::Update(void)
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
	//m_fRadian = D3DXToRadian(90.f);

	//CalcMat();
	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fRadian);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;
	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);
	m_vMoveSize = m_vWorldDir * m_fSpeed * DT;
	m_vPos += m_vMoveSize;
	int a = 10;
	float DTDT = DT;

	//CurTime이 0보다 작으면 이미지 교체
	if (m_fCurTime <= 0.1f)
	{
		m_iTexIndex = (m_iTexIndex + 1) % 16;
		m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Monster", L"Zombie", m_iTexIndex);
		m_fCurTime = 0.75;
	}
	else
	{
		m_fCurTime -= DT;
	}

    return 0;
}

void CZombie::Render(HDC hDC)
{
	/*MoveToEx(hDC
		, int(m_vWorldPoint[0].x)
		, int(m_vWorldPoint[0].y)
		, nullptr);

	for (int i(1); i < sizeof(4); ++i)
	{
		LineTo(hDC
			, int(m_vWorldPoint[i].x)
			, int(m_vWorldPoint[i].y));
	}

	LineTo(hDC
		, int(m_vWorldPoint[0].x)
		, int(m_vWorldPoint[0].y));

	EllipseDrawCenter(hDC, m_vWorldPoint[1].x, m_vWorldPoint[1].y, 10, 10);
	EllipseDrawCenter(hDC, m_vWorldPoint[2].x, m_vWorldPoint[2].y, 10, 10);*/

	MGR(CDevice)->Get_Sprite()->SetTransform(&m_matWorld);
	/*m_iTexIndex = (m_iTexIndex + 1) % 16;
	m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Monster", L"Zombie", m_iTexIndex);*/
	

	float Half_Width = m_pTexInfo->tImgInfo.Width * 0.5f;
	float Half_Height = m_pTexInfo->tImgInfo.Height * 0.5f;

	MGR(CDevice)->Get_Sprite()->Draw(m_pTexInfo->pTexture, // 텍스처 객체
		nullptr,	// 출력할 이미지 영역에 대한 렉트 구조체 포인터, null인 경우 이미지의 0, 0기준으로 출력
		&D3DXVECTOR3(Half_Width, Half_Height, 0.f),	// 출력할 이미지의 중심 축에 대한 vec3 구조체 포인터, null인 경우 0, 0이 중심 좌표
		nullptr,	// 위치 좌표에 대한 vec3 구조체 포인터, null인 경우 스크린 상 0,0,에 좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//m_vecComponents[0]->Render(hDC);
}

void CZombie::Release(void)
{
}

void CZombie::Set_Active(bool _isActive)
{
	CObj::Set_Active(_isActive);

	if (!_isActive)
	{
		CObj* Coin = CAbstractFactory<CCoin>::Create();
		Coin->Set_Pos(m_vPos);
		MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin);
	}
}
