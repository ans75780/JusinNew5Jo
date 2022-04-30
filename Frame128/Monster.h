#pragma once
#include "Unit.h"

#include "Stat.h"

class CMonster :
    public CUnit
{
public:
    CMonster();
    virtual ~CMonster();
public:
    // CUnit을(를) 통해 상속됨
    virtual void OnCollision(CCollider* _pOther) override;
    virtual void OnCollisionEnter(CCollider* _pOther) override;
    virtual void OnCollisionExit(CCollider* _pOther) override;
    virtual void OnTrigger(CCollider* _pOther) override;
    virtual void OnTriggerEnter(CCollider* _pOther) override;
    virtual void OnTriggerExit(CCollider* _pOther) override;

    virtual void Init(void) PURE;
    virtual int Update(void) PURE;
    virtual void Render(HDC hDC) PURE;
    virtual void Release(void) PURE;
    virtual void    FindTarget();//Obj매니저에서 타겟을 찾아서 넣어줌.
    void	SetRadianToPlayer();//플레이어를 바라보는 각도 찾기.
    CStat& Get_Stat() { return m_UnitStat; }
protected:
    CStat m_UnitStat;
private:
    CObj* m_pTarget;
 
};

