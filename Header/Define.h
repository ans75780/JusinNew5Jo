#pragma once
#define WINCX	800
#define WINCY	600	
	   
#define WINCX_HALF (WINCX / 2)
#define WINCY_HALF (WINCY / 2)

#define TILECX	64
#define TILECY	64
	    
#define TILEX	30
#define TILEY	20
	    
#define PURE = 0
	    
#define OBJ_NOEVENT  0
#define OBJ_DEAD     1
	    
#define PI 3.141592f
	    
#define VK_MAX 0xff
	    
#define MIN_STR 64
#define MAX_STR 256

#define DEG_TO_RAD 0.017435	//디그리 1도(라디안값)
#define PI2 (PI * 2)
#define PI_2	(PI / 2)
#define PI_4	(PI / 4)
#define PI_8	(PI / 8)
#define PI_16	(PI / 16)
#define PI_32	(PI / 32)

#define KEY(type, state) KEY_STATE::state == MGR(CKeyMgr)->get_KeyState(KEY_TYPE::type)
#define KEYTAP(type)	KEY(type, TAP)
#define KEYHOLD(type)	KEY(type, HOLD)
#define KEYAWAY(type)	KEY(type, AWAY)
#define KEYNONE(type)	KEY(type, NONE)

typedef D3DXVECTOR3 DXV3;
typedef D3DXMATRIX	DXMAT;

#define DT		MGR(CTimeMgr)->getElasedTime()

#define CreateBullet(type)	MGR(CObjMgr)->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<type>::Create())

extern		HWND	g_hWnd;