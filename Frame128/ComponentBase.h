#pragma once

#include "../Header/Include.h"

class CComponentBase abstract
{
public:
	CComponentBase() {};
	virtual ~CComponentBase() {};
public:
	virtual void				Init() PURE;
	virtual void				Release() PURE;
	virtual void				Update() PURE;
	virtual void				Late_Update() PURE;
	virtual void				Render(HDC hDC) PURE;
};

