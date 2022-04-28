#pragma once
#include "Unit.h"
class CMonster :
    public CUnit
{
public:
    CMonster();
    virtual ~CMonster();
public:
    // CUnit��(��) ���� ��ӵ�
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
    virtual void    FindTarget();//Obj�Ŵ������� Ÿ���� ã�Ƽ� �־���.
    void	SetRadianToPlayer();//�÷��̾ �ٶ󺸴� ���� ã��.
private:
    CObj* m_pTarget;
};

