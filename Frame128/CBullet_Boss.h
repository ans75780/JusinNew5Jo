#pragma once
#include "Bullet.h"
class CBullet_Boss :
	public CBullet
{
public:
	CBullet_Boss();
	virtual ~CBullet_Boss();

public:
	virtual void Init();
	virtual int Update();

public:
	virtual void OnCollision(CCollider * _pOther);
	virtual void OnCollisionEnter(CCollider * _pOther);
	virtual void OnCollisionExit(CCollider * _pOther);
	virtual void OnTrigger(CCollider * _pOther);
	virtual void OnTriggerEnter(CCollider * _pOther);
	virtual void OnTriggerExit(CCollider * _pOther);
};
