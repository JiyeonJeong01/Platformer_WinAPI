#include "pch.h"
#include "CObject.h"

CObject::CObject()
	: m_tRect({ 0, 0, 0, 0 }),
	  m_fSpeedX(0.f), m_fSpeedY(0.f),
	  m_bDead(false),
	  m_objID(OBJ_END),
	  m_fHP(0.f), m_fMaxHP(0.f), m_fDamage(0.f)
{
}

CObject::~CObject()
{
}

void CObject::Update_Rect()
{
	m_tRect.left   = static_cast<LONG>(m_vPosition.x - (m_vSize.x / 2.f));
	m_tRect.top    = static_cast<LONG>(m_vPosition.y - (m_vSize.y / 2.f));
	m_tRect.right  = static_cast<LONG>(m_vPosition.x + (m_vSize.x / 2.f));
	m_tRect.bottom = static_cast<LONG>(m_vPosition.y + (m_vSize.y / 2.f));
}
