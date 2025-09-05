#include "pch.h"
#include "CItem.h"

void CItem::Initialize()
{
	m_objID = ITEM;
	m_bDead = false;
	m_fSpeedX = 0.f;
	m_fSpeedY = 0.f;
}

int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CItem::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CItem::On_Collision(CObject* pObj)
{
	if (pObj->Get_ObjectID() == PLAYER)
	{
		Apply_Effect(pObj);
	}
}