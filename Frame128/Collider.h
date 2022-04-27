#pragma once
#include "Component.h"
class CCollider :
    public CComponent
{
public:
    CCollider();
    virtual ~CCollider();
    CCollider(const CCollider& _origin);
    CCollider& operator    =(CCollider& _origin) = delete;
public:
    // CComponentBase��(��) ���� ��ӵ�
    virtual void    Init() override;
    virtual void    Release() override;
    virtual void    Update() override;
    virtual void    Late_Update() override;
    virtual void    Render(HDC hDC) override;
public:
    virtual void   Set_Owner(CObj* pObj);
    void            Set_Scale(VECTOR2 vec2) { m_vScale = vec2; }
    void            SetOffsetPos(VECTOR2 vec2) { m_vOffsetPos = vec2; }
    void            SetTriger(bool _triger) { m_bIsTriger = _triger; }
public:
    VECTOR2     Get_Scale() { return m_vScale; }
    VECTOR2     Get_OffsetPos() {return  m_vScale; }
    VECTOR2     Get_FinalPos() { return m_vFinalPos; }
    UINT            Get_Collider_ID() { return m_iID; }
    bool            Get_IsTriger() { return m_bIsTriger; }
public:// �浹���� �Լ�
    //OnCollision�� ������ �浹ó��(�о ȿ��)�� ��
    void    OnCollision(CCollider* _pOther) ;//�浹���� ��� ȣ��Ǵ� �Լ�
    void    OnCollisionEnter(CCollider* _pOther);
    void    OnCollisionExit(CCollider* _pOther);
public:
    //OnTriger�� �ö��̴��� �浹������, ������ �浹ó���� ������ ����. �̴� m_bIsTriger�� True�϶��� ȣ���.
    void    OnTrigger(CCollider* _pOther);
    void    OnTriggerEnter(CCollider* _pOther);
    void    OnTriggerExit(CCollider* _pOther);
private:
    void    CalcCollision(CCollider* _pOther);//�浹ü�� �������� �о�⸦ ����
    void    SyncOwnerPos();

private:
    static             UINT g_iNextID;
public:
    static void      Reset_Collider_ID() { g_iNextID = 0; }//�� ��ȯ���� ��쿡�� ��� �ȱ׷��� ���� ������ �浹������
private:
    VECTOR2         m_vOffsetPos;
    VECTOR2         m_vScale;
    VECTOR2         m_vFinalPos;
    UINT               m_iID;
private://�浹 ó�� ����
    bool                m_bIsTriger;
};

