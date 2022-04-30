#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "Collider.h"
#include "Obj.h"
#include "ObjMgr.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
    Release();
}

void CMonster::OnCollision(CCollider* _pOther)
{
   
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
    if (_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_BULLET)
    {
      //  m_bActive = false;
    }
}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
}

void CMonster::OnTrigger(CCollider* _pOther)
{
}

void CMonster::OnTriggerEnter(CCollider* _pOther)
{
}

void CMonster::OnTriggerExit(CCollider* _pOther)
{
}

void CMonster::Init(void)
{
}

int CMonster::Update(void)
{
    return 0;
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release(void)
{
}

void CMonster::FindTarget()
{   
    m_pTarget = MGR(CObjMgr)->Get_Player();
}

void CMonster::SetRadianToPlayer()
{
    //플레이어에서 자신의 위치를 빼서 방향벡터를 만들고, 정규화시켜줌
    D3DXVECTOR3 dirVec = m_pTarget->Get_Pos() - m_vPos;
    D3DXVec3Normalize(&dirVec, &dirVec);//정규화된 벡터나옴.
    //룩 벡터랑(가로) 정규화된 방향 벡터랑 내적한 값(코사인)을 아크코사인에 넣어 라디안값으로변경
    m_fRadian = acosf(D3DXVec3Dot(&m_vDir, &dirVec));
    if (m_vPos.y > m_pTarget->Get_Pos().y)
    {
        m_fRadian = PI2 - m_fRadian;
    }
    int a = 10;
}
