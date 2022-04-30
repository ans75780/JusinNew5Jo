#pragma once
#include "Obj.h"
class CGun :
	public CObj
{
public:
	CGun();
	virtual ~CGun();

public:
	virtual void Init() PURE;
	virtual int Update();
	virtual void Render(HDC hDC);
	virtual void Release() PURE;

protected:
	GUN_TYPE	m_eType = GUN_TYPE::END;

	float m_fShootInterval;

	int m_iMaxLoad;
	int m_iCurLoad;


public:
	float Get_ShotInterval() { return m_fShootInterval; }

private:
	GUN_TYPE	get_Type() { return m_eType; }
	friend class CBullet;

public:
	virtual void OnCollision(CCollider * _pOther) PURE;
	virtual void OnCollisionEnter(CCollider * _pOther) PURE;
	virtual void OnCollisionExit(CCollider * _pOther) PURE;
	virtual void OnTrigger(CCollider * _pOther) PURE;
	virtual void OnTriggerEnter(CCollider * _pOther) PURE;
	virtual void OnTriggerExit(CCollider * _pOther) PURE;
};