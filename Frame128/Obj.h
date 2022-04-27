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
	const VECTOR2& Get_Pos() { return m_vPos; }
	const VECTOR2& Get_Scale() { return m_vScale; }
	const float& Get_Angle() { return m_fAngle; }
	const bool& Get_Active() { return m_bActive; }
	RENDERID Get_RenderID() { return m_eRenderID; }
	CComponent*	Get_Component(const TCHAR* ComponentName);
	void						CreateCollider();
	CCollider*				Get_Collider();
	OBJID						Get_ID() { return m_eID; }

	//Setter
	void				Set_Pos(const VECTOR2& _vector2) { m_vPos = _vector2; }
	void				Set_Scale(const VECTOR2& _vector2) { m_vScale = _vector2; };
	void				Set_Angle(float _f) { m_fAngle = _f; }
	void				Set_Active(bool _isActive) { m_bActive = _isActive; }
	void				Set_PosX(float _x) { m_vPos.x = _x; }
	void				Set_PosY(float _y) { m_vPos.y = _y; }
	void				Add_Pos(VECTOR2 vec) { m_vPos + vec; }
	void				Add_Scale(VECTOR2 vec) { m_vScale + vec; }

	//CollisionFunction
	virtual void    OnCollision(CCollider* _pOther) PURE;//�浹���� ��� ȣ��Ǵ� �Լ�
	virtual void    OnCollisionEnter(CCollider* _pOther) PURE;//�浹 ������ ��� ȣ��Ǵ� �Լ�
	virtual void    OnCollisionExit(CCollider* _pOther) PURE;//�浹�� ������ ȣ��Ǵ� �Լ�
	//TrigerFunction
	virtual void    OnTrigger(CCollider* _pOther) PURE;//�浹���� ��� ȣ��Ǵ� �Լ�
	virtual void    OnTriggerEnter(CCollider* _pOther) PURE;//�浹 ������ ��� ȣ��Ǵ� �Լ�
	virtual void    OnTriggerExit(CCollider* _pOther) PURE;//�浹�� ������ ȣ��Ǵ� �Լ�

protected:
	wstring		m_strName;//������Ʈ ����
	VECTOR2		m_vPos;
	VECTOR2		m_vScale;//������
	float		m_fAngle;//������Ʈ ����
	bool		m_bActive;//������Ʈ Ȱ��ȭ ����
	OBJID		m_eID;//������Ʈ ����Ƽ
	RENDERID	m_eRenderID;//���� ����
	vector<CComponent*> m_vecComponents;//������ ������Ʈ
};

