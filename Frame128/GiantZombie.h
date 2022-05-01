#pragma once
#include "Monster.h"
class CGiantZombie :
    public CMonster
{
public:
    CGiantZombie();
    virtual ~CGiantZombie();
public:
    // CMonster을(를) 통해 상속됨
    virtual void Init(void) override;
    virtual int Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;

    virtual void Set_Active(bool _isActive) final;

private:
    DXV3 m_vImgScale;

    float m_fImgTime = 0.75f;
    float m_fCurTime = m_fImgTime;
    int m_iColor = 255;
    bool    m_bUpdated;
};

