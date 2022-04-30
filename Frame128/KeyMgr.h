#pragma once
#include "Include.h"
#include "SingletonBase.h"

enum class KEY_STATE
{
	NONE
	, TAP
	, HOLD
	, AWAY
};

enum class KEY_TYPE
{
	LEFT
	, RIGHT
	, UP
	, DOWN

	, Q
	, W
	, E
	, R
	, A
	, S
	, D
	, F
	, Z
	, X
	, C
	, V
	, B
	, ALT
	, LSHIFT
	, SPACE
	, LCTRL
	, ENTER
	, ESC
	, TAB
	, LBUTTON
	, RBUTTON
	, F1
	, F2
	, F3
	, F4
	, F5
	, F6
	, F7
	, F8
	, F9
	, F10
	, F11
	, F12

	, LAST
};

struct tKeyInfo
{
	KEY_STATE   eState;
	bool        bPrevPush;
};

class CKeyMgr : public CSingletonBase<CKeyMgr>
{
	friend CSingletonBase;
private:
	CKeyMgr();
	~CKeyMgr();
private:
	vector<tKeyInfo> m_vecKey;


public:
	void init();
	void update();

public:
	KEY_STATE get_KeyState(KEY_TYPE _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}
};