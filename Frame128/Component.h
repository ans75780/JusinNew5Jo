#pragma once
#include "ComponentBase.h"

class CObj;

class CComponent :
    public CComponentBase
{
public:
    CComponent();
    virtual ~CComponent();
    // CComponentBase을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
public:
    wstring& Get_Name() { return m_strName; }
    CComponentBase* Get_Component() { return this; }
    CObj* Get_Owner() { return m_pOwner; }
public:
   virtual void             Set_Owner(CObj* _pOwner) { m_pOwner = _pOwner; }
protected:
    CObj* m_pOwner;
    wstring	m_strName;
};

