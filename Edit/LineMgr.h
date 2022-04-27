#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	bool		Collision_Line(float& fX, float* pY);

private:
	void		Key_Input(void);
	void		Save_Data(void);
	void		Load_Data(void);


public:
	static CLineMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CLineMgr*		m_pInstance;

	POINTPOS				m_tLinePoint[2];
	list<CLine*>			m_LineList;
};

// 라인 에디터에 스크롤 적용하여 지형 만들기
// 1. 플레이어의 이동 방향과 반대 방향으로 스크롤 값이 생성됨
// EX)  m_tInfo.fX += m_speed;
//	    m_scrollX -= m_speed;

// 2. 스크롤 값은 모든 그리기 코드의 적용
// 3. 마우스 스크롤도 같이 처리해야 오류가 발생하지 않음(마우스는 반드시 0, 0 ~ 800,600이라는 양수 범위내에서만 존재함)
