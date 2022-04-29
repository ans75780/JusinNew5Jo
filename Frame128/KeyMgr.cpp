#include "stdafx.h"
#include "KeyMgr.h"


int g_arrVK[(int)KEY_TYPE::LAST] =
{
	VK_LEFT
	, VK_RIGHT
	, VK_UP
	, VK_DOWN

	, 'Q'
	, 'W'
	, 'E'
	, 'R'
	, 'A'
	, 'S'
	, 'D'
	, 'F'
	, 'Z'
	, 'X'
	, 'C'
	, 'V'
	, 'B'
	, VK_MENU
	, VK_LSHIFT
	, VK_SPACE
	, VK_LCONTROL
	, VK_RETURN
	, VK_ESCAPE
	, VK_TAB
	, VK_LBUTTON
	, VK_RBUTTON
	, VK_F1
	, VK_F2
	, VK_F3
	, VK_F4
	, VK_F5
	, VK_F6
	, VK_F7
	, VK_F8
	, VK_F9
	, VK_F10
	, VK_F11
	, VK_F12
};






CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}


void CKeyMgr::init()
{
	for (int i(0); i < (int)KEY_TYPE::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// HWND hMainWnd = CMainCore::get_inst()->get_main_hWnd();
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i(0); i < (int)KEY_TYPE::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) // 키가 눌려 있다
			{
				if (m_vecKey[i].bPrevPush) // 전에도 눌렸으면
				{
					m_vecKey[i].eState = KEY_STATE::HOLD; // 홀드인걸로
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP; // 아니면 걍 탭
				}

				m_vecKey[i].bPrevPush = true; // 전에 눌린거 활성화
			}
			else // 키가 안눌려있다
			{
				if (m_vecKey[i].bPrevPush) // 전에는 눌렸다면
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false; // 전에 눌린거 비활성화
			}

		}
	}
	else
	{
		for (int i(0); i < (int)KEY_TYPE::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState ||
				KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
				m_vecKey[i].eState = KEY_STATE::NONE;
		}
	}
}
