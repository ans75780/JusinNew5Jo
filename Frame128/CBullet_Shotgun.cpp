#include "stdafx.h"
#include "CBullet_Shotgun.h"

CBullet_Shotgun::CBullet_Shotgun()
{
}

CBullet_Shotgun::~CBullet_Shotgun()
{
}

void CBullet_Shotgun::Init()
{
}

int CBullet_Shotgun::Update()
{
	m_vPos = { 0.f, 0.f, 0.f };
	return OBJ_NOEVENT;
}

void CBullet_Shotgun::Render(HDC hDC)
{
}

void CBullet_Shotgun::Release()
{
}

void CBullet_Shotgun::OnCollision(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnCollisionEnter(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnCollisionExit(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTrigger(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTriggerEnter(CCollider * _pOther)
{
}

void CBullet_Shotgun::OnTriggerExit(CCollider * _pOther)
{
}
