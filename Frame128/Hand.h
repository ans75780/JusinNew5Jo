#pragma once
#include "Obj.h"
class CHand :
    public CObj
{
public:
    CHand(CObj* _pTarget, DXV3 _vOffset);
    virtual ~CHand();
public:
    // CObj을(를) 통해 상속됨
    virtual void Init(void) override;
    virtual int Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void OnCollision(CCollider* _pOther) override;
    virtual void OnCollisionEnter(CCollider* _pOther) override;
    virtual void OnCollisionExit(CCollider* _pOther) override;
    virtual void OnTrigger(CCollider* _pOther) override;
    virtual void OnTriggerEnter(CCollider* _pOther) override;
    virtual void OnTriggerExit(CCollider* _pOther) override;
private:
    CObj* m_pTarget;
    DXV3 m_vOffset;
};

