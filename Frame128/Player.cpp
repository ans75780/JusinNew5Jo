#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "CBullet_Pistol.h"
#include "Device.h"
#include "AbstractFactory.h"
#include "CGun.h"
#include "CPistol.h"
#include "CSMG.h"
#include "CShotgun.h"
#include "AbstractFactory.h"
#include "Stat.h"
#include "MultiTexture.h"
#include "TextureMgr.h"
#include "Camera.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	: tik(0.f), time(0.f), bPressSpace(false), bShoot(false)
{
	m_UnitStat.Set_Atk(10.f);
	m_UnitStat.Set_Hp(100.f);
	m_UnitStat.Set_MaxHp(100.f);
}

CPlayer::~CPlayer() { Release(); }

void CPlayer::Init(void)
{
	m_vPos = { WINCX / 2.f, WINCY / 2.f, 0.f };
	m_vScale = { 75, 75, 0.f };
	m_iCoin = 0;
	m_vPoint[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	m_vPoint[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };

	m_fSpeed = 100.f;

	m_bActive = true;
	m_eID = OBJID::OBJ_PLAYER;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Player";

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotZ);
	D3DXMatrixIdentity(&m_matTrans);

	CreateCollider();

	m_fRadian = D3DXToRadian(-90.f);
	m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Pistol", L"Idle", m_iTexIndex);
	m_ePrevDir = DIRECTION::DOWN;

	time = 0.06f;
}

int CPlayer::Update(void)
{
	if (false == m_bActive)
		return OBJ_DEAD;

	key_input();
	player_direction(m_eDirection);
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

	//animation
	if (m_fCurTime <= 0.1f)
	{
		m_iTexIndex = (m_iTexIndex + 1) % 16;
		m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Pistol", L"Idle", m_iTexIndex);
		m_fCurTime = 0.75;
	}
	else
	{
		m_fCurTime -= 0.015f;
	}

	return OBJ_NOEVENT;
}

