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

	//Ű�� �ѹ��� ���ȳ�?
	bool isOnceKeyDown(int key);
	//Ű�� �ѹ� ������ �����?
	bool isOnceKeyUp(int key);
	//Ű�� ��� �����ֳ�?
	bool isStayKeyDown(int key);
	//���Ű��?(ĸ����, �ѹ���)
	bool isToggleKey(int key);

};

