#pragma once
#include "Unit.h"

class CBullet :
	public CUnit
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Init() PURE;
	virtual int Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

public:
	virtual void OnCollision(CCollider * _pOther) PURE;
	virtual void OnCollisionEnter(CCollider * _pOther) PURE;
	virtual void OnCollisionExit(CCollider * _pOther) PURE;
	virtual void OnTrigger(CCollider * _pOther) PURE;
	virtual void OnTriggerEnter(CCollider * _pOther) PURE;
	virtual void OnTriggerExit(CCollider * _pOther) PURE;

public:
	void set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

protected:
	CObj*	m_pPlayer;
	float	m_fLifeTime;
};