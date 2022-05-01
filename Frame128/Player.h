#pragma once
#include "Include.h"
#include "Unit.h"
#include "Stat.h"

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
	float tik, time;
	bool bShoot;
	bool bPressSpace;
	CGun* m_pGun = nullptr;
public:
	void set_gun(CGun* _pGun) {
		m_pGun = _pGun;
	}
public:
	DIRECTION get_eDir() { return m_eDirection; }
	

public:
	void key_input();
	void player_movement();
	void player_change_gun();
	void player_direction(DIRECTION _eDir);

public:
	bool shoot() { return bShoot; }


private:
	virtual void OnCollision(CCollider * _pOther) ;
	virtual void OnCollisionEnter(CCollider * _pOther);
	virtual void OnCollisionExit(CCollider * _pOther);
	virtual void OnTrigger(CCollider * _pOther);
	virtual void OnTriggerEnter(CCollider * _pOther);
	virtual void OnTriggerExit(CCollider * _pOther);
private:
	//virtual void CalcMat();
	int             m_iCoin;
	GUN_TYPE	m_ePlayerGun = GUN_TYPE::END;
	CStat			m_UnitStat;
	float m_fCurTime = 0.003f;
	TCHAR	szStr[MAX_STR];
	DIRECTION	m_ePrevDir;
};

