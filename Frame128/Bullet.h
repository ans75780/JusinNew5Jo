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


protected:
	float	m_fLifeTime;
	

};