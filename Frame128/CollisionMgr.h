#pragma once

#include "SingletonBase.h"
#include "Obj.h"
#include "Collider.h"
class CCollider;

union COLLIDER_ID
{
	struct {
		UINT	Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr : public CSingletonBase<CCollisionMgr>
{
	friend	CSingletonBase;
private:
	CCollisionMgr();
	~CCollisionMgr();
private:
	map<ULONGLONG, bool>	m_mapColInfo;//�浹ü���� ���� ������ �浹 ����

public:
	void	CollisionUpdate(list<CObj*>& Dest, list<CObj*>& Sour);
	bool	IsCollision(float* _outW, float* _outH, CCollider* DestCollider, CCollider* SourCollider);
	bool	IsOBBCollision(CCollider* DestCollider, CCollider* SourCollider);
	void	ClearColInfo();

};

