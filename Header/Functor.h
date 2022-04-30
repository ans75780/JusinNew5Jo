#pragma once
//���� �ʿ��� �Լ� �߰��س���.
template<typename T>
bool		CompareY(T Dest, T Sour)
{
	return Dest->Get_Pos().y < Sour->Get_Pos().y;
}
template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}
class CTagFinder
{
private:
	const TCHAR*		m_pStrKey;

public:
	CTagFinder(const TCHAR* pStrKey)
		: m_pStrKey(pStrKey)
	{

	}

public:
	template<typename T>
	bool		operator()(T& Pair)
	{
		return !lstrcmp(m_pStrKey, Pair.first);
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

class CDeleteObj
{
public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}
//���׸���
inline void DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width, y + height };
	return rc;
}

//RECT �����(���ͺ���)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2, y + height / 2 };
	return rc;
}

//�簢�� �׸���
inline void RectDraw(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//���׸���
inline void EllipseDraw(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//���׸���(���ͺ���)
inline void EllipseDrawCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//���׸���(���ͺ���)
inline void RectDrawCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}
