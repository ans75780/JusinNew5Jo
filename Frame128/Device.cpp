#include "stdafx.h"
#include "Device.h"
#include "UserDefineHeaders.h"

CDevice::CDevice()
	: m_pSDK(nullptr), m_pDevice(nullptr), m_pSprite(nullptr)
{

}


CDevice::~CDevice()
{
	Release();
}

void CDevice::Draw_Line(D3DXVECTOR3 vecs[],int count, D3DXCOLOR color)

{
	D3DXVECTOR2 * line = new D3DXVECTOR2[count];
	for (int i = 0; i < count; i++)
	{
		line[i].x = vecs[i % 4].x;
		line[i].y = vecs[i % 4].y;
	}
	DEVICE->Get_Line()->Draw(line, (sizeof(D3DXVECTOR2) * count) / sizeof(D3DXVECTOR2), color);
	
	delete[] line;
	line = nullptr;
}

//	HRESULT : �����ϰ� �Ǹ� ��� ���� ��ȯ, �����ϰ� �Ǹ� ������ ��ȯ ��Ű���� ������ ����
HRESULT CDevice::Init(void)
{
	// ��ġ �ʱ�ȭ ����
	/*  1. �ϵ��� ������ ��ġ ��ü ����
	2. �ϵ���� ����(���� ����)
	3. �ϵ��� ������ ��ü ����*/

	 // 1. LPDIRECT3D9 ��ü ����

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	
	// 2. �ϵ���� ����
	
	D3DCAPS9			DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// GetDeviceCaps : ��ġ�� ���� ����(���� ����)�� ������ �Լ�
	// D3DADAPTER_DEFAULT : ������ �������� �⺻ �׷��� ī�带 �ǹ�
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		return E_FAIL;
	}

	DWORD		vp = 0;		// ���ؽ� ���μ��� = ������ ��ȯ + ������

	// HAL�� ���� ������ ��ġ�� �ϵ���� ���ؽ� ���μ����� �����Ѵٸ�
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;

	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	// 3. LPDIRECT3DDEVICE9 ��ü ����

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	Set_Partameters(d3dpp);

	// CreateDevice : ��ġ�� ������ �׷��� �İ�ü�� ����
	/*
	1. � �׷��� ī�带 ������ ���ΰ�
	2. � ������ ��ġ�� ������ ���ΰ�
	3. ��ġ�� ����� ������ �ڵ�
	4. ���� ���
	5. ���ȯ��
	6. ������ �İ�ü �ּ�*/
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		return E_FAIL;
	}
	// ��������Ʈ �� ��ü 
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		MessageBox(g_hWnd, L"D3DXCreateLine Failed", NULL, 0);
		return E_FAIL;
	}
		
	//return E_FAIL;
	return S_OK;
}

// �ĸ� ����
void CDevice::Render_Begin(void)
{
	m_pDevice->Clear(0,			// ������� �ϴ� ��Ʈ�� ����
					nullptr,	// ��Ʈ �迭�� ù ��° �ּ�	, nullptr�� ��� ��ü ������ ���ڴٴ� �ǹ�
					D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,	// ���ٽ�, ����, Ÿ�� ���� ���ڴٴ� �ǹ�
					D3DCOLOR_ARGB(255, 125, 125, 125),	// �� ������ ����
					1.f,		// ���� ������ �ʱ�ȭ ��(�ſ� �߿�!!!!!!!!!!!!!)
					0);			// ���ٽ� ������ �ʱ�ȭ ��

	
	// ���⼭���� �ĸ� ���ۿ� �׸��⸦ �����ϰڴ�.
	m_pDevice->BeginScene();


	// 2D�̹����� �׸� �� �ֵ��� ��ġ�� �غ�(������ �ɼ�) // ���� �׽�Ʈ�� ��ȿ�� ���¿��� ���� ���� ����ϰڴٴ� �ɼ�
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pLine->Begin();
}




// ����ü�� ������ �ĸ� ����
void CDevice::Render_End(HWND hWnd)
{

	m_pLine->End();
	m_pSprite->End();
	m_pDevice->EndScene();

	// ���� ������ ����
	// 1, 2���� : ���� ü���� D3DSWAPEFFECT_COPY�� �ۼ����� �ʴ��� NULL
	// 3���� : ��� ��� ������ �ڵ�
	// 4���� :  ���� ü���� D3DSWAPEFFECT_COPY�� �ۼ����� �ʴ��� NULL

	m_pDevice->Present(NULL, NULL, hWnd, NULL);

}

void CDevice::Release(void)
{
	Safe_Release(m_pLine);
	Safe_Release(m_pSprite);
	Safe_Release(m_pDevice);
	Safe_Release(m_pSDK);
}

void CDevice::Set_BufferSize(POINT _Point)
{
	m_BufferSize = _Point;
}

const POINT& CDevice::Get_BufferSize()
{
	return m_BufferSize;
}

void CDevice::Set_Partameters(D3DPRESENT_PARAMETERS& d3dpp)
{
	d3dpp.BackBufferWidth	= m_BufferSize.x;
	d3dpp.BackBufferHeight	= m_BufferSize.y;
	d3dpp.BackBufferFormat  = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	
	/*D3DSWAPEFFECT_DISCARD = ����ü�� ���
	D3DSWAPEFFECT_FLIP = ���� �ϳ��� �������鼭 ����ϴ� ���
	D3DSWAPEFFECT_COPY = ���� ���۸��� ������ ���� ���*/
	
	//���� ü�� : ������ �ø��� ������� �̷��� ������ ���� ���۴� ������ ���, �ĸ� ���۴� ����� ���� ȭ�� ����� ���� �׸��� ���� �д����� ���� ����Ű�� ����� ��ü�Ͽ� �����Ÿ� ���� �� ȭ�� ������ �����ϰ� ������ �� �ִ�.

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// ����ü�� ���

	d3dpp.hDeviceWindow = g_hWnd;
	
	//â ���� ����, ��üȭ�� ����
	d3dpp.Windowed =  TRUE;		// TRUE�� ��� â ��� ����

	// Ÿ�� ����(�׸��� ����), ���ٽ� ����(�ݻ簡 �Ǵ� ���� ǥ��), ���� ����(���� ���� ����)
	// �ڵ����� ���ٽ� ���ۿ� ���̹��۸� �����ϰڴٴ� �ɼ�
	d3dpp.EnableAutoDepthStencil = TRUE;
	//���� ���� 24��Ʈ, ���ٽ� ���� 8��Ʈ
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;


	// ��üȭ�� �ÿ��� ���Ǵ� �Ű� ������
	// â ��忡���� �ü���� ������� ������
	// ��üȭ�� �ÿ��� �׷��� ī�尡 �����ϰ� �ȴ�.

	// ��üȭ�� �� ���� ����� ��������� ����(���� ����� ������� ���� �˾Ƽ� ����)
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// ������� �ÿ� ���ݼ���
	// D3DPRESENT_INTERVAL_IMMEDIATE  : ��� �ÿ�
	// D3DPRESENT_INTERVAL_DEFAULT : ������ ������ ��ġ�� �˾Ƽ� ����(���� ����� ������� ����)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
