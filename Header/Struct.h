#pragma once

typedef D3DXVECTOR3 DXV3;
typedef D3DXMATRIX	DXMAT;

typedef struct tagInfo
{
	DXV3 vPos;
	DXV3 vScale;
	DXV3 vDir;

	DXMAT matWorld;
}INFO;