#include "stdafx.h"
#include "Bullet.h"

#include "TimeMgr.h"

typedef D3DXVECTOR3 DXV3;
typedef D3DXMATRIX	DXMAT;

CBullet::CBullet()
{
	D3DXMatrixIdentity(&m_matWorld);
}

CBullet::~CBullet() { Release(); }

void CBullet::Init(void)
{
	vLocalPos = { 0.f, 0.f, 0.f };
	vLocalScale = { 10.f, 10.f, 0.f };
	vLocalDir = { 0.f, -1.f, 0.f };

	m_eID = OBJID::OBJ_BULLET;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Bullet";

	vLocalLT = { -vLocalScale.x, -vLocalScale.y, 0.f };
	vLocalRT = { vLocalScale.x, -vLocalScale.y, 0.f };
	vLocalRB = { vLocalScale.x, vLocalScale.y, 0.f };
	vLocalLB = { -vLocalScale.x, vLocalScale.y, 0.f };

	CreateCollider();
}

int CBullet::Update(void)
{
	D3DXMATRIX 	matScale, matTrans;
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matTrans);
	


	// 플레이어 방향에따라 방향 바꿔주기 --> Player Angle에서 가져오기
	// 방향이 정해지면 그 방향으로 날라가기
	vLocalPos.x += cosf(m_fAngle) * m_fSpeed * DT;
	vLocalPos.y -= sinf(m_fAngle) * m_fSpeed * DT;


	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	// 플레이어 좌표에다가 중점 설정해주기
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, 0.f);
	m_matWorld = matScale * matTrans;

	D3DXVec3TransformCoord(&vWorldPos, &vLocalPos, &m_matWorld);
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
}

void CBullet::Release(void)
{
}


void CBullet::OnCollision(CCollider * _pOther)
{
}

void CBullet::OnCollisionEnter(CCollider * _pOther)
{
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