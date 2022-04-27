#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

HRESULT CKeyMgr::Init()
{
	//키값을 전부 눌려있지 않는 상태로 초기화 한다.
	for (int i = 0; i < KEYMAX; i++)
	{
		m_keyUp.set(i, false);
		m_keyDown.set(i, false);
	}

	return S_OK;
}

void CKeyMgr::release()
{
}

bool CKeyMgr::isOnceKeyDown(int key)
{
	//0x8000 : 이전에 누른적이 없고, 호출 시점에서는 눌려있는상태
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!m_keyDown[key])
		{
			m_keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		m_keyDown.set(key, false);
	}
	return false;
}

bool CKeyMgr::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		m_keyUp.set(key, true);
	}
	else
	{
		if (m_keyUp[key])
		{
			m_keyUp.set(key, false);
			return true;
		}
	}
	return false;
}

bool CKeyMgr::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool CKeyMgr::isToggleKey(int key)
{
	//0x0001 : 이전에 누른 적이 있고, 눌려있지 않는 상태
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
