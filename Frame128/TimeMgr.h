#pragma once
#include "SingletonBase.h"
#include "Timer.h"

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
	//�� �����Ӵ� ����ð� �������� 1/60
	float getElasedTime() const { return m_pTimer->GetElapsedTime(); }
	//��ü �ð� ����� ��������
	float getWorldTime() const { return m_pTimer->GetWorldTime(); }
};

