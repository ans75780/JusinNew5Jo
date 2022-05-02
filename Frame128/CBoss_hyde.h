#pragma once
#include "Monster.h"
class CBoss_hyde :
	public CMonster
{
public:
	CBoss_hyde();
	virtual ~CBoss_hyde();

public:
	virtual void Init(void);
	virtual int Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

private:
	float m_fshoot_interval;
	float m_fshoot_interval2;
	float m_fshoot_interval3;
	float m_ftik;
	float m_ftik2;
	float m_ftik3;
};
