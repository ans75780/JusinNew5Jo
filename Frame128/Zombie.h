#pragma once
#include "Monster.h"
class CZombie :
    public CMonster
{
public:
    CZombie();
    virtual ~CZombie();
public:
    // CMonster��(��) ���� ��ӵ�
    virtual void Init(void) override;
    virtual int Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
};

