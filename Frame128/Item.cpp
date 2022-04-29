#include "stdafx.h"
#include "Item.h"
#include "UserDefineHeaders.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

void CItem::AddMagnetic()
{
	if (!m_pTarget)
	{
		return;
	}

	DXV3 vTargetDir = m_pTarget->Get_Pos() - m_vPos;
	float fDistance = D3DXVec3Length(&vTargetDir);


	D3DXVec3Normalize(&vTargetDir, &vTargetDir);
	
	if (fDistance < m_fTargetDistance)
	{
		m_vPos += vTargetDir * m_fSpeed * DT;
		m_fSpeed *= 1.1f;
	}

}
