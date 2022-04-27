#pragma once

#include "Unit.h"

class CPlayer :
    public CUnit
{
public:
    CPlayer();
    virtual ~CPlayer();
public:
    virtual void    Init(void) override;
    virtual int     Update(void) override;
    virtual void    Render(HDC hDC) override;
    virtual void    Release(void) override;
private:

	// CUnit��(��) ���� ��ӵ�
	virtual void OnCollision(CCollider * _pOther) override;
	virtual void OnCollisionEnter(CCollider * _pOther) override;
	virtual void OnCollisionExit(CCollider * _pOther) override;
	virtual void OnTrigger(CCollider * _pOther) override;
	virtual void OnTriggerEnter(CCollider * _pOther) override;
	virtual void OnTriggerExit(CCollider * _pOther) override;
};

