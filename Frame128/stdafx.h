// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <ctime>
#include <bitset>
#include <d3d9.h>

#include <io.h>
#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex64_vc.lib")

#include <d3d9.h>
#include <d3dx9.h>

#define	KEYMANAGER			CKeyMgr::GetSingleton()
#define	SCENEMANAGER		CSceneMgr::GetSingleton()
#define	OBJMANAGER			CObjMgr::GetSingleton()
#define COLLISIONMANAGER	CCollisionMgr::GetSingleton()
#define TIMEMANAGER			CTimeMgr::GetSingleton()
#define SOUNDMANAGER		CSoundMgr::GetSingleton()

#define SAFE_DELETE(p){if(p){delete p; p = nullptr;}}

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif

#endif // _DEBUG

using namespace std;