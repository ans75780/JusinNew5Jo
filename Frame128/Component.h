#pragma once
#include "ComponentBase.h"

class CObj;

class CComponent :
    public CComponentBase
{
public:
    CComponent();
    virtual ~CComponent();

public:
    virtual void Init();
    virtual void Release();
    virtual void Update();
    virtual void Late_Update();
    virtual void Render(HDC hDC);

public:
    wstring& Get_Name() { return m_strName; }
    CComponentBase* Get_Component() { return this; }
    CObj* Get_Owner() { return m_pOwner; }

public:
   virtual void Set_Owner(CObj* _pOwner) { m_pOwner = _pOwner; }

protected:
    CObj* m_pOwner;
    wstring	m_strName;
};