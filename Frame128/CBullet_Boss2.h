#pragma once
#include "Bullet.h"
class CBullet_Boss2 :
	public CBullet
{
public:
	CBullet_Boss2();
	virtual ~CBullet_Boss2();

public:
	// CBullet��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual int Update();
	virtual void OnCollision(CCollider * _pOther) override;
	virtual void OnCollisionEnter(CCollider * _pOther) override;
	virtual void OnCollisionExit(CCollider * _pOther) override;
	virtual void OnTrigger(CCollider * _pOther) override;
	virtual void OnTriggerEnter(CCollider * _pOther) override;
	virtual void OnTriggerExit(CCollider * _pOther) override;
};

