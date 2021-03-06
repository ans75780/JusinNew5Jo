#pragma once
class CTimer
{
private:
	bool m_isHardware;		//고성능 타이머를 지원하냐?
	float m_timeScale;		//시간경과량
	float m_timeElapsed;	//한 프레임당 경과량
	__int64 m_curTime;		//현재시간
	__int64 m_lastTime;		//마지막 시간
	__int64 m_periodFrequency;	//시간주기

	unsigned long m_frameRate;		//FPS
	unsigned long m_FPSframeCount;	//FPS 카운트
	float m_FPStimeElapsed;			//FPS 마지막 시간과 현재 시간의 경과량
	float m_worldTime;				//전체 시간 경과량

public:
	CTimer();
	~CTimer();

	HRESULT Init();

	//현재 시간 계산
	void Tick(float lockFPS = 0.0f);
	//현재 FPS 가져오기
	unsigned long GetFrameRate(TCHAR* str = nullptr) const;
	//한프레임당 경과 시간
	float GetElapsedTime() const { return m_timeElapsed; }
	//전체 경과 시간 가져오기
	float GetWorldTime() const { return m_worldTime; }

};

