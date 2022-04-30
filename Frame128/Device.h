#pragma once

#include "SingletonBase.h"
#include "Include.h"

class CScene;

class CDevice : public CSingletonBase<CDevice>
{
	friend	CSingletonBase;

private:
	CDevice();
	~CDevice();

public:
	LPDIRECT3DDEVICE9		Get_Device(void) { return m_pDevice; }
	LPD3DXSPRITE			Get_Sprite(void) { return m_pSprite; }
	LPD3DXLINE			Get_Line(void) { return m_pLine; }
	LPD3DXFONT			Get_Font(void) { return m_pFont; }
	void			Draw_Line(D3DXVECTOR3 vertex[], int count, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));



public:
	HRESULT			Init(void);
	void			Render_Begin(void);
	void			Render_End(HWND hWnd = NULL);
	void			Release(void);

	void			Set_BufferSize(POINT _Point);
	const POINT&			Get_BufferSize();

	// ��ġ�ʱ�ȭ ����
/*  1. �ϵ��� ������ ��ġ ��ü ����
	2. �ϵ���� ����(���� ����)
	3. �ϵ��� ������ ��ü ����*/

	// COM(COMPONENT object model) ��ü : ���� ȯ�濡 ������� ȣȯ�� ������ ������Ʈ�� ����� ���� ms���� ������ ǥ��ȭ�� ���

private:
	void		Set_Partameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9			m_pSDK;		// ����ϰ��� �ϴ� �ϵ���� ��ġ�� �����ϰ�, �ش� ��ġ�� �����ϱ� ���� ��ü ������ ���ִ� ������
	LPDIRECT3DDEVICE9	m_pDevice;	// �׷��� ��ġ�� ���� �������� �����ϴ� ��ü ������
	LPD3DXSPRITE		m_pSprite;	// dx�󿡼� 2D �̹����� ������ִ� com ��ü ������
	LPD3DXLINE		m_pLine; //dx�󿡼� 2D������ ������ִ� �� ��ü ������
	LPD3DXFONT		m_pFont;

	POINT m_BufferSize;
	
};

