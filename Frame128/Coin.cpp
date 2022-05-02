#include "stdafx.h"
#include "Coin.h"
#include "UserDefineHeaders.h"
#include "TextureMgr.h"
#include "RandomMgr.h"
CCoin::CCoin()
{
	m_vPos = { 0.f, 0.f, 0.f };
	m_vDir = { 0.f, -1.f, 0.f };
	m_vScale = { 50.f, 50.f, 0.f };
	m_vPoint[LT] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[RT] = {  m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[RB] = {  m_vScale.x * 0.5f,  m_vScale.y * 0.5f, 0.f };
	m_vPoint[LB] = { -m_vScale.x * 0.5f,  m_vScale.y * 0.5f, 0.f };
	m_strName = L"Coin";
	m_bActive = true;
	m_eID = OBJID::OBJ_ITEM;
	m_eRenderID = RENDERID::RENDER_OBJ;

	int i = int(MGR(CRandomMgr)->getFromFloatTo(1, 2));
	m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Item", L"Coin", i);

	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	CreateCollider();
	m_bUpdated = false;
}

CCoin::~CCoin()
{
}

void CCoin::Init(void)
{
}

int CCoin::Update(void)
{
	if (false == m_bActive)
		return OBJ_DEAD;

	m_bUpdated = true;
	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = m_matScale * m_matTrans;
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}

	m_pTarget = MGR(CObjMgr)->Get_Player();

	AddMagnetic();

	return OBJ_NOEVENT;
}

void CCoin::Render(HDC hDC)
{
	if (!m_bUpdated)
		return;
	MGR(CDevice)->Get_Sprite()->SetTransform(&m_matWorld);
	MGR(CDevice)->Get_Sprite()->Draw(m_pTexInfo->pTexture, // 텍스처 객체
		nullptr,	// 출력할 이미지 영역에 대한 렉트 구조체 포인터, null인 경우 이미지의 0, 0기준으로 출력
		&D3DXVECTOR3(float(m_pTexInfo->tImgInfo.Width / 2), float(m_pTexInfo->tImgInfo.Height / 2), 0.f),	// 출력할 이미지의 중심 축에 대한 vec3 구조체 포인터, null인 경우 0, 0이 중심 좌표
		nullptr,	// 위치 좌표에 대한 vec3 구조체 포인터, null인 경우 스크린 상 0,0,에 좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255));
	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}

void CCoin::Release(void)
{
}

void CCoin::OnCollision(CCollider* _pOther)
{
}

void CCoin::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->Get_Owner()->Get_ID() == OBJID::OBJ_PLAYER)
	{
		m_bActive = false;
	}

}

void CCoin::OnCollisionExit(CCollider* _pOther)
{
}

void CCoin::OnTrigger(CCollider* _pOther)
{
}

void CCoin::OnTriggerEnter(CCollider* _pOther)
{
}

void CCoin::OnTriggerExit(CCollider* _pOther)
{
}
