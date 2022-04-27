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

		DXV3 vec(_fX, _fY, 0.f);
		pObj->Set_Pos(vec);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj*	Create2();	//DX��ǥ �� �� �߰��� Create�Լ�

public:
	CAbstractFactory()	{	}
	~CAbstractFactory() {	}
};

// �߻� ���丮 ���� : ���� ������ �� ������� �ν��Ͻ��� ����� ������ �߻�ȭ�ϴ� ����
// ��, ��ü ���� �� ���ݵǴ� �������� �۾��� �߻�ȭ ��Ų ���̴�.

// ���ͷ����� ����(�ݺ��� ����) : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ����
// ������ : ����Ǵ� �θ� ���� ������Ʈ���� �ϳ��� �����̳ʷ� ����->��Ӱ� ������ ������ ������ ���̸�, ��ü ������ ���� ������ ���Ͽ� ���Ѵ�.

