#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CollisionMgr.h"

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

//����ƽ ���� ������� �ΰ����� �ʱ�ȭ
CScene* CSceneMgr::m_currentScene = nullptr;


HRESULT CSceneMgr::Init()
{
	return S_OK;
}

void CSceneMgr::Release()
{
	//�ݺ��ڸ� ���ؼ� ���� ���鼭 �ϳ��� �����Ѵ�.
	m_miSceneList iter = m_sceneList.begin();
	for (iter; iter != m_sceneList.end();)
	{
		//����
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

	//�� ã������ fail
	if (find == m_sceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������̶� ������ fail
	if (find->second == m_currentScene) return E_FAIL;

	//������� ������ ������ ������ ���� �ʱ�ȭ�ϰ� �������ش�.
	if (SUCCEEDED(find->second->Init()))
	{
		//�������� ������ ������
		if (m_currentScene) m_currentScene->Release();
		m_currentScene = find->second;

		return S_OK;
	}

	return E_NOTIMPL;
}
