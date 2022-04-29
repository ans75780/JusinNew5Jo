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
    virtual void Init();
    virtual int  Update();
    virtual void Render(HDC hDC);
    virtual void Release();

private:
	GUN_TYPE m_ePlayerGun = GUN_TYPE::PISTOL;
	DIRECTION m_eDirection = DIRECTION::NONE;
	float tik, time;
	bool bFire;

public:
	DIRECTION get_eDir() { return m_eDirection; }
	

public:
	void key_input();
	void player_movement();
	void player_change_gun();
	void player_direction(DIRECTION _eDir);

public:
	bool shoot() { return bFire; }

private:
	virtual void OnCollision(CCollider * _pOther) ;
	virtual void OnCollisionEnter(CCollider * _pOther);
	virtual void OnCollisionExit(CCollider * _pOther);
	virtual void OnTrigger(CCollider * _pOther);
	virtual void OnTriggerEnter(CCollider * _pOther);
	virtual void OnTriggerExit(CCollider * _pOther);
private:
	//virtual void CalcMat();
};

