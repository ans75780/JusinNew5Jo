#pragma once
class CTimer
{
private:
	bool m_isHardware;		//���� Ÿ�̸Ӹ� �����ϳ�?
	float m_timeScale;		//�ð������
	float m_timeElapsed;	//�� �����Ӵ� �����
	__int64 m_curTime;		//����ð�
	__int64 m_lastTime;		//������ �ð�
	__int64 m_periodFrequency;	//�ð��ֱ�

	unsigned long m_frameRate;		//FPS
	unsigned long m_FPSframeCount;	//FPS ī��Ʈ
	float m_FPStimeElapsed;			//FPS ������ �ð��� ���� �ð��� �����
	float m_worldTime;				//��ü �ð� �����

public:
	CTimer();
	~CTimer();

	HRESULT Init();

	//���� �ð� ���
	void Tick(float lockFPS = 0.0f);
	//���� FPS ��������
	unsigned long GetFrameRate(TCHAR* str = nullptr) const;
	//�������Ӵ� ��� �ð�
	float GetElapsedTime() const { return m_timeElapsed; }
	//��ü ��� �ð� ��������
	float GetWorldTime() const { return m_worldTime; }

};

