#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "CBullet_Pistol.h"
<<<<<<< Updated upstream

#include "AbstractFactory.h"

CPlayer::CPlayer()
=======
#include "CBullet_SMG.h"
#include "CGun.h"
#include "CPistol.h"
#include "AbstractFactory.h"

CPlayer::CPlayer()
	: tik(0.f), time(0.f), bPressSpace(false), bShoot(false)
>>>>>>> Stashed changes
{
}

CPlayer::~CPlayer() { Release(); }

void CPlayer::Init(void)
{
#pragma region original version (tank version)
	/*D3DXMatrixIdentity(&m_matLocal);
    m_vPos = { 300,300, 0.f};
	m_fWheelDist = 25;

	m_vWheel[LT].x = -m_fWheelDist;
	m_vWheel[LT].y  = -m_fWheelDist;

	m_vWheel[LB].x = -m_fWheelDist;
	m_vWheel[LB].y = +m_fWheelDist;

	m_vWheel[RT].x = +m_fWheelDist;
	m_vWheel[RT].y = -m_fWheelDist;

	m_vWheel[RB].x = +m_fWheelDist;
	m_vWheel[RB].y = +m_fWheelDist;

    m_vScale = { 50,50 ,0.f};
    m_fSpeed = 500.f;
    m_fRadian = D3DXToRadian(0);
    m_fAtk = 0.f;
    m_eID = OBJ_PLAYER;
    m_eRenderID = RENDERID::RENDER_OBJ;
    m_strName = L"Player";

    CreateCollider();*/
#pragma endregion __


#pragma region ver2 - 8 direction movements

	m_vPos = { WINCX / 2.f, WINCY / 2.f, 0.f };
	m_vScale = { 50.f, 50.f, 0.f };

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

<<<<<<< Updated upstream
#pragma endregion __
=======
	time = 0.06f;
>>>>>>> Stashed changes
}

int CPlayer::Update(void)
{
	if (false == m_bActive)
		return OBJ_DEAD;
#pragma region original version (tank mode)
	//   if (!m_bActive)
	//       return OBJ_DEAD;

	   //m_vDirPos.x = 0;
	   //m_vDirPos.y = 0;
	   //// 키입력에 따른 update 따로 key_input함수로 이동
	   //key_input();

	//   for (auto& iter : m_vecComponents)
	//       iter->Update();                                    

	//   return 0;
#pragma endregion __

	key_input();
	player_direction(m_eDirection);
	CalcMat();//이동과 회전 관련 매트릭스 처리를 관리하는 함수
	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	m_vMoveSize = m_vWorldDir * m_fSpeed * DT;

	m_vPos += m_vMoveSize;

	return OBJ_NOEVENT;
}

void CPlayer::Render(HDC hDC)
{
#pragma region original version (tank mode)
	/*MoveToEx(hDC, m_vCoord[LT].x, m_vCoord[LT].y, NULL);
	LineTo(hDC, m_vCoord[LB].x, m_vCoord[LB].y);
	LineTo(hDC, m_vCoord[RB].x, m_vCoord[RB].y);
	LineTo(hDC, m_vCoord[RT].x, m_vCoord[RT].y);
	LineTo(hDC, m_vCoord[LT].x, m_vCoord[LT].y);*/
#pragma endregion __

#pragma region ver2 - 8 direction movements
	
	MoveToEx(hDC
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
	EllipseDrawCenter(hDC, m_vWorldPoint[2].x, m_vWorldPoint[2].y, 10, 10);


#pragma endregion __


	for (auto& iter : m_vecComponents)
        iter->Render(hDC);
}

void CPlayer::Release(void)
{
    
}

void CPlayer::key_input()
{
	m_fSpeed = 100.f;
<<<<<<< Updated upstream
		
#pragma region original version (tank mode)
	//if (MGR(CKeyMgr)->isStayKeyDown('A'))
	//	m_fRadian -= D3DXToRadian(5.f);
	//if (MGR(CKeyMgr)->isStayKeyDown('D'))
	//	m_fRadian += D3DXToRadian(5.f);
	//if (MGR(CKeyMgr)->isStayKeyDown('W'))
	//{
	//	D3DXMATRIX infoRotZMat;
	//	D3DXMATRIX infoTranslateLocalMat;
	//	D3DXMATRIX infoWorldMat;
	//	D3DXMATRIX infoParentMat;

	//	D3DXMatrixRotationZ(&infoRotZMat, m_fRadian);
	//	D3DXMatrixTranslation(&infoTranslateLocalMat, 0, -m_fSpeed * DT, 0);
	//	D3DXMatrixTranslation(&infoParentMat, m_vPos.x, m_vPos.y, 0);
	//	infoWorldMat = infoTranslateLocalMat * infoRotZMat * infoParentMat;
	//	D3DXVec3TransformCoord(&m_vPos, &D3DXVECTOR3(0, 0, 0), &infoWorldMat);
	//	//D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &infoParentMat);
	//}
	//if (MGR(CKeyMgr)->isStayKeyDown('S'))
	//{
	//	D3DXMATRIX infoRotZMat;
	//	D3DXMATRIX infoTranslateLocalMat;
	//	D3DXMATRIX infoWorldMat;
	//	D3DXMATRIX infoParentMat;

	//	//로테이션이랑 트랜스레이션 함수가 기본적으로 매트릭스를 초기화시켜줌
	//	D3DXMatrixRotationZ(&infoRotZMat, m_fRadian);
	//	D3DXMatrixTranslation(&infoTranslateLocalMat, 0, m_fSpeed * DT, 0);
	//	D3DXMatrixTranslation(&infoParentMat, m_vPos.x, m_vPos.y, 0);
	//	infoWorldMat = infoTranslateLocalMat * infoRotZMat * infoParentMat;
	//	D3DXVec3TransformCoord(&m_vPos, &D3DXVECTOR3(0, 0, 0), &infoWorldMat);
	//	//D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &infoParentMat);
	//}
#pragma endregion __



#pragma region 8방향이동으로 수정, 이동방향을 바라보도록 수정중
	// 움직이는 키는 임시로 I(상), K(하), J(좌), L(우)
	if (MGR(CKeyMgr)->isStayKeyDown(VK_UP))
=======
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
		}
	}



	if (KEYAWAY(E))
	{
		tik = 0.f;
		bShoot = false;
	}


	CalcMat();
}

void CPlayer::player_movement()
{
	if (KEYHOLD(UP))
>>>>>>> Stashed changes
	{
		// 상 이동
		m_eDirection = DIRECTION::UP;
<<<<<<< Updated upstream
		if (MGR(CKeyMgr)->isStayKeyDown(VK_LEFT))
		{
			m_eDirection = DIRECTION::UPLEFT;
		}
		else if (MGR(CKeyMgr)->isStayKeyDown(VK_RIGHT))
		{
=======

		if (KEYHOLD(LEFT))
			m_eDirection = DIRECTION::UPLEFT;
		else if (KEYHOLD(RIGHT))
>>>>>>> Stashed changes
			m_eDirection = DIRECTION::UPRIGHT;
		}
	}

	else if (KEYHOLD(DOWN))
	{
		// 하 이동
		m_eDirection = DIRECTION::DOWN;
<<<<<<< Updated upstream
		if (MGR(CKeyMgr)->isStayKeyDown(VK_LEFT))
		{
			m_eDirection = DIRECTION::DOWNLEFT;
		}
		else if (MGR(CKeyMgr)->isStayKeyDown(VK_RIGHT))
		{
=======

		if (KEYHOLD(LEFT))
			m_eDirection = DIRECTION::DOWNLEFT;
		else if (KEYHOLD(RIGHT))
>>>>>>> Stashed changes
			m_eDirection = DIRECTION::DOWNRIGHT;
		}
	}

<<<<<<< Updated upstream
	else if (MGR(CKeyMgr)->isStayKeyDown(VK_LEFT))
	{
		// 좌 이동
=======
	else if (KEYHOLD(LEFT))
>>>>>>> Stashed changes
		m_eDirection = DIRECTION::LEFT;
	}

<<<<<<< Updated upstream
	else if (MGR(CKeyMgr)->isStayKeyDown(VK_RIGHT))
	{
		// 우 이동
=======
	else if (KEYHOLD(RIGHT))
>>>>>>> Stashed changes
		m_eDirection = DIRECTION::RIGHT;
	}
#pragma endregion __

	else
	{
		// 키를 누르고 있지 않은 동안은 움직이지 않도록
		m_eDirection = DIRECTION::NONE;
		m_fSpeed = 0.f;
	}

<<<<<<< Updated upstream

	if (MGR(CKeyMgr)->isStayKeyDown(VK_SPACE))
	{
		// 총의 종류에 따라 쏘는 총알이 달라지도록 변경
		// create bullet
		MGR(CObjMgr)->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<CBullet_Pistol>::Create(m_vPos.x, m_vPos.y, m_fRadian));
	}


	CalcMat();
=======
void CPlayer::player_change_gun()
{
	if (KEYAWAY(Q))
	{
		if (nullptr != m_pGun)
			m_pGun->Set_Active(false);

		m_ePlayerGun = GUN_TYPE::PISTOL;
		MGR(CObjMgr)->AddObject(OBJID::OBJ_GUN, CAbstractFactory<CPistol>::Create());
		time = m_pGun->Get_ShotInterval();
	}
		

	if (KEYAWAY(W))
	{
		if (nullptr != m_pGun) m_pGun->Set_Active(false);

		m_ePlayerGun = GUN_TYPE::PISTOL;
		MGR(CObjMgr)->AddObject(OBJID::OBJ_GUN, CAbstractFactory<CPistol>::Create());
		time = m_pGun->Get_ShotInterval();
	}
>>>>>>> Stashed changes
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
		// m_vDir = { -1.f, 1.f, 0.f };
		m_fRadian = D3DXToRadian(135);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWNRIGHT:
		// m_vDir = { 1.f, 1.f, 0.f };
		m_fRadian = D3DXToRadian(45);
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}
}

void CPlayer::OnCollision(CCollider * _pOther)
{
}

void CPlayer::OnCollisionEnter(CCollider * _pOther)
{
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
