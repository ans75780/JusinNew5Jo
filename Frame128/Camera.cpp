#include "stdafx.h"
#include "Camera.h"
#include "Obj.h"
#include "KeyMgr.h"
#include "RandomMgr.h"
#include "TimeMgr.h"
CCamera::CCamera()
	:m_pTargetObj(nullptr), m_vLootAt(0, 0, 0)
{
	m_fShakeTick = 0.f;
	m_fShakeTime = 1.f;
	m_bShake = false;
	m_fShakePower = 0.f;
	m_vShakePos = { 0,0,0 };
}

CCamera::~CCamera()
{
}

void CCamera::CalDiff()
{
	DXV3	vCenter(WINCX_HALF, WINCY_HALF, 0);
	m_vDiff = m_vLootAt - vCenter;
}

void CCamera::Update()
{
	if (m_pTargetObj)//������Ʈ�� �����Ѵٸ�
	{
		if (!m_pTargetObj->Get_Active())
			m_pTargetObj = nullptr;
		else
			m_vLootAt = m_pTargetObj->Get_Pos();
		//CalcCameraOffset();
	}
	if (m_pTargetObj != m_MainTarget)
	{
		m_fSwapTime -= DT;
		if (m_fSwapTime <= 0.001f)
		{
			m_pTargetObj = m_MainTarget;
		}
	}
	CalDiff();
	m_vShakePos = { 0,0,0 };
	//ȭ�� ���� ���¶��
	if (m_bShake)
	{
		//���� ��ġ�� ������ �����ؼ� ��ũ�ѿ� ������
		int i = MGR(CRandomMgr)->getInt(4);
		switch (i)
		{
		case 0:
			m_vShakePos.x += m_fShakePower;
			break;
		case 1:
			m_vShakePos.x -= m_fShakePower;
			break;
		case 2:
			m_vShakePos.y += m_fShakePower;
			break;
		case 3:
			m_vShakePos.y -= m_fShakePower;
			break;
		default:
			break;
		}
		//ƽ �� ��������ŭ ����ũ �Ŀ��� ����
		float fAmount = MGR(CRandomMgr)->getFromFloatTo(1, 3) * 0.1;
		m_fShakePower -= fAmount;
		if (m_fShakePower < 0.1f)//���� �Ŀ��� 0.1���� �۴ٸ� ���� ����
		{
			m_bShake = false;
			m_vShakePos = { 0,0,0 };
		}
	}
}

void CCamera::Shake(float _Power)
{
	m_bShake = true;
	m_fShakePower = _Power;
	m_fShakeTick = 0.f;
}

bool CCamera::PosInCam(DXV3& Pos, DXV3& Scale)
{

	DXV3 LeftBottom = Pos + (Scale / 2.f);
	DXV3 RightTop = Pos - (Scale / 2.f);
	if (LeftBottom.x >= (m_vLootAt.x - WINCX_HALF) && RightTop.x <= (m_vLootAt.x + WINCX_HALF) &&
		LeftBottom.y >= (m_vLootAt.y - WINCY_HALF) && RightTop.y <= (m_vLootAt.y + WINCY_HALF)
		)
	{
		return true;
	}
	return false;
}

void CCamera::CalcCameraOffset()
{
	if (m_vLootAt.x + WINCX_HALF >= 1000)//�� ���ι����� ī�޶� ��� ���,
	{
		m_vLootAt.x = (TILECX * TILEX) - WINCX_HALF;
	}
	if (m_vLootAt.x - WINCX_HALF <= 0)//�� ���ι����� ī�޶� ��� ���,
	{
		m_vLootAt.x = WINCX_HALF;
	}
	if (m_vLootAt.y + WINCY_HALF >= 600)//�� ���ι����� ī�޶� ��� ���,
	{
		m_vLootAt.y = (TILECY * TILEY) - WINCY_HALF;
	}
	if (m_vLootAt.y - WINCY_HALF <= 0)//�� ���ι����� ī�޶� ��� ���,
	{
		m_vLootAt.y = WINCY_HALF;
	}
}

