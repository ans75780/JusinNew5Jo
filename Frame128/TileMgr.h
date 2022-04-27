#pragma once

#include "Tile.h"
#include "Include.h"
#include "SingletonBase.h"


class CTileMgr : public CSingletonBase<CTileMgr>
{
	friend	 CSingletonBase;
private:
	CTileMgr();
	~CTileMgr();
public:
	void		Init(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
	bool		Save(const char* strData);
	bool		Load(const char* strData);
	void		Picking_Tile(POINT pt, const int& iDrawID, const int& iOption);
private:
	static CTileMgr*		m_pInstance;
	vector<CObj*>			m_vecTile;
	int							m_iIndex = 0;
	TCHAR					m_szBuf[MIN_STR];
};


