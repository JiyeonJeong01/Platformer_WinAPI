#include "pch.h"
#include "CPlayer01.h"

void CPlayer01::Initialize()
{
	CPlayer::Initialize();
	
	// Player's position can change based on map environments
}

int CPlayer01::Update()
{
	return CPlayer::Update();
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
