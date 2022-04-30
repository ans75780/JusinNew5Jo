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

typedef		struct tagTexture
{
	LPDIRECT3DTEXTURE9	pTexture;	// 객체, 이미지와 관련된 각종 기능을 제공하는 클래스

	D3DXIMAGE_INFO		tImgInfo;	// 구조체, 이미지와 관련된 실제적인 데이터를 저장하는 구조체

}TEXINFO;