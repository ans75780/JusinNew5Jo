#pragma once
#include "Obj.h"
// ������ �� �ִ� �ֵ�
class CUnit :
    public CObj
{
public:
    CUnit();
    virtual ~CUnit();
    // CObj��(��) ���� ��ӵ�
    virtual void    Init(void) PURE;
    virtual int      Update(void) PURE;
    virtual void    Render(HDC hDC) PURE;
    virtual void    Release(void) PURE;

protected:
    float           m_fSpeed;
	// �߰������� ���� �߰� ��
};

