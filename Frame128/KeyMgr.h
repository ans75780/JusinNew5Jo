#pragma once
#include "../Header/Include.h"
#include "SingletonBase.h"
using namespace std;

#define KEYMAX 256

class CKeyMgr : public CSingletonBase<CKeyMgr>
{
	friend	CSingletonBase;
private:
	bitset<KEYMAX> m_keyUp;
	bitset<KEYMAX> m_keyDown;
private:
	CKeyMgr();
	~CKeyMgr();
public:
	HRESULT Init();
	void release();

	//키가 한번만 눌렸냐?
	bool isOnceKeyDown(int key);
	//키가 한번 눌렀다 띄었냐?
	bool isOnceKeyUp(int key);
	//키가 계속 눌려있냐?
	bool isStayKeyDown(int key);
	//토글키냐?(캡스락, 넘버락)
	bool isToggleKey(int key);

};

