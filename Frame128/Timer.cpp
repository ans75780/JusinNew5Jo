#include "stdafx.h"
#include "Timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime �Լ��� ����ϱ� ���� ���̺귯�� �߰�
//�����찡 ���۵ǰ� �� ���� �ð��� ����

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}

HRESULT CTimer::Init()
{
	//���� Ÿ�̸� �������θ� üũ�Ѵ�.
	//���� Ÿ�̸Ӹ� �����ϸ� �ʴ� ����ũ�μ�������� ���� ����(1/1000000)
	//�ð� ����
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_periodFrequency))
	{
		//64��Ʈ ������ ����� �� �ֵ��� ������ ������
		//����ũ�� ���ϵ带(1/1000000)�� ���� �����Ͽ� �� �� ��Ȯ�� �ð����� �����ϱ� ����
		m_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_lastTime);
		//�ʴ� �ð� ��� ����
		m_timeScale = 1.0f / m_periodFrequency;
	}

	else
	{
		m_isHardware = false;
		//�и������� ������ �ð����� �ʴ� 1000�� ī���
		m_lastTime = timeGetTime();
		m_timeScale = 0.001f;
	}
	m_frameRate = 0;
	m_FPSframeCount = 0;
	m_FPStimeElapsed = 0.0f;
	m_worldTime = 0;

	return S_OK;
}

void CTimer::Tick(float lockFPS)
{
	//���� Ÿ�̸Ӹ� �����Ѵٸ�
	if (m_isHardware)
	{
		//�� ���� ����ũ���� ������ ���
		QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
	}
	else
	{
		//�������� ������ time�Լ��� �̿� �и�������
		m_curTime = timeGetTime();
	}
	//������ �ð��� ����ð��� �����
	m_timeElapsed = (m_curTime - m_lastTime) * m_timeScale;

	if (lockFPS > 0.0f)
	{
		//���� ������ �ð��� �����Ҷ����� �������Ѷ�
		while (m_timeElapsed < (1.0f / lockFPS))
		{
			if (m_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
			else m_curTime = timeGetTime();

			//������ �ð��� ����ð��� �����
			m_timeElapsed = (m_curTime - m_lastTime) * m_timeScale;
		}
	}

	m_lastTime = m_curTime;	//������ �ð��� ���
	m_FPSframeCount++;		//�ڵ����� ������ ī��Ʈ ����
	m_FPStimeElapsed += m_timeElapsed;	//�ʴ� ������ �ð� ����� ����
	m_worldTime += m_timeElapsed;		//��ü �ð������ ����

	//������ �ʱ�ȭ�� 1�ʸ��� ����
	if (m_FPStimeElapsed > 1.0f)
	{
		m_frameRate = m_FPSframeCount;
		m_FPSframeCount = 0;
		m_FPStimeElapsed = 0.0f;
	}
}

unsigned long CTimer::GetFrameRate(TCHAR* str) const
{
	if (str != nullptr)
	{
		wsprintf(str, L"FPS: %d", m_frameRate);
	}
	return m_frameRate;
}
