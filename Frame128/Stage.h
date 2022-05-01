#pragma once
#include "Scene.h"
#include "TimerEvent.h"
#include "Player.h"

class CStage :
	public CScene, public ITimerEvent
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual HRESULT Init(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


	// ITimerEvent을(를) 통해 상속됨
	virtual void OnTimerEvent(int _iEventNum) override;

private:
	void SpawnZombie();
	void SpawnItem();
	DXV3	pt;
	DXV3 mapSize;
	DXV3 half;
	RECT rc;
};

