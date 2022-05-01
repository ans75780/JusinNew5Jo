#pragma once
#include "Unit.h"

class CBullet :
	public CUnit
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Init() PURE;
	virtual int Update();
	virtual void Render(HDC hDC);
	virtual void Release();

public:
	virtual void OnCollision(CCollider * _pOther) PURE;
	virtual void OnCollisionEnter(CCollider * _pOther) PURE;
	virtual void OnCollisionExit(CCollider * _pOther) PURE;
	virtual void OnTrigger(CCollider * _pOther) PURE;
	virtual void OnTriggerEnter(CCollider * _pOther) PURE;
	virtual void OnTriggerExit(CCollider * _pOther) PURE;

protected:
	float create_x_spread();
	float create_y_spread();
	void set_bullet_dir(DIRECTION _eDir);

protected:
	DXMAT	m_matPos;


	DXV3	m_vLocalPos;	// ���� ��ǥ�� ��ġ
	DXV3	m_vInitPos;		// �ʱ� ��ġ
	DXV3	m_vWorldPos;	// ���� ��ǥ�� ��ġ

	float	m_fLifeTime;
	
	int	m_iSpreadRate;
	float m_fSpreadX;
	float m_fSpreadY;

	float m_fAtk;
};