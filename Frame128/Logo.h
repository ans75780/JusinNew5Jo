#pragma once
#include "Scene.h"
class CLogo : public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	virtual HRESULT Init(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

