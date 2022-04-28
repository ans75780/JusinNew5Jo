#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "AbstractFactory.h"
#include "Bullet.h"

CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{
    Release();
}
void CPlayer::Init(void)
{
	D3DXMatrixIdentity(&m_matLocal);
    m_vPos = { 300,300, 0.f};
	m_fWheelDist = 25;

	m_vWheel[LT].x = -m_fWheelDist;
	m_vWheel[LT].y  = -m_fWheelDist;

	m_vWheel[LB].x = -m_fWheelDist;
	m_vWheel[LB].y = +m_fWheelDist;

	m_vWheel[RT].x = +m_fWheelDist;
	m_vWheel[RT].y = -m_fWheelDist;

	m_vWheel[RB].x = +m_fWheelDist;
	m_vWheel[RB].y = +m_fWheelDist;

    m_vScale = { 50,50 ,0.f};
    m_fSpeed = 500.f;
    m_fRadian = D3DXToRadian(0);
    m_fAtk = 0.f;
    m_eID = OBJ_PLAYER;
    m_eRenderID = RENDERID::RENDER_OBJ;
    m_strName = L"Player";

    CreateCollider();

}

int CPlayer::Update(void)
{
    if (!m_bActive)
        return OBJ_DEAD;
	m_vDirPos.x = 0;
	m_vDirPos.y = 0;
	// Ű�Է¿� ���� update ���� key_input�Լ��� �̵�
	key_input();

    int a = 0;

    for (auto& iter : m_vecComponents)
        iter->Update();                                    

    return 0;
}

void CPlayer::Render(HDC hDC)
{
	MoveToEx(hDC, m_vCoord[LT].x, m_vCoord[LT].y, NULL);
	LineTo(hDC, m_vCoord[LB].x, m_vCoord[LB].y);
	LineTo(hDC, m_vCoord[RB].x, m_vCoord[RB].y);
	LineTo(hDC, m_vCoord[RT].x, m_vCoord[RT].y);
	LineTo(hDC, m_vCoord[LT].x, m_vCoord[LT].y);
    /*
	for (auto& iter : m_vecComponents)
        iter->Render(hDC);*/
}

void CPlayer::Release(void)
{
    for_each(m_vecComponents.begin(), m_vecComponents.end(), Safe_Delete<CComponent*>);
    m_vecComponents.clear();
    m_strName.clear();
}

void CPlayer::key_input()
{
	// �÷��̾� 8�������� �������
	// �׷��� �÷��̾ �ٶ󺸴� �������� �Ѿ��� �������� ���� (���ž���)
#pragma region original version
	if (MGR(CKeyMgr)->isStayKeyDown('A'))
		m_fRadian -= D3DXToRadian(5.f);
	if (MGR(CKeyMgr)->isStayKeyDown('D'))
		m_fRadian += D3DXToRadian(5.f);
	if (MGR(CKeyMgr)->isStayKeyDown('W'))
	{
		D3DXMATRIX infoRotZMat;
		D3DXMATRIX infoTranslateLocalMat;
		D3DXMATRIX infoWorldMat;
		D3DXMATRIX infoParentMat;

		D3DXMatrixRotationZ(&infoRotZMat, m_fRadian);
		D3DXMatrixTranslation(&infoTranslateLocalMat, 0, -m_fSpeed * DT, 0);
		D3DXMatrixTranslation(&infoParentMat, m_vPos.x, m_vPos.y, 0);
		infoWorldMat = infoTranslateLocalMat * infoRotZMat * infoParentMat;
		D3DXVec3TransformCoord(&m_vPos, &D3DXVECTOR3(0, 0, 0), &infoWorldMat);
		//D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &infoParentMat);
	}
	if (MGR(CKeyMgr)->isStayKeyDown('S'))
	{
		D3DXMATRIX infoRotZMat;
		D3DXMATRIX infoTranslateLocalMat;
		D3DXMATRIX infoWorldMat;
		D3DXMATRIX infoParentMat;

		//�����̼��̶� Ʈ�������̼� �Լ��� �⺻������ ��Ʈ������ �ʱ�ȭ������
		D3DXMatrixRotationZ(&infoRotZMat, m_fRadian);
		D3DXMatrixTranslation(&infoTranslateLocalMat, 0, m_fSpeed * DT, 0);
		D3DXMatrixTranslation(&infoParentMat, m_vPos.x, m_vPos.y, 0);
		infoWorldMat = infoTranslateLocalMat * infoRotZMat * infoParentMat;
		D3DXVec3TransformCoord(&m_vPos, &D3DXVECTOR3(0, 0, 0), &infoWorldMat);
		//D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &infoParentMat);
	}
#pragma endregion __



#pragma region 8�����̵����� ����, �̵������� �ٶ󺸵��� ������
	// �����̴� Ű�� �ӽ÷� I(��), K(��), J(��), L(��)
	if (MGR(CKeyMgr)->isStayKeyDown('I'))
	{
		// �� �̵�
		eDirection = UP;
		vLocalDir = { 0.f, -1.f, 0.f };
		vLocalPos.x += vLocalDir * m_fSpeed * DT;
		vLovalPos.y += vLocalDir * m_fSpeed * DT;
	}

	if (MGR(CKeyMgr)->isStayKeyDown('K'))
	{
		// �� �̵�
		eDirection = DOWN;
	}

	if (MGR(CKeyMgr)->isStayKeyDown('J'))
	{
		// �� �̵�
		eDirection = LEFT;
	}

	if (MGR(CKeyMgr)->isStayKeyDown('L'))
	{
		// �� �̵�
		eDirection = RIGHT;
	}

#pragma endregion __

	


	if (MGR(CKeyMgr)->isOnceKeyUp(VK_SPACE))
	{
		// create bullet
		MGR(CObjMgr)->AddObject(OBJID::OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_vPos.x, m_vPos.y, m_fRadian));
	}
	CalcMat();
}

void CPlayer::OnCollision(CCollider * _pOther)
{
}

void CPlayer::OnCollisionEnter(CCollider * _pOther)
{
}

void CPlayer::OnCollisionExit(CCollider * _pOther)
{
}

void CPlayer::OnTrigger(CCollider * _pOther)
{
}

void CPlayer::OnTriggerEnter(CCollider * _pOther)
{
}

void CPlayer::OnTriggerExit(CCollider * _pOther)
{
}

void CPlayer::CalcMat()
{
	DXMAT		matScale;
	DXMAT		matRotZ;
	DXMAT		matTransform;
	DXMAT		matWheelTransform;//���� ���� ����� ���� ��ǥ
	DXMAT		matWheelRotZ;//���� ���� ����� ���� ��ǥ
	DXMAT		matWheelLocal;
	DXV3			m_tPos;
	DXV3			m_tAngle;

	
	m_tPos = m_vPos;
	float angle = D3DXToDegree(m_fRadian);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fRadian);
	D3DXMatrixTranslation(&matTransform, m_vPos.x, m_vPos.y, 0.f);
	m_matLocal = matScale * matRotZ * matTransform;

	for (int i = 0; i < 4; i++)
	{
		D3DXMatrixTranslation(&matWheelTransform, m_vWheel[i].x, m_vWheel[i].y, 0.f);

		//���� ���忡���� �÷��̾��� m_matLocal�� �����̱⿡ �� ������ �տ��� �����ش�.
		// ũ * �� * ��  * ��
		matWheelLocal = matWheelTransform * m_matLocal;
		D3DXVec3TransformCoord(&m_vCoord[i], &m_vWheel[i], &matWheelLocal);
	}

}
