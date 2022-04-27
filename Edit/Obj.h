#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO&		Get_Info(void) const	{ return m_tInfo; }
	const RECT&		Get_Rect()const			{ return m_tRect; }
	void			Set_Dead()				{ m_bDead = true; }
	bool			Get_Dead() { return m_bDead; }

	void			Set_Pos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}
	void			Set_X(float fX) { m_tInfo.fX += fX; }
	void			Set_Y(float fY) { m_tInfo.fY += fY; }

	void			Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

	void			Set_Dir(DIRECTION eDir) { m_eDir = eDir; }

	void			Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }

public:
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)	PURE;
	virtual void		Late_Update(void) PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release(void)	PURE;

protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	CObj*		m_pTarget;

	bool	m_bDead;
	float	m_fSpeed;
	float   m_fAngle;
	float	m_fDiagonal;

};

