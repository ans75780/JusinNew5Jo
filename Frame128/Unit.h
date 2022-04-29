#pragma once
#include "Obj.h"
// 움직일 수 있는 애들
class CUnit :
    public CObj
{
public:
    CUnit();
    virtual ~CUnit();
    // CObj을(를) 통해 상속됨
    virtual void    Init(void) PURE;
    virtual int      Update(void) PURE;
    virtual void    Render(HDC hDC) PURE;
    virtual void    Release(void) PURE;

protected:
    float           m_fSpeed;
    float           m_fAtk;	// 공격력
    float           m_fHP;
    float           m_fMaxHP;


    
	// 추가적으로 변수 추가 요망

    
};

