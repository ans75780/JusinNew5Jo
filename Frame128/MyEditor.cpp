#include "stdafx.h"
#include "MyEditor.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "BmpMgr.h"
CMyEditor::CMyEditor()
{
}

CMyEditor::~CMyEditor()
{
	Release();
}

void CMyEditor::Key_Input(void)
{
	/*if (MGR(CKeyMgr)->isOnceKeyDown('Q'))
	{
		CTileMgr::GetSingleton()->Save("Stage1.dat");
	}
	if (MGR(CKeyMgr)->isOnceKeyDown('E'))
	{
		CTileMgr::GetSingleton()->Load("Stage1.dat");
	}

	if (MGR(CKeyMgr)->isStayKeyDown('A'))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);
	}

	if (MGR(CKeyMgr)->isStayKeyDown('D'))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);
	}

	if (MGR(CKeyMgr)->isStayKeyDown('W'))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);
	}

	if (MGR(CKeyMgr)->isStayKeyDown('S'))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);
	}

	if (MGR(CKeyMgr)->isOnceKeyDown(VK_LBUTTON))
	{
		POINT	Pt;
		GetCursorPos(&Pt);
		ScreenToClient(g_hWnd, &Pt);

		Pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		Pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::GetSingleton()->Picking_Tile(Pt, 1, 0);
	}*/

}

HRESULT CMyEditor::Init(void)
{
	CTileMgr::GetSingleton()->Init();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage1/Stage1.bmp", L"Stage1");
	

	return S_OK;
}

void CMyEditor::Update(void)
{
	Key_Input();
	CScrollMgr::Get_Instance()->Scroll_Lock();
	CTileMgr::GetSingleton()->Update();
}

void CMyEditor::Late_Update(void)
{
	CTileMgr::GetSingleton()->Late_Update();
}

void CMyEditor::Render(HDC hDC)
{

	HDC img = CBmpMgr::Get_Instance()->Find_Image(L"Stage1");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	BitBlt(hDC,
		iScrollX,
		iScrollY,
		TILECX * TILEX,
		TILECY * TILEY,
		img,
		0,
		0,
		SRCCOPY);
	
	CTileMgr::GetSingleton()->Render(hDC);

}

void CMyEditor::Release(void)
{
	CTileMgr::GetSingleton()->ReleaseSingleton();
}
