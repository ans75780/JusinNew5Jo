#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
	ZeroMemory(m_tLinePoint, sizeof(POINTPOS));
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	/*POINTPOS tPoint[4] = { 
		{ 150.f, 450.f}, 
		{ 300.f, 450.f }, 
		{ 500.f, 250.f }, 
		{ 650.f, 250.f }};

	m_LineList.push_back(new CLine(tPoint[0], tPoint[1]));
	m_LineList.push_back(new CLine(tPoint[1], tPoint[2]));
	m_LineList.push_back(new CLine(tPoint[2], tPoint[3]));*/
}

int CLineMgr::Update(void)
{
	

	for (auto& iter : m_LineList)
		iter->Update();

	Key_Input();
	

	return 0;
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float& fX, float* pY)
{
	if (m_LineList.empty())
		return false;
	
	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_Info().tLeftPoint.fX &&
			fX <= iter->Get_Info().tRightPoint.fX)
		{
			pTargetLine = iter;
		}
	}

	if (!pTargetLine)
		return false;

	// 두 점을 지나는 직선의 방정식
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y  = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float fX1 = pTargetLine->Get_Info().tLeftPoint.fX;
	float fX2 = pTargetLine->Get_Info().tRightPoint.fX;
	float fY1 = pTargetLine->Get_Info().tLeftPoint.fY;
	float fY2 = pTargetLine->Get_Info().tRightPoint.fY;

	*pY = ((fY2 - fY1) / (fX2 - fX1)) * (fX - fX1) + fY1;

	return true;
}

void CLineMgr::Key_Input(void)
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();


	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		// 맨 처음 시작에
		if ((!m_tLinePoint[0].fX) && (!m_tLinePoint[0].fY))
		{
			// 0 번은 left 점
			m_tLinePoint[0].fX = (float)Pt.x;
			m_tLinePoint[0].fY = (float)Pt.y;
		}

		else
		{
			// 1 번은 right 점
			m_tLinePoint[1].fX = (float)Pt.x;
			m_tLinePoint[1].fY = (float)Pt.y;

			LINEINFO	 tInfo = { m_tLinePoint[0], m_tLinePoint[1] };
			m_LineList.push_back(new CLine(tInfo));

			m_tLinePoint[0].fX = m_tLinePoint[1].fX;
			m_tLinePoint[0].fY = m_tLinePoint[1].fY;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F5))
		Save_Data();


	if (CKeyMgr::Get_Instance()->Key_Down(VK_F6))
		Load_Data();
}


void CLineMgr::Save_Data(void)
{
	// 파일 개방 함수
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// 파일의 경로와 이름을 명시
		GENERIC_WRITE,		// 파일 접근 모드 (출력 : WRITE, 입력 : READ)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용하는가에 대한 설정, NULL 지정 시 공유안함
		NULL,				// 보안 속성 모드, NULL인 경우 기본값 설정
		CREATE_ALWAYS,		// 파일이 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING - 파일이 있는 경우에만 로드
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 파일 등등을 설정), 아무런 속성이 없는 파일 모드 생성
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓸것이기 때문에 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		// 1. 핸들
		// 2. 팝업 창에 프레임에 띄우고자 하는 메시지(유니코드)
		// 3. 팝업 창에 띄우고자 하는 실제 메시지
		// 4. 버튼 설정, MB_OK 는 확인만 , MB_OKCANCEL 확인, 취소 버튼

		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINEINFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 성공"), _T("성공"), MB_OK);
}

void CLineMgr::Load_Data(void)
{
	// 파일 개방 함수
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// 파일의 경로와 이름을 명시
		GENERIC_READ,		// 파일 접근 모드 (출력 : WRITE, 입력 : READ)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용하는가에 대한 설정, NULL 지정 시 공유안함
		NULL,				// 보안 속성 모드, NULL인 경우 기본값 설정
		OPEN_EXISTING,		// 파일이 없으면 생성, 있으면 덮어 쓰기, OPEN_EXISTING - 파일이 있는 경우에만 로드
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김 파일 등등을 설정), 아무런 속성이 없는 파일 모드 생성
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일, 우린 안 쓸것이기 때문에 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		// 1. 핸들
		// 2. 팝업 창에 프레임에 띄우고자 하는 메시지(유니코드)
		// 3. 팝업 창에 띄우고자 하는 실제 메시지
		// 4. 버튼 설정, MB_OK 는 확인만 , MB_OKCANCEL 확인, 취소 버튼

		return;
	}

	DWORD			dwByte = 0;
	LINEINFO		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}
		
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 성공"), _T("성공"), MB_OK);
}
