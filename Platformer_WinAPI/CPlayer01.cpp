#include "pch.h"
#include "CPlayer01.h"

#include "CUIManager.h"

void CPlayer01::Initialize()
{
	CPlayer::Initialize();
	m_objID = PLAYER;

	// Player's position can change based on map environments
	m_fMaxHP = 70.f;
	m_fHP = m_fMaxHP;
	m_vPosition = { 100, 400 };
}

int CPlayer01::Update()
{
	return CPlayer::Update();
}

void CPlayer01::Render(HDC hDC)
{
	CPlayer::Render(hDC);
	CUIManager::Get_Instance()->Render_PlayerHP(hDC, this);
}

void CPlayer01::Do_Attack()
{
	CPlayer::Do_Attack();
}

void CPlayer01::Take_Damage(float _fDamage)
{
	m_fHP -= _fDamage;

	if (m_fHP <= 0.f)
	{
		m_fHP = 0.f;
		m_bDead = true;
	}
}
