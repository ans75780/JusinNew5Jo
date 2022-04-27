#pragma once

#include "../Header/Include.h"
#include "Obj.h"

class CFeature : public CObj
{
public:
	CFeature();
	~CFeature();
public:
	// CObj을(를) 통해 상속됨
	virtual void Init(void) override;
	virtual int Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
private:
};

