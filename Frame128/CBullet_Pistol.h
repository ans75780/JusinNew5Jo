#pragma once
#include "Bullet.h"
class CBullet_Pistol :
	public CBullet
{
public:
	CBullet_Pistol();
	virtual ~CBullet_Pistol();

public:
	virtual void Init(); // 앤 또 정의가 없다고 하고
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

