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

    virtual void Set_Active(bool _isActive) final;

private:
    float m_fCurTime = 0.003f;
    bool    m_bUpdated;
};

