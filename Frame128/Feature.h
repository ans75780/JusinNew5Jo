#pragma once

#include "../Header/Include.h"
#include "Obj.h"

class CFeature : public CObj
{
public:
	CFeature();
	~CFeature();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Init(void) override;
	virtual int Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
private:

	// CObj��(��) ���� ��ӵ�
	virtual void OnCollision(CCollider * _pOther) override;
	virtual void OnCollisionEnter(CCollider * _pOther) override;
	virtual void OnCollisionExit(CCollider * _pOther) override;
	virtual void OnTrigger(CCollider * _pOther) override;
	virtual void OnTriggerEnter(CCollider * _pOther) override;
	virtual void OnTriggerExit(CCollider * _pOther) override;
};

