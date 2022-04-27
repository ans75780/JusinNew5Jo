#pragma once

#include "Include.h"

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	static CKeyMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CKeyMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	bool		Key_Pressing(int _iKey);
	bool		Key_Down(int _iKey);
	bool		Key_Up(int _iKey);

private:
	static CKeyMgr*		m_pInstance;
	bool		m_bKeyState[VK_MAX];
};

