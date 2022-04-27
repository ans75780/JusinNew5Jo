#pragma once

#include "Include.h"

class CLine
{
public:
	CLine();
	CLine(POINTPOS& tLeft, POINTPOS& tRight);
	CLine(LINEINFO& tLine);
	~CLine();

public:
	const LINEINFO& Get_Info(void) const { return m_tInfo; }

public:
	void		Update(void);
	void		Render(HDC hDC);


private:
	LINEINFO		m_tInfo;
};

