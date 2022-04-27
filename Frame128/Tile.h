#pragma once
#include "Obj.h"
class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }
	int			Get_DrawID() { return m_iDrawID; }
public:
	virtual void	Init(void) override;
	virtual int	Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	TCHAR	m_strType[MIN_STR];
	int		m_iDrawID = 0;
	int		m_iOption = 0;

	// CObj을(를) 통해 상속됨
	virtual void OnCollision(CCollider * _pOther) override;
	virtual void OnCollisionEnter(CCollider * _pOther) override;
	virtual void OnCollisionExit(CCollider * _pOther) override;
	virtual void OnTrigger(CCollider * _pOther) override;
	virtual void OnTriggerEnter(CCollider * _pOther) override;
	virtual void OnTriggerExit(CCollider * _pOther) override;
};

