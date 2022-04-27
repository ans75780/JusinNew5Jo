#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "Tile.h"

CTileMgr*		CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Init(void)
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float	fX = float((TILECX * j) + (TILECX >> 1));
			float	fY = float((TILECY * i) + (TILECY >> 1));
			CObj*	pObj = CAbstractFactory<CTile>::Create(fX, fY, 0);
			pObj->Set_Scale(VECTOR2(TILECX, TILECY));
			m_vecTile.push_back(pObj);
		}
	}

}

void CTileMgr::Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	int	iIndex = 0;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int	iCullX = abs(iScrollX / TILECX);
	int	iCullY = abs(iScrollY / TILECY);

	int iCullEndX = iCullX + WINCX / TILECX + 2;
	int iCullEndY = iCullY + WINCY / TILECY + 2;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Render(hDC);
			/*
			wsprintf(m_szBuf, L"%d", iIndex);
			TextOut(hDC, m_vecTile[iIndex]->Get_Rect().left + iScrollX, 
				m_vecTile[iIndex]->Get_Rect().top + iScrollY,
				m_szBuf, lstrlen(m_szBuf));
			*/
		}
	}	
}
void CTileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}

bool CTileMgr::Save(const char* strData)
{
	//현재 타일맵 저장은 64*64 타일 30,20장을 기준으로 작성된다.
	FILE		*fp;
	errno_t	err;
	char		saveData[MAX_STR] = "../Data/";
	strcat_s(saveData,sizeof(saveData), strData);
	int		size = 0;
	try
	{
		err = fopen_s(&fp, saveData, "wb");
		if (err == -1)	//open한 파일이 eof이다.(해당 주소에 파일이 없다.)
			throw(err);
		size = (int)(m_vecTile.size());	// original : size = m_vecTile.size();
		err = fwrite(&size, sizeof(size), 1, fp) ? 0 : throw(0);
		for (int i = 0; i < size; i++)
		{
			int ID = dynamic_cast<CTile*>(m_vecTile[i])->Get_DrawID();
			err = fwrite(&ID, sizeof(ID), 1, fp) ? 0 : throw(0);
		}
	}
	catch (int data)
	{
		if (data == -1)
			MessageBox(g_hWnd, L"경로에 올바른 파일이 없습니다.", L"세이브 에러", MB_OK);
		else if(data == 0)
			MessageBox(g_hWnd, L"읽기 에러.", L"세이브 에러", MB_OK);
		fclose(fp);
		return false;
	}
	MessageBox(g_hWnd, L"정상적으로 세이브가 완료되었습니다.", L"성공", MB_OK);
	fclose(fp);
	return true;
}

bool CTileMgr::Load(const char* strData)
{
	//현재 타일맵 저장은 64*64 타일 30,20장을 기준으로 작성된다.
	FILE* fp;
	errno_t	err;
	char		loadData[MAX_STR] = "../Data/";
	strcat_s(loadData, sizeof(loadData), strData);
	int		size = 0;
	try
	{
		err = fopen_s(&fp, loadData, "rb");
		if (err == -1)//open한 파일이 eof이다.(해당 주소에 파일이 없다.)
			throw(err);
		err = fread(&size, sizeof(size), 1, fp) ? 0 : throw(0);
		for (int i = 0; i < size; i++)
		{
			int ID = 0;
			err = fread(&ID, sizeof(ID), 1, fp) ? 0 : throw(0);
			dynamic_cast<CTile*>(m_vecTile[i])->Set_DrawID(ID);
		}
	}
	catch (int data)
	{
		if (data == -1)
			MessageBox(g_hWnd, L"경로에 올바른 파일이 없습니다.", L"로드 에러", MB_OK);
		else if (data == 0)
			MessageBox(g_hWnd, L"불러오기 에러.", L"로드 에러", MB_OK);
		fclose(fp);
		return false;
	}
	MessageBox(g_hWnd, L"정상적으로 로드가 완료되었습니다.", L"로드 성공", MB_OK);
	fclose(fp);
	return true;
}

void CTileMgr::Picking_Tile(POINT pt, const int& iDrawID, const int& iOption)
{
	int	iWidthX = pt.x / TILECX;
	int	iHeightY = pt.y / TILECY;

	int	iIndex = iHeightY * TILEX + iWidthX;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);

}
