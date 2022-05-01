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
};

