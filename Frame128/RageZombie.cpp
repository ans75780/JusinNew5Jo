#include "stdafx.h"
#include "RageZombie.h"
#include "UserDefineHeaders.h"

CRageZombie::CRageZombie()
{
}

CRageZombie::~CRageZombie()
{
	Release();
}

void CRageZombie::Init(void)
{
	m_UnitStat.Set_Atk(15.f);
	m_UnitStat.Set_Hp(20.f);
	m_UnitStat.Set_MaxHp(60.f);

	m_vPos = { 400, 100, 0.f };
	m_vScale = { 50, 50.f, 0.f };

	m_vPoint[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vPoint[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	m_vPoint[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };

	m_fSpeed = 60;

	m_bActive = true;
	m_eID = OBJID::OBJ_MONSTER;
	m_eRenderID = RENDERID::RENDER_OBJ;
	m_strName = L"Zombie";

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotZ);
	D3DXMatrixIdentity(&m_matTrans);

	CreateCollider();
	FindTarget();
	CHand* hand = new CHand(this, DXV3(45, -15, 0));
	MGR(CObjMgr)->AddObject(OBJ_MONSTER, hand);
	hand = new CHand(this, DXV3(45, 15, 0));
	MGR(CObjMgr)->AddObject(OBJ_MONSTER, hand);

	m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Monster", L"Zombie", m_iTexIndex);

	m_fCurTime = 0.75;

	m_vImgScale = { m_vScale.x / m_pTexInfo->tImgInfo.Width ,m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f };

	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fRadian);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;
	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);
	m_bUpdated = false;
}

int CRageZombie::Update(void)
{
	m_bUpdated = true;
	if (m_UnitStat.Get_Hp() < 1)
	{
		Set_Active(false);
	}
	if (m_bActive == false)
	{
		return OBJ_DEAD;
	}
	if (KEYTAP(R))
	{
		m_UnitStat.Damaged(100);
	}
	SetRadianToPlayer();
	//m_fRadian = D3DXToRadian(90.f);

	//CalcMat();
	m_fImgTime -= DT * 0.2f;
	D3DXMatrixScaling(&m_matScale, m_vScale.x / m_pTexInfo->tImgInfo.Width, m_vScale.y / m_pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixRotationZ(&m_matRotZ, m_fRadian);
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, 0.f);
	m_matWorld = m_matScale * m_matRotZ * m_matTrans;
	for (int i(0); i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vWorldPoint[i], &m_vPoint[i], &m_matWorld);
	}
	D3DXVec3TransformNormal(&m_vWorldDir, &m_vDir, &m_matRotZ);
	m_vMoveSize = m_vWorldDir * m_fSpeed * DT;
	m_vPos += m_vMoveSize;

	//CurTime?? 0???? ?????? ?????? ????
	if (m_fCurTime <= 0.1f)
	{
		m_iTexIndex = (m_iTexIndex + 1) % 16;
		m_pTexInfo = MGR(CTextureMgr)->Get_Texture(L"Monster", L"Zombie", m_iTexIndex);
		m_fCurTime = m_fImgTime;
	}
	else
	{
		m_fCurTime -= DT;
	}

	return 0;
}

void CRageZombie::Render(HDC hDC)
{
	if (!m_bUpdated)
		return;
	MGR(CDevice)->Get_Sprite()->SetTransform(&m_matWorld);


	float Half_Width = m_pTexInfo->tImgInfo.Width * 0.5f;
	float Half_Height = m_pTexInfo->tImgInfo.Height * 0.5f;

	MGR(CDevice)->Get_Sprite()->Draw(m_pTexInfo->pTexture, // ?????? ????
		nullptr,	// ?????? ?????? ?????? ???? ???? ?????? ??????, null?? ???? ???????? 0, 0???????? ????
		&D3DXVECTOR3(Half_Width, Half_Height, 0.f),	// ?????? ???????? ???? ???? ???? vec3 ?????? ??????, null?? ???? 0, 0?? ???? ????
		nullptr,	// ???? ?????? ???? vec3 ?????? ??????, null?? ???? ?????? ?? 0,0,?? ???? ????
		D3DCOLOR_ARGB(255, 165, 0, 0));


}

void CRageZombie::Release(void)
{
}

void CRageZombie::Set_Active(bool _isActive)
{
	CObj::Set_Active(_isActive);

	if (!_isActive)
	{
		MGR(SoundMgr)->Play("Zombie_Dead");
		CObj* Coin = CAbstractFactory<CCoin>::Create();
		Coin->Set_Pos(m_vPos);
		MGR(CObjMgr)->AddObject(OBJ_ITEM, Coin);
	}
}