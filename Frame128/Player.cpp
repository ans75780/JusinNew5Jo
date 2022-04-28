#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "AbstractFactory.h"
#include "Bullet.h"

CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{
    Release();
}
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
	m_vDir = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { -m_vScale.x, -m_vScale.y, 0.f };
	m_vPoint[1] = { m_vScale.x, -m_vScale.y, 0.f };
	m_vPoint[2] = { m_vScale.x, m_vScale.y, 0.f };
	m_vPoint[3] = { -m_vScale.x, m_vScale.y, 0.f };

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
#pragma endregion __
}

int CPlayer::Update(void)
{
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


#pragma region ver2 - 8 direction movements
	if (m_bActive)
		return OBJ_DEAD;

	key_input();

	return OBJ_NOEVENT;
#pragma endregion __
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

#pragma region #pragma region ver2 - 8 direction movements
	MoveToEx(hDC, m_vWorldPoint[0].x, m_vWorldPoint[0].y, nullptr);
	
	for (int i(1); i < sizeof(4); ++i)
	{
		LineTo(hDC, m_vWorldPoint[i].x, m_vWorldPoint[i].y);
	}
#pragma endregion __
	for (auto& iter : m_vecComponents)
        iter->Render(hDC);
}

void CPlayer::Release(void)
{
    for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
    m_vecComponents.clear();
    m_strName.clear();
}

void CPlayer::key_input()
{
	// 플레이어 8방향으로 수정요망
	// 그러면 플레이어가 바라보는 방향으로 총알이 나가도록 수정 (포신없음)
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
	if (MGR(CKeyMgr)->isStayKeyDown('I'))
	{
		// 상 이동
		m_eDirection = DIRECTION::UP;
	}

	if (MGR(CKeyMgr)->isStayKeyDown('K'))
	{
		// 하 이동
		m_eDirection = DIRECTION::DOWN;
	}

	if (MGR(CKeyMgr)->isStayKeyDown('J'))
	{
		// 좌 이동
		m_eDirection = DIRECTION::LEFT;
	}

	if (MGR(CKeyMgr)->isStayKeyDown('L'))
	{
		// 우 이동
		m_eDirection = DIRECTION::RIGHT;
	}

	switch (m_eDirection)
	{
	case DIRECTION::UP:
		m_vDir = { 0.f, -1.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::DOWN:
		m_vDir = { 0.f, 1.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::LEFT:
		m_vDir = { -1.f, 0.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;

	case DIRECTION::RIGHT:
		m_vDir = { 1.f, 0.f, 0.f };
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		break;
	}
#pragma endregion __

	


	if (MGR(CKeyMgr)->isOnceKeyUp(VK_SPACE))
	{
		// create bullet
		MGR(CObjMgr)->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_vPos.x, m_vPos.y, m_fRadian));
	}
	CalcMat();
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

void CPlayer::CalcMat()
{
	DXMAT		matScale;
	DXMAT		matRotZ;
	DXMAT		matTransform;
	DXMAT		matWheelTransform;//각각 휠의 행렬을 담을 좌표
	DXMAT		matWheelRotZ;//각각 휠의 행렬을 담을 좌표
	DXMAT		matWheelLocal;
	DXV3		m_tPos;
	DXV3		m_tAngle;

	
	m_tPos = m_vPos;
	float angle = D3DXToDegree(m_fRadian);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fRadian);
	D3DXMatrixTranslation(&matTransform, m_vPos.x, m_vPos.y, 0.f);
	m_matLocal = matScale * matRotZ * matTransform;

	for (int i = 0; i < 4; i++)
	{
		D3DXMatrixTranslation(&matWheelTransform, m_vWheel[i].x, m_vWheel[i].y, 0.f);

		//바퀴 입장에서는 플레이어의 m_matLocal이 월드이기에 휠 로컬을 앞에서 곱해준다.
		// 크 * 자 * 이  * 공
		matWheelLocal = matWheelTransform * m_matLocal;
		D3DXVec3TransformCoord(&m_vCoord[i], &m_vWheel[i], &matWheelLocal);
	}

}
