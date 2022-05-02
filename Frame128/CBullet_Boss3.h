#pragma once
#include "Bullet.h"
class CBullet_Boss3 :
	public CBullet
{
public:
	CBullet_Boss3();
	virtual ~CBullet_Boss3();

public:
	virtual void Init() override;
	virtual int Update();

public:
	virtual void OnCollision(CCollider * _pOther) override;
	virtual void OnCollisionEnter(CCollider * _pOther) override;
	virtual void OnCollisionExit(CCollider * _pOther) override;
	virtual void OnTrigger(CCollider * _pOther) override;
	virtual void OnTriggerEnter(CCollider * _pOther) override;
	virtual void OnTriggerExit(CCollider * _pOther) override;
};

