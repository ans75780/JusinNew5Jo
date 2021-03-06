#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CollisionMgr.h"

CSceneMgr::CSceneMgr() {}

CSceneMgr::~CSceneMgr() { Release(); }

//스태틱 변수 현재씬은 널값으로 초기화
CScene* CSceneMgr::m_currentScene = nullptr;


HRESULT CSceneMgr::Init() { return S_OK; }

void CSceneMgr::Release()
{
	//반복자를 통해서 맵을 돌면서 하나씩 삭제한다.
	m_miSceneList iter = m_sceneList.begin();
	for (iter; iter != m_sceneList.end();)
	{
		//삭제
		if (iter->second != NULL)
		{
			if (iter->second == m_currentScene) 
				iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = m_sceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	m_sceneList.clear();
}

void CSceneMgr::Update()
{
	if (m_currentScene)
	{
		m_currentScene->Update();
	}
}

void CSceneMgr::Late_Update()
{
	if (m_currentScene) m_currentScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if (m_currentScene) m_currentScene->Render(hDC);
}

CScene* CSceneMgr::AddScene(string sceneName, CScene* scene)
{
	if (!scene) return nullptr;

	m_sceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}

HRESULT CSceneMgr::ChangeScene(string sceneName)
{
	m_miSceneList find = m_sceneList.find(sceneName);

	//못 찾았으면 fail
	if (find == m_sceneList.end()) return E_FAIL;

	//바꾸려는 씬이 현재씬이랑 같으면 fail
	if (find->second == m_currentScene) return E_FAIL;

	//여기까지 왔으면 문제가 없으니 씬을 초기화하고 변경해준다.
	if (SUCCEEDED(find->second->Init()))
	{
		//기존씬이 있으면 릴리즈
		if (m_currentScene) m_currentScene->Release();
		m_currentScene = find->second;

		return S_OK;
	}

	return E_NOTIMPL;
}
