#pragma once
#include "Monster.h"
class CZombie :
    public CMonster
{
public:
    CZombie();
    virtual ~CZombie();
public:
    // CMonster을(를) 통해 상속됨
    virtual void Init(void) override;
    virtual int Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
};

