#include "pch.h"
#include "CShield.h"

CShield::CShield() : pTarget(nullptr)
{

}

CShield::~CShield()
{

}

void CShield::Initialize()
{
	m_vPosition = { 0.f, 0.f };
	m_vSize = { 400,400 };

	m_fMaxHP = 30.f;
	m_fHP = m_fMaxHP;

}

int CShield::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CShield::Late_Update()
{

}

void CShield::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release()
{

}
