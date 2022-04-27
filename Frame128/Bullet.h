#pragma once
#include "Unit.h"

typedef D3DXVECTOR3 DXV3;
typedef D3DXMATRIX	DXMAT;

class CBullet :
	public CUnit
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Init(void);
	virtual int Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

public:
	virtual void OnCollision(CCollider * _pOther);
	virtual void OnCollisionEnter(CCollider * _pOther);
	virtual void OnCollisionExit(CCollider * _pOther);
	virtual void OnTrigger(CCollider * _pOther);
	virtual void OnTriggerEnter(CCollider * _pOther);
	virtual void OnTriggerExit(CCollider * _pOther);

public:
	void set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }

private:
	CObj*	m_pPlayer;
	
	DXV3 vLocalPos;
	DXV3 vLocalScale;
	DXV3 vLocalDir;

	DXMAT m_matWorld;

	// Local Rect
	DXV3	vLocalLT;
	DXV3	vLocalRT;
	DXV3	vLocalRB;
	DXV3	vLocalLB;

	

	DXV3 vWorldPos;
	DXV3 vWorldScale;
	DXV3 vWorldDir;
	
	// World Rect
	DXV3	vWorldLT;
	DXV3	vWorldRT;
	DXV3	vWorldRB;
	DXV3	vWorldLB;
};