#pragma once
#include "SingletonBase.h"
#include "Timer.h"
#include "TimerEvent.h"


struct TimerEventGroup
{
	ITimerEvent* pTimerEvent;
	int iEventNum;
};


class CTimeMgr : public CSingletonBase<CTimeMgr>
{
	friend CSingletonBase;
private:
	CTimer* m_pTimer;

private:
	CTimeMgr();
	~CTimeMgr();
public:
	HRESULT Init();
	void Release();
	void Update(float lock = 0.0f);
	void Render(HDC hdc);
	void Render(HWND hWnd);
	//한 프레임당 경과시간 가져오기 1/60
	float getElasedTime() const { return m_pTimer->GetElapsedTime(); }
	//전체 시간 경과량 가져오기
	float getWorldTime() const { return m_pTimer->GetWorldTime(); }

	void AddEvent(float _fTime, ITimerEvent* _pTimerEvent, int _iEventNum);
	void AddLoopEvent(float _fTime, ITimerEvent* _pTimerEvent, int _iEventNum);
	void RemoveLoopEvent(ITimerEvent* _pTimerEvent, int _iEventNum);


private:
	void UpdateTimerEvent();

private:
	list<pair<float, TimerEventGroup>> m_TimerEvents;
	list<pair<float, TimerEventGroup>> m_LoopTimerEvents;

};

