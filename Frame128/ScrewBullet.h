#pragma once
#include "Obj.h"
class CScrewBullet :
	public CObj
{
public:
	CScrewBullet();
	virtual ~CScrewBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	bool		m_bStart;
	float		m_fRotAngle;	// 회전각
	float		m_fRotSpeed;	// 회전각의 변화량


	POINT		m_tCenter;

};

