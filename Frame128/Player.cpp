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
    m_vPos = { 300,300 };
    m_vScale = { 50,50 };
    m_fSpeed = 5.f;
    m_fRadian = 0.f;
    m_fAtk = 0.f;
    m_eID = OBJ_PLAYER;
    m_eRenderID = RENDERID::RENDER_OBJ;
    m_strName = L"Player";

    CreateCollider();
}

int CPlayer::Update(void)
{
    if (!m_bActive)
        return OBJ_DEAD;

	// 키입력에 따른 update 따로 key_input함수로 이동
	key_input();

    int a = 0;

    for (auto& iter : m_vecComponents)
        iter->Update();
    return 0;
}

void CPlayer::Render(HDC hDC)
{
    RectDrawCenter(hDC
		, int(m_vPos.x)
		, int(m_vPos.y)
		, int(m_vScale.x)
		, int(m_vScale.y));
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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		m_vPos.x -= m_fSpeed;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		m_vPos.x += m_fSpeed;
	if (KEYMANAGER->isStayKeyDown(VK_UP))
		m_vPos.y -= m_fSpeed;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		m_vPos.y += m_fSpeed;

	// 총알 날라가는지 확인하려고 임의로 준 angle 라디안 값
	m_fRadian = 0.3f;

	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		// create bullet
		OBJMANAGER->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_vPos.x, m_vPos.y, m_fRadian));
		
		// 총알 안날라감... --> 총알 날라가는 거 해결
		// 총알 일정 시간 경과하면 삭제되는 거 추가중 --> 추가완료
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
