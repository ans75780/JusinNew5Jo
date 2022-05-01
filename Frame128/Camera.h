#pragma once

#include "Include.h"
#include "SingletonBase.h"

class CObj;

class CCamera : public CSingletonBase<CCamera>
{
	friend CSingletonBase;
private:
	CCamera();
	~CCamera();
private:
	void	CalDiff();
public:
	void	Update();
	void	Shake(float _Power);
public:
	void	SetLookAt(DXV3	_vLook) { m_vLootAt = _vLook; }
	void	SetTarget(CObj* _pTarget) { m_pTargetObj = _pTarget; m_MainTarget = m_pTargetObj; }
	void	Swap(CObj* _pTarget, float fTime) { m_pTargetObj = _pTarget; m_fSwapTime = fTime; }
	DXV3	Get_ShakePos() { return m_vShakePos; }
	bool	PosInCam(DXV3& Pos, DXV3& Scale);
	bool	isShake() { return m_bShake; }
public:
	DXV3	Get_RenderPos(DXV3 _vObjPos) { return _vObjPos - m_vDiff; }
	DXV3	Get_LootAt()
	{
		DXV3 ret = m_vLootAt;
		ret.x -= WINCX_HALF;
		ret.y -= WINCY_HALF;
		return ret;
	}
private:
	void	CalcCameraOffset();
private:
	DXV3	m_prevPos;
	DXV3	m_vLootAt;// ī�޶� ���� ��ġ
	DXV3	m_vPrevLootAt;//ī�޶� ���� ���������� ��ġ
	CObj* m_pTargetObj;// ī�޶� Ÿ�� ������Ʈ
	CObj* m_MainTarget;// ī�޶� Ÿ�� ������Ʈ
	DXV3	m_vDiff; //�ػ� �߽���ġ��, ī�޶� LootAk ���� ���̰�
	DXV3	m_vShakePos;

	float			m_fShakeTick;
	float			m_fShakeTime;
	bool			m_bShake;
	float			m_fShakePower;
	float			m_fSwapTime;

	float			m_fZoomTick;
	float			m_fZoomTime;
	float			m_fZoomPower;
	float			m_bZoom;

};

