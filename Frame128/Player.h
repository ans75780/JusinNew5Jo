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
};

