#include "stdafx.h"
#include "CGun.h"

#include "KeyMgr.h"
#include "ObjMgr.h"

#include "AbstractFactory.h"

#include "CBullet_Pistol.h"


CGun::CGun(): m_fShootInterval(0.f){}
CGun::~CGun() {}
