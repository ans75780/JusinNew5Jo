#pragma once
#include "SingletonBase.h"

//���ӳ�� ���漱��
class CScene;

class CSceneMgr : public CSingletonBase<CSceneMgr>
{
	friend	CSingletonBase;
private:
	typedef map<string, CScene*> m_mSceneList;
	typedef map<string, CScene*>::iterator m_miSceneList;

	static CScene* m_currentScene;		//�����
	m_mSceneList m_sceneList;				//�� ���

private:
	CSceneMgr();
	~CSceneMgr();
public:
	HRESULT Init();
	void	Release();
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);

	//���߰�
	CScene* AddScene(string sceneName, CScene* scene);
	//�� ����
	HRESULT ChangeScene(string sceneName);

};