void CPlayer::Render(HDC hDC)
{
	DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
	MGR(CDevice)->Get_Sprite()->SetTransform(&m_matWorld);
	MGR(CDevice)->Get_Sprite()->Draw(m_pTexInfo->pTexture, // 텍스처 객체
		nullptr,	// 출력할 이미지 영역에 대한 렉트 구조체 포인터, null인 경우 이미지의 0, 0기준으로 출력
		&D3DXVECTOR3(float(m_pTexInfo->tImgInfo.Width / 2), float(m_pTexInfo->tImgInfo.Height / 2), 0.f),	// 출력할 이미지의 중심 축에 대한 vec3 구조체 포인터, null인 경우 0, 0이 중심 좌표
		nullptr,	// 위치 좌표에 대한 vec3 구조체 포인터, null인 경우 스크린 상 0,0,에 좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255));
	for (auto& iter : m_vecComponents)
        iter->Render(hDC);

	RECT rc = { 50,0,0,0 };
	swprintf_s(szStr, L"Coin : %d", m_iCoin);
	DEVICE->Get_Font()->DrawTextW(nullptr, szStr, -1, &rc, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CPlayer::Release(void)
{
    
}

void CPlayer::key_input()
{
	m_fSpeed = 100.f;

	player_movement();
	player_change_gun();
	

	if (KEYHOLD(E))
	{
		bShoot = false;
		tik += DT;
		if (tik >= time)
		{
			bShoot = true;
			tik = 0.f;
			switch (m_ePlayerGun)
			{
			case GUN_TYPE::PISTOL:
				MGR(CCamera)->Shake(3.f);
				break;
			case GUN_TYPE::SMG:
				MGR(CCamera)->Shake(2.f);
				break;
			case GUN_TYPE::AK47:
				break;
			case GUN_TYPE::SHOTGUN:
				MGR(CCamera)->Shake(5.f);
				break;
			case GUN_TYPE::RAILGUN:
				break;
			case GUN_TYPE::END:
				break;
			default:
				break;
			}
		}
	}

	if (KEYAWAY(E))
	{
		tik = 0.f;
		bShoot = false;
		if (m_ePlayerGun == GUN_TYPE::SMG)
		{
			MGR(SoundMgr)->Stop("SMG_Shoot");
		}
	}


	CalcMat();
}

void CPlayer::player_movement()
{
	m_eDirection = DIRECTION::NONE;
	if (KEYHOLD(UP))
	{
		m_eDirection = DIRECTION::UP;

		if (KEYHOLD(LEFT))
			m_eDirection = DIRECTION::UPLEFT;
		else if (KEYHOLD(RIGHT))
			m_eDirection = DIRECTION::UPRIGHT;
	}
	else if (KEYHOLD(DOWN))
	{
		m_eDirection = DIRECTION::DOWN;
		if (KEYHOLD(LEFT))
			m_eDirection = DIRECTION::DOWNLEFT;
		else if (KEYHOLD(RIGHT))
			m_eDirection = DIRECTION::DOWNRIGHT;
	}
	else if (KEYHOLD(LEFT))
		m_eDirection = DIRECTION::LEFT;
	else if (KEYHOLD(RIGHT))
		m_eDirection = DIRECTION::RIGHT;
	
	if (m_eDirection == DIRECTION::NONE)//예전에 입력처리가 없다면, 가장 최근에 입력한 키값으로
	{
		m_eDirection = m_ePrevDir;
		m_fSpeed = 0.f;
		MGR(SoundMgr)->Stop("Walk");
	}
	else
	{
		m_ePrevDir = m_eDirection;
		if (!MGR(SoundMgr)->IsPlaySound("Walk"))
			MGR(SoundMgr)->Play("Walk");
	}
	CalcMat();
}

void CPlayer::player_change_gun()
{
	if (KEYAWAY(Q))
	{
		MGR(CObjMgr)->Delete_ID(OBJID::OBJ_GUN);

		m_ePlayerGun = GUN_TYPE::PISTOL;
		MGR(CObjMgr)->AddObject(OBJID::OBJ_GUN, CAbstractFactory<CPistol>::Create());
		time = m_pGun->Get_ShotInterval();
	}
	if (KEYAWAY(W))
	{
		MGR(CObjMgr)->Delete_ID(OBJID::OBJ_GUN);

		m_ePlayerGun = GUN_TYPE::SMG;
		MGR(CObjMgr)->AddObject(OBJID::OBJ_GUN, CAbstractFactory<CSMG>::Create());
		time = m_pGun->Get_ShotInterval();
	}

	if (KEYAWAY(A))
	{
		MGR(CObjMgr)->Delete_ID(OBJID::OBJ_GUN);

		MGR(CObjMgr)->Delete_ID(OBJID::OBJ_GUN);
		m_ePlayerGun = GUN_TYPE::SHOTGUN;
		MGR(CObjMgr)->AddObject(OBJID::OBJ_GUN, CAbstractFactory<CShotgun>::Create());
		time = m_pGun->Get_ShotInterval();
	}
}

void CPlayer::player_direction(DIRECTION _eDir)
{
	switch (_eDir)
	{

	case DIRECTION::UP:
		m_fRadian = D3DXToRadian(-90);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWN:
		m_fRadian = D3DXToRadian(90);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::LEFT:
		m_fRadian = D3DXToRadian(-180);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::RIGHT:
		m_fRadian = D3DXToRadian(0);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::UPLEFT:
		m_fRadian = D3DXToRadian(-135);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::UPRIGHT:
		m_fRadian = D3DXToRadian(-45);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNLEFT:
		m_fRadian = D3DXToRadian(135);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNRIGHT:
		m_fRadian = D3DXToRadian(45);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}
}

void CPlayer::OnCollision(CCollider * _pOther)
{
	if (_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_MONSTER)
	{
		DXV3 Dir = m_vPos - _pOther->Get_FinalPos();
		D3DXVec3Normalize(&Dir, &Dir);
		Dir *= 15;

		Add_Pos(Dir);
	}

}

void CPlayer::OnCollisionEnter(CCollider * _pOther)
{
	if (_pOther->Get_Owner()->Get_Name() == L"Coin")
	{
		m_iCoin += 100;
	}
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
}

void CPlayer::OnTrigger(CCollider * _pOther)
{
}

void CPlayer::OnTriggerEnter(CCollider * _pOther)
{
}

void CPlayer::OnTriggerExit(CCollider * _pOther)
{
}
