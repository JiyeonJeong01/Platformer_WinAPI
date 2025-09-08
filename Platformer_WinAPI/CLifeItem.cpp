#include "pch.h"
#include "CLifeItem.h"

void CLifeItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CLifeItem::Initialize()
{
	m_objID = ITEM;
	m_bDead = false;
	m_fSpeedX = 0.f;
	m_fSpeedY = 0.f;

	m_vPosition = { 0.f, 0.f };
	m_vDirection = { 0.f, 0.f };
	m_vSize = { 20.f, 10.f };
}

void CLifeItem::Apply_Effect(CObject* pObj)
{
	// player's current hp +20%
	pObj->Set_HP(min(pObj->Get_MaxHP(), pObj->Get_HP() * 1.35f));
	m_bDead = true;
}