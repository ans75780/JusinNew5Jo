#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,	// 프로그램 인스턴스 핸들, 프로세스로 부터 읽어들일 정보가 아니라 파일로부터 읽어올 것이기 때문에 NULL
		pFilePath,  // 파일 경로
		IMAGE_BITMAP,  // 어떤 타입을 읽어올 지 결정
		0,	// 가로 사이즈
		0,	// 세로 사이즈
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일에서 이미지를 읽어들이겠다는 옵션 LR_CREATEDIBSECTION : 읽어온 파일을 dib형태로 변환

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
