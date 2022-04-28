#include "stdafx.h"
#include "Bullet.h"

#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Collider.h"

typedef D3DXVECTOR3 DXV3;
typedef D3DXMATRIX	DXMAT;

CBullet::CBullet()
	: m_pPlayer(nullptr)
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&vLocalPos, sizeof(DXV3));
	ZeroMemory(&vLocalScale, sizeof(DXV3));
	ZeroMemory(&vLocalDir, sizeof(DXV3));
	ZeroMemory(&vLocalLT, sizeof(DXV3));
	ZeroMemory(&vLocalRT, sizeof(DXV3));
	ZeroMemory(&vLocalRB, sizeof(DXV3));
	ZeroMemory(&vLocalLB, sizeof(DXV3));
}

CBullet::~CBullet() { Release(); }

void CBullet::Init(void)
{
	vLocalPos = { 0.f, 0.f, 0.f};
	vLocalScale = { 10.f, 10.f, 0.f };
	m_vScale = { 10.f, 10.f, 0.f};
	vLocalDir = { 0.f, -1.f, 0.f };

	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Bullet";

	m_fSpeed = 300.f;

	vLocalLT = { -vLocalScale.x, -vLocalScale.y, 0.f };
	vLocalRT = { vLocalScale.x, -vLocalScale.y, 0.f };
	vLocalRB = { vLocalScale.x, vLocalScale.y, 0.f };
	vLocalLB = { -vLocalScale.x, vLocalScale.y, 0.f };

	CreateCollider();
	int a = 10;
}

int CBullet::Update(void)
{
	m_fLifeTime -= DT;
	if (m_fLifeTime <= 0 || m_bActive == false)
	{
		return OBJ_DEAD; // 삭제 명령
	}

	D3DXMATRIX 	matScale, matTrans;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matTrans);

	// 플레이어 방향에따라 방향 바꿔주기 --> Player Angle에서 가져오기
	// 방향이 정해지면 그 방향으로 날라가기
	vLocalPos.x += sinf(m_fRadian) * m_fSpeed * DT;
	vLocalPos.y -= cosf(m_fRadian) * m_fSpeed * DT;

	DXMAT temp;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	// 플레이어 좌표에다가 중점 설정해주기
	D3DXMatrixTranslation(&temp, vLocalPos.x, vLocalPos.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, 0.f);
	m_matWorld = matScale * temp  * matTrans;

	// D3DXVec3TransformCoord(&vWorldPos, &vLocalPos, &m_matWorld);
	D3DXVec3TransformCoord(&vWorldLT, &vLocalLT, &m_matWorld);
	D3DXVec3TransformCoord(&vWorldRT, &vLocalRT, &m_matWorld);
	D3DXVec3TransformCoord(&vWorldRB, &vLocalRB, &m_matWorld);
	D3DXVec3TransformCoord(&vWorldLB, &vLocalLB, &m_matWorld);


	return OBJ_NOEVENT;
}

void CBullet::Render(HDC hDC)
{
	MoveToEx(hDC, int(vWorldLT.x), int(vWorldLT.y), nullptr);
	LineTo(hDC, int(vWorldRT.x), int(vWorldRT.y));
	LineTo(hDC, int(vWorldRB.x), int(vWorldRB.y));
	LineTo(hDC, int(vWorldLB.x), int(vWorldLB.y));
	LineTo(hDC, int(vWorldLT.x), int(vWorldLT.y));

	for (auto& iter : m_vecComponents)
	{
		iter->Render(hDC);
	}
}

void CBullet::Release(void)
{
	for_each(m_vecComponents.begin(), m_vecComponents.end(),
		Safe_Delete<CComponent*>);
	m_vecComponents.clear();
}


void CBullet::OnCollision(CCollider * _pOther)
{
}

void CBullet::OnCollisionEnter(CCollider * _pOther)
{
	if (OBJID::OBJ_FEATURE == _pOther->Get_Owner()->Get_ID())
	{
		// 삭제
		m_bActive = false;
	}
}

void CBullet::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet::OnTrigger(CCollider * _pOther)
{
}

void CBullet::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet::OnTriggerExit(CCollider * _pOther)
{
}