#pragma once

#include "Obj.h"
#include "SingletonBase.h"

class CObjMgr : public CSingletonBase<CObjMgr>
{
	friend CSingletonBase;
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj* Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj* Get_Target(OBJID eID, CObj* pObj);
	list<CObj*>& Get_ObjList(OBJID _eiD) { return m_ObjList[_eiD]; }
public:
	void	AddObject(OBJID eID, CObj* pObj);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);
	void	Delete_ID(OBJID eID);
public:
	void	LoadFeature(const char* strData);


private:
	list<CObj*>			m_ObjList[OBJ_END];
	list<CObj*>			m_RenderSort[RENDER_END];
};
