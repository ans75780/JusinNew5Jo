#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void	AddObject(OBJID eID, CObj* pObj);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);

private:
	list<CObj*>			m_ObjList[OBJ_END];

public:
	static CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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

private:
	static CObjMgr*		m_pInstance;
};

