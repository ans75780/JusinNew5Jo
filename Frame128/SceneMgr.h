#pragma once
#include "SingletonBase.h"

//게임노드 전방선언
class CScene;

class CSceneMgr : public CSingletonBase<CSceneMgr>
{
	friend	CSingletonBase;
private:
	typedef map<string, CScene*> m_mSceneList;
	typedef map<string, CScene*>::iterator m_miSceneList;

	static CScene* m_currentScene;		//현재씬
	m_mSceneList m_sceneList;				//씬 목록

private:
	CSceneMgr();
	~CSceneMgr();
public:
	HRESULT Init();
	void	Release();
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);

	//씬추가
	CScene* AddScene(string sceneName, CScene* scene);
	//씬 변경
	HRESULT ChangeScene(string sceneName);

};

