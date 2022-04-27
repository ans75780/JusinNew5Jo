#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
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
    m_fAngle = 0.f;
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

    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
        m_vPos.x -= m_fSpeed;
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
        m_vPos.x += m_fSpeed;
    if (KEYMANAGER->isStayKeyDown(VK_UP))
        m_vPos.y -= m_fSpeed;
    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
        m_vPos.y += m_fSpeed;
    int a = 0;

    for (auto& iter : m_vecComponents)
        iter->Update();
    return 0;
}

void CPlayer::Render(HDC hDC)
{
    RectDrawCenter(hDC, m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y);
    for (auto& iter : m_vecComponents)
        iter->Render(hDC);
}

void CPlayer::Release(void)
{
    for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
    m_vecComponents.clear();
    m_strName.clear();
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
