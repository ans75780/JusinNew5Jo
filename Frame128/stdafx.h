// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <ctime>
#include <bitset>
#include <d3d9.h>
#include <assert.h>

#include <io.h>
#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex64_vc.lib")

#include <d3d9.h>
#include <d3dx9.h>

#define MGR(manger) manger::GetSingleton()
#define SAFE_DELETE(p){if(p){delete p; p = nullptr;}}

#define DEVICE CDevice::GetSingleton()
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


#define SAFE_DELETE_ARRAY(p){delete[] p; p = nullptr;}