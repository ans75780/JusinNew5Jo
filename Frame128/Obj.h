#pragma once
#include "Component.h"

class CCollider;

#define LT 0
#define RT 1
#define RB 2
#define LB 3

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
	const wstring& Get_Name() { return m_strName; }
	const DXV3& Get_Pos() { return m_vPos; }
	const DXV3& Get_Scale() { return m_vScale; }
	const DXV3& Get_Dir() { return m_vDir; }
	DXV3* Get_Wheels() { return m_vWorldPoint; }
	const DXV3& Get_MoveSize() { return m_vMoveSize; }
	const float& Get_Angle() { return D3DXToDegree(m_fRadian); }
	const float& Get_Radian() { return m_fRadian; }
	const bool& Get_Active() { return m_bActive; }
	RENDERID Get_RenderID() { return m_eRenderID; }
	CComponent*	Get_Component(const TCHAR* ComponentName);
	void						CreateCollider();
	CCollider*				Get_Collider();
	OBJID						Get_ID() { return m_eID; }
	const DXMAT	GetWorld() { return m_matWorld; }//���� ��Ʈ���� �� ���� ��Ʈ������ �ڽ��� ����μ�, �ڽ� ������Ʈ�� �� �θ��� ���忡 ������ �޴´�.


	//Setter
	void Set_Pos(const DXV3& _DXV3) { m_vPos = _DXV3; }
	void Set_Scale(const DXV3& _DXV3) { m_vScale = _DXV3; };
	void Set_Angle(float _f) { m_fRadian = D3DXToRadian(_f); }
	void Set_Radian(float _f) { m_fRadian = _f; }
	virtual void Set_Active(bool _isActive) { m_bActive = _isActive; }
	void Set_PosX(float _x) { m_vPos.x = _x; }
	void Set_PosY(float _y) { m_vPos.y = _y; }
	void Add_Pos(DXV3 vec) { m_vPos += vec; }
	void Add_Scale(DXV3 vec) { m_vScale + vec; }
	//CollisionFunction
	virtual void    OnCollision(CCollider* _pOther) PURE;//�浹���� ��� ȣ��Ǵ� �Լ�
	virtual void    OnCollisionEnter(CCollider* _pOther) PURE;//�浹 ������ ��� ȣ��Ǵ� �Լ�
	virtual void    OnCollisionExit(CCollider* _pOther) PURE;//�浹�� ������ ȣ��Ǵ� �Լ�
	//TrigerFunction
	virtual void    OnTrigger(CCollider* _pOther) PURE;//�浹���� ��� ȣ��Ǵ� �Լ�
	virtual void    OnTriggerEnter(CCollider* _pOther) PURE;//�浹 ������ ��� ȣ��Ǵ� �Լ�
	virtual void    OnTriggerExit(CCollider* _pOther) PURE;//�浹�� ������ ȣ��Ǵ� �Լ�
protected:
	void Set_Initial_Points()
	{
		//LT,RT,RB,LB
		m_vPoint[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
		m_vPoint[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
		m_vPoint[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
		m_vPoint[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	}
	void Set_Matrix_to_Identity()
	{
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixIdentity(&m_matScale);
		D3DXMatrixIdentity(&m_matRotZ);
		D3DXMatrixIdentity(&m_matTrans);
	}
	virtual void		CalcMat();
protected:
	wstring		m_strName;//������Ʈ ����

	DXV3		m_vPos;
	DXV3		m_vScale;//������

	DXMAT		m_matWorld;
	DXMAT		m_matScale;
	DXMAT		m_matRotZ;
	DXMAT		m_matTrans;

	DXV3		m_vDir;	// ���⺤��
	DXV3		m_vLook;
	DXV3		m_vWorldDir;	//���� ����

	DXV3		m_vPoint[4];		// render ��ǥ
	DXV3		m_vWorldPoint[4];	// world ��ǥ

	float		m_fRadian = 0;//������Ʈ ����
	bool		m_bActive;//������Ʈ Ȱ��ȭ ����
	OBJID		m_eID;//������Ʈ ����Ƽ
	RENDERID	m_eRenderID;//���� ����
	vector<CComponent*> m_vecComponents;//������ ������Ʈ

	DXV3		m_vDirPos;
	DXV3		m_vMoveSize = {};
};

