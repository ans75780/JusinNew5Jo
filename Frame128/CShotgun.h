#pragma once
#include "CGun.h"
class CShotgun :
	public CGun
{
public:
	CShotgun();
	virtual ~CShotgun();

public:
	virtual void Init();
	virtual int Update();
	virtual void Release();

public:
	virtual void OnCollision(CCollider * _pOther);
	virtual void OnCollisionEnter(CCollider * _pOther);
	virtual void OnCollisionExit(CCollider * _pOther);
	virtual void OnTrigger(CCollider * _pOther);
	virtual void OnTriggerEnter(CCollider * _pOther);
	virtual void OnTriggerExit(CCollider * _pOther);

};

