#pragma once
#include "Include.h"
#include "Unit.h"

#define LT 0
#define LB 1
#define RT 2
#define RB 3


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
	enum class DIRECTION
	{
		UP, DOWN, LEFT, RIGHT,
		UPLEFT, UPRIGHT,
		DOWNLEFT, DOWNRIGHT,
		NONE
	};

	DIRECTION m_eDirection = DIRECTION::NONE;
public:
	void key_input();
	void player_direction(DIRECTION _eDir);

private:
	virtual void OnCollision(CCollider * _pOther) override;
	virtual void OnCollisionEnter(CCollider * _pOther) override;
	virtual void OnCollisionExit(CCollider * _pOther) override;
	virtual void OnTrigger(CCollider * _pOther) override;
	virtual void OnTriggerEnter(CCollider * _pOther) override;
	virtual void OnTriggerExit(CCollider * _pOther) override;
private:
	void		CalcMat();
private:
	
};

