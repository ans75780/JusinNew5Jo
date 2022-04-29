#pragma once
#include "Include.h"
#include "Unit.h"

#define LT 0
#define LB 1
#define RT 2
#define RB 3

class CGun;

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

public:

	DIRECTION m_eDirection = DIRECTION::NONE;
<<<<<<< Updated upstream

=======
	float tik, time;
	bool bShoot;
	bool bPressSpace;
	CGun* m_pGun = nullptr;
>>>>>>> Stashed changes

public:
	void set_gun(CGun* _pGun) {
		m_pGun = _pGun;
	}
public:
	DIRECTION get_eDir() { return m_eDirection; }
	

public:
	void key_input();
	void player_direction(DIRECTION _eDir);

<<<<<<< Updated upstream
=======
public:
	bool shoot() { return bShoot; }

>>>>>>> Stashed changes
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

