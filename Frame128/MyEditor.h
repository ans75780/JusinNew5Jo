#pragma once
#include "scene.h"
class CMyEditor :
	public CScene
{
public:
	CMyEditor();
	virtual ~CMyEditor();

private:
	void Key_Input(void);

public:
	virtual HRESULT Init(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

};

