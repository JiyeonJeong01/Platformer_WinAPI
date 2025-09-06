#include "pch.h"
#include "CObject.h"

CObject::CObject() 
	: m_fSpeedX(0.f), m_fSpeedY(0.f), m_bDead(false), m_tRect({0, 0, 0, 0}), m_objID(OBJ_END) { }

CObject::~CObject() { }

void CObject::Update_Rect()
{
	m_tRect.left  = static_cast<long>(m_vPosition.x - (m_vSize.x / 2.f));
	m_tRect.top   = static_cast<long>(m_vPosition.y - (m_vSize.y / 2.f));
	m_tRect.right = static_cast<long>(m_vPosition.x + (m_vSize.x / 2.f));
	m_tRect.bottom = static_cast<long>(m_vPosition.y + (m_vSize.y / 2.f));
}