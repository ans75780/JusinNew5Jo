#pragma once
#include "Include.h"
#include "Unit.h"




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


public:
	DIRECTION get_eDir() { return m_eDirection; }
	

public:
	void key_input();
	void player_direction(DIRECTION _eDir);

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
};

