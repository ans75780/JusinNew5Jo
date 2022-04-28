#include "stdafx.h"
#include "Bullet.h"

#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Collider.h"

CBullet::CBullet()
	: m_pPlayer(nullptr), m_fLifeTime(0.f)
{}

CBullet::~CBullet() {}