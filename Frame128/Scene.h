#pragma once

#include "../Header/Include.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual HRESULT Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Late_Update(void) = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release(void) = 0;
};

