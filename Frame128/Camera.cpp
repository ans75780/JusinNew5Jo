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
	if (m_pTargetObj)//오브젝트가 존재한다면
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
	//화면 흔드는 상태라면
	if (m_bShake)
	{
		//흔드는 위치를 난수로 지정해서 스크롤에 더해줌
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
		//틱 당 보정값만큼 쉐이크 파워를 뺴줌
		float fAmount = MGR(CRandomMgr)->getFromFloatTo(1, 3) * 0.1;
		m_fShakePower -= fAmount;
		if (m_fShakePower < 0.1f)//흔드는 파워가 0.1보다 작다면 흔들기 멈춤
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
	if (m_vLootAt.x + WINCX_HALF >= 1000)//맵 가로범위를 카메라가 벗어날 경우,
	{
		m_vLootAt.x = (TILECX * TILEX) - WINCX_HALF;
	}
	if (m_vLootAt.x - WINCX_HALF <= 0)//맵 가로범위를 카메라가 벗어날 경우,
	{
		m_vLootAt.x = WINCX_HALF;
	}
	if (m_vLootAt.y + WINCY_HALF >= 600)//맵 가로범위를 카메라가 벗어날 경우,
	{
		m_vLootAt.y = (TILECY * TILEY) - WINCY_HALF;
	}
	if (m_vLootAt.y - WINCY_HALF <= 0)//맵 가로범위를 카메라가 벗어날 경우,
	{
		m_vLootAt.y = WINCY_HALF;
	}
}

