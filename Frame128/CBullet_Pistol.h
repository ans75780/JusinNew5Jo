#pragma once
#include "Bullet.h"
class CBullet_Pistol :
	public CBullet
{
public:
	CBullet_Pistol();
	virtual ~CBullet_Pistol();

public:
	virtual void Init();

public:
	virtual void OnCollision(CCollider * _pOther);
	virtual void OnCollisionEnter(CCollider * _pOther);
	virtual void OnCollisionExit(CCollider * _pOther);
	virtual void OnTrigger(CCollider * _pOther);
	virtual void OnTriggerEnter(CCollider * _pOther);
	virtual void OnTriggerExit(CCollider * _pOther);
};

