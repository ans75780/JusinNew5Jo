#pragma once
#include "CGun.h"
class CPistol :
	public CGun
{
public:
	CPistol();
	virtual ~CPistol();

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

