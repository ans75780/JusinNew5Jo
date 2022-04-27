#include "stdafx.h"
#include "Component.h"

CComponent::CComponent()
	:m_pOwner(nullptr)
{
}

CComponent::~CComponent()
{
}

void CComponent::Init()
{
}

void CComponent::Release()
{
}

void CComponent::Update()
{
}

void CComponent::Late_Update()
{
}

void CComponent::Render(HDC hDC)
{
}
