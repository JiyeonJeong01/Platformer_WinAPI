#include "pch.h"
#include "CPowerItem.h"

void CPowerItem::Initialize()
{
	m_objID = ITEM;
	m_bDead = false;
	m_fSpeedX = 0.f;
	m_fSpeedY = 0.f;

	m_vPosition = { 0.f, 0.f };
	m_vDirection = { 0.f, 0.f };
	m_vSize = { 10.f, 20.f };

	fPowerUpPercentage = 1.2f;
}

void CPowerItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}



void CPowerItem::Apply_Effect(CObject* pObj)
{
	pObj->Set_Damage(pObj->Get_Damage() * fPowerUpPercentage);
	m_bDead = true;
}
