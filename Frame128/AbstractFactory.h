#pragma once

#include "Obj.h"
#include "Tile.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create(void)
	{
		CObj*		pObj = new T;
		pObj->Init();

		return pObj;
	}
	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Init();

		VECTOR2 vec(_fX, _fY);
		pObj->Set_Pos(vec);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

public:
	CAbstractFactory()	{	}
	~CAbstractFactory() {	}
};

// 추상 팩토리 패턴 : 생성 패턴의 한 방법으로 인스턴스를 만드는 절차를 추상화하는 개념
// 즉, 객체 생성 시 동반되는 공통적인 작업을 추상화 시킨 것이다.

// 이터레이터 패턴(반복자 패턴) : 내부 표현 방식은 공개하지 않고 순차적인 접근 방법을 제공하는 패턴
// 사용목적 : 공통되는 부모를 갖는 오브젝트들을 하나의 컨테이너로 관리->상속과 다형성 때문에 가능한 것이며, 객체 관리를 위한 디자인 패턴에 속한다.

