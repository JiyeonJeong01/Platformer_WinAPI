#include "pch.h"
#include "CObject.h"

CObject::CObject()
	: m_objID(OBJ_END),
	m_tRect({ 0, 0, 0, 0 }),
	m_fSpeedX(0.f), m_fSpeedY(0.f),
	m_bDead(false), m_fHP(0.f), m_fMaxHP(0.f), m_fDamage(0.f),
	m_qwDTTimer(GetTickCount64()), m_fDeltaTime(0.f)
{
}

CObject::~CObject()
{
}

void CObject::Update_Rect()
{
	float iScrollX = CScrollManager::Get_Instance()->Get_ScrollX();
	float iScrollY = CScrollManager::Get_Instance()->Get_ScrollY();

	m_tRect.left = static_cast<LONG>(m_vPosition.x   + iScrollX - (m_vSize.x / 2.f));
	m_tRect.top = static_cast<LONG>(m_vPosition.y    + iScrollY - (m_vSize.y / 2.f));
	m_tRect.right = static_cast<LONG>(m_vPosition.x  + iScrollX + (m_vSize.x / 2.f));
	m_tRect.bottom = static_cast<LONG>(m_vPosition.y + iScrollY + (m_vSize.y / 2.f));
}

float CObject::DeltaTime()
{
	ULONGLONG qwCurrentTime = GetTickCount64();
	ULONGLONG qwTimeDiff = qwCurrentTime - m_qwDTTimer;
	m_qwDTTimer = qwCurrentTime;

	float fDeltaTime = static_cast<float>(qwTimeDiff) * 0.001f;

	return fDeltaTime;
}

