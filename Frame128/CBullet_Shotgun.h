#pragma once
#include "Bullet.h"
class CBullet_Shotgun :
	public CBullet
{
public:
	CBullet_Shotgun();
	virtual ~CBullet_Shotgun();

public:
	virtual void Init();
	virtual int Update();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	virtual void OnCollision(CCollider * _pOther);
	virtual void OnCollisionEnter(CCollider * _pOther);
	virtual void OnCollisionExit(CCollider * _pOther);
	virtual void OnTrigger(CCollider * _pOther);
	virtual void OnTriggerEnter(CCollider * _pOther);
	virtual void OnTriggerExit(CCollider * _pOther);
};

