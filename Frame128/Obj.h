#pragma once
#include "Component.h"

class CCollider;

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Init(void) PURE;
	virtual int  Update(void) PURE;
	virtual void Late_Update(void) final;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;
public:
	//Getter
	const DXV3& Get_Pos() { return m_vPos; }
	const DXV3& Get_Scale() { return m_vScale; }
	const float& Get_Angle() { return m_fRadian; }
	const bool& Get_Active() { return m_bActive; }
	RENDERID Get_RenderID() { return m_eRenderID; }
	CComponent*	Get_Component(const TCHAR* ComponentName);
	void						CreateCollider();
	CCollider*				Get_Collider();
	OBJID						Get_ID() { return m_eID; }
	const DXMAT	GetWorld() { return m_matLocal; }//월드 매트릭스 이 월드 매트릭스는 자신의 월드로서, 자식 오브젝트는 이 부모의 월드에 영향을 받는다.


	//Setter
	void				Set_Pos(const DXV3& _DXV3) { m_vPos = _DXV3; }
	void				Set_Scale(const DXV3& _DXV3) { m_vScale = _DXV3; };
	void				Set_Angle(float _f) { m_fRadian = _f; }
	void				Set_Active(bool _isActive) { m_bActive = _isActive; }
	void				Set_PosX(float _x) { m_vPos.x = _x; }
	void				Set_PosY(float _y) { m_vPos.y = _y; }
	void				Add_Pos(DXV3 vec) { m_vPos += vec; }
	void				Add_Scale(DXV3 vec) { m_vScale + vec; }
	//CollisionFunction
	virtual void    OnCollision(CCollider* _pOther) PURE;//충돌중인 경우 호출되는 함수
	virtual void    OnCollisionEnter(CCollider* _pOther) PURE;//충돌 진입한 경우 호출되는 함수
	virtual void    OnCollisionExit(CCollider* _pOther) PURE;//충돌이 끝나면 호출되는 함수
	//TrigerFunction
	virtual void    OnTrigger(CCollider* _pOther) PURE;//충돌중인 경우 호출되는 함수
	virtual void    OnTriggerEnter(CCollider* _pOther) PURE;//충돌 진입한 경우 호출되는 함수
	virtual void    OnTriggerExit(CCollider* _pOther) PURE;//충돌이 끝나면 호출되는 함수

protected:
	wstring		m_strName;//오브젝트 네임
	DXV3		m_vPos;
	DXV3		m_vScale;//사이즈
	float		m_fRadian;//오브젝트 각도
	bool		m_bActive;//오브젝트 활성화 상태
	OBJID		m_eID;//오브젝트 아이티
	RENDERID	m_eRenderID;//렌더 순서
	vector<CComponent*> m_vecComponents;//보유한 컴포넌트
	DXMAT		m_matLocal;
};

