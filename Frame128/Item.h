#pragma once
#include "Obj.h"
class CItem :
    public CObj
{
public:
    CItem();
    virtual ~CItem();

public:
    void AddMagnetic();


protected:
    float m_fTargetDistance = 130.f;
    CObj* m_pTarget = nullptr;
    float m_fSpeed = 100.f;

};

