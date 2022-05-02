#include "stdafx.h"
#include "Bullet.h"

#include "Device.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "TextureMgr.h"


CBullet::CBullet()
	: m_fLifeTime(0.f), m_iSpreadRate(0),
	m_fSpreadX(0.f), m_fSpreadY(0.f),
	m_fAtk(0.f), m_fReduceRate(0.f), m_fBulletSizeRate(0.f),
	m_pTarget(nullptr)
{
	D3DXMatrixIdentity(&m_matPos);
	ZeroMemory(&m_vWorldPos, sizeof(DXV3));
	ZeroMemory(&m_vLocalPos, sizeof(DXV3));

	m_fRadian = MGR(CObjMgr)->Get_Player()->Get_Radian();
	m_bNowAppear = true;
	m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Bullet");
	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);
}

CBullet::~CBullet() {}

int CBullet::Update()
{
	m_bNowAppear = false;
	float tempDT = DT;
	m_fLifeTime += DT;
	if (m_fLifeTime >= 3)
		return OBJ_DEAD;

	if (false == m_bActive)
		return OBJ_DEAD;

	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width,m_vScale.y / m_pTexInfo->tImgInfo.Height, 1.f);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = m_matScale  * m_matTrans;

	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);

	m_vPos += m_vWorldDir * m_fSpeed * DT;

	return OBJ_NOEVENT;
}

void CBullet::Render(HDC hDC)
{
	if (m_bNowAppear)
		return;
	//DEVICE->Draw_Line(m_vWorldPoint, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
	MGR(CDevice)->Get_Sprite()->SetTransform(&m_matWorld);
	MGR(CDevice)->Get_Sprite()->Draw(m_pTexInfo->pTexture, // 텍스처 객체
		nullptr,	// 출력할 이미지 영역에 대한 렉트 구조체 포인터, null인 경우 이미지의 0, 0기준으로 출력
		&D3DXVECTOR3(float(m_pTexInfo->tImgInfo.Width / 2), float(m_pTexInfo->tImgInfo.Height / 2), 0.f),	// 출력할 이미지의 중심 축에 대한 vec3 구조체 포인터, null인 경우 0, 0이 중심 좌표
		nullptr,	// 위치 좌표에 대한 vec3 구조체 포인터, null인 경우 스크린 상 0,0,에 좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255));
	for (auto& iter : m_vecComponents)
		iter->Render(hDC);
}

void CBullet::Release()
{
	for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
	m_vecComponents.clear();
	m_strName.clear();
}

void CBullet::FindTarget()
{
	m_pTarget = MGR(CObjMgr)->Get_Player();
}

void CBullet::SetRadianToPlayer()
{
	//플레이어에서 자신의 위치를 빼서 방향벡터를 만들고, 정규화시켜줌
	D3DXVECTOR3 dirVec = m_pTarget->Get_Pos() - m_vPos;
	D3DXVec3Normalize(&dirVec, &dirVec);//정규화된 벡터나옴.
	//룩 벡터랑(가로) 정규화된 방향 벡터랑 내적한 값(코사인)을 아크코사인에 넣어 라디안값으로변경
	m_fRadian = acosf(D3DXVec3Dot(&m_vDir, &dirVec));
	if (m_vPos.y > m_pTarget->Get_Pos().y)
	{
		m_fRadian = PI2 - m_fRadian;
	}
}

float CBullet::create_x_spread()
{
	float tempx = float(rand() % m_iSpreadRate) / 100.f;
	int tempx2 = ((rand() % 2) == 0) ? 1 : -1;
	float x_final = float(tempx) * tempx2;

	return x_final;
}

float CBullet::create_y_spread()
{
	float tempy = float(rand() % m_iSpreadRate) / 100.f;
	int tempy2 = ((rand() % 2) == 0) ? 1 : -1;
	float y_final = float(tempy) * tempy2;

	return y_final;
}

void CBullet::set_bullet_dir(DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIRECTION::UP:
		m_vDir = { m_fSpreadX, -1.f, 0.f };
		break;
	case DIRECTION::DOWN:
		m_vDir = { m_fSpreadX, 1.f, 0.f };
		break;
	case DIRECTION::LEFT:
		m_vDir = { -1.f, m_fSpreadY, 0.f };
		break;
	case DIRECTION::RIGHT:
		m_vDir = { 1.f, m_fSpreadY, 0.f };
		break;
	case DIRECTION::UPLEFT:
		m_vDir = { -1.f + m_fSpreadX, -1.f + m_fSpreadY, 0.f };
		break;
	case DIRECTION::UPRIGHT:
		m_vDir = { 1.f + m_fSpreadX, -1.f + m_fSpreadY, 0.f };
		break;
	case DIRECTION::DOWNLEFT:
		m_vDir = { -1.f + m_fSpreadX, 1.f + m_fSpreadY, 0.f };
		break;
	case DIRECTION::DOWNRIGHT:
		m_vDir = { 1.f + m_fSpreadX, 1.f + m_fSpreadY, 0.f };
		break;
	}

	D3DXVec3Normalize(&m_vDir, &m_vDir);
}
