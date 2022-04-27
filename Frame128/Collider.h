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
    // CComponentBase을(를) 통해 상속됨
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
public:// 충돌시점 함수
    //OnCollision은 물리적 충돌처리(밀어냄 효과)를 줌
    void    OnCollision(CCollider* _pOther) ;//충돌중인 경우 호출되는 함수
    void    OnCollisionEnter(CCollider* _pOther);
    void    OnCollisionExit(CCollider* _pOther);
public:
    //OnTriger는 컬라이더에 충돌했으나, 물리적 충돌처리는 해주지 않음. 이는 m_bIsTriger가 True일때만 호출됨.
    void    OnTrigger(CCollider* _pOther);
    void    OnTriggerEnter(CCollider* _pOther);
    void    OnTriggerExit(CCollider* _pOther);
private:
    void    CalcCollision(CCollider* _pOther);//충돌체와 물리적인 밀어내기를 구현
    void    SyncOwnerPos();

private:
    static             UINT g_iNextID;
public:
    static void      Reset_Collider_ID() { g_iNextID = 0; }//씬 전환등의 경우에만 사용 안그러면 거의 무조건 충돌에러남
private:
    VECTOR2         m_vOffsetPos;
    VECTOR2         m_vScale;
    VECTOR2         m_vFinalPos;
    UINT               m_iID;
private://충돌 처리 관련
    bool                m_bIsTriger;
};

