#include "pch.h"
#include "CPlayer04.h"

CPlayer04::CPlayer04()
{ }

CPlayer04::~CPlayer04()
{
	CPlayer04::Release();
}

void CPlayer04::Initialize()
{
	m_vPosition  = { WINCX >> 3, WINCY - (WINCY >> 2) };
	m_vDirection = { 0.f, 0.f };
	m_vSize      = { 40.f, 40.f };

	m_fSpeedX = 10.f;
	m_fSpeedY = 7.f;

	m_objID = PLAYER;

	m_fMaxHP = 100.f;
	m_fHP    = m_fMaxHP;

	m_fDamage = 1.f;
}

int CPlayer04::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	CObject::Update_Rect();

	// Process client's inputs
	CPlayer::Handle_KeyInput();

	// Apply inputs to player's state
	CPlayer04::Update_Components();

	if (bLeftMouseClicked)
		CPlayer::Do_Attack();

	return OBJ_NOEVENT;
}

void CPlayer04::Late_Update()
{
	CPlayer::Late_Update();
}

void CPlayer04::Render(HDC hDC)
{
	CPlayer::Render(hDC);
}

void CPlayer04::Release()
{ }

void CPlayer04::Do_Attack()
{
	CPlayer::Do_Attack();
}

void CPlayer04::Take_Damage(float _fDamage)
{
	CPlayer::Take_Damage(_fDamage);
	//! Take_Damage : 현재 구현 안되어 있음
}

void CPlayer04::Update_Components()
{
	float fPosX = 0.f, fPosY = 0.f, fDirX = 0.f, fDirY = 0.f;

	// Update player's direction

	if (bLeftPressed)			// 좌로 이동
	{
		if (bJumpPressed)			// 하면서 점프
		{
			m_vDirection.x = -1.f;
			m_vDirection.y = -1.f;
		}
		else
		{
			m_vDirection.x = -1.f;
			m_vDirection.y = 0.f;
		}
	}
	else if (bRightPressed)		// 우로 이동
	{
		if (bJumpPressed)			// 하면서 점프
		{
			m_vDirection.x = 1.f;
			m_vDirection.y = -1.f;
		}
		else
		{
			m_vDirection.x = 1.f;
			m_vDirection.y = 0.f;
		}
	}
	else if (bJumpPressed)		// 점프만
	{
		m_vDirection.x = 0.f;
		m_vDirection.y = -1.f;
	}

	m_vDirection = m_vDirection.GetNomalized();

	m_vPosition.x += m_vDirection.x * m_fSpeedX;
	m_vPosition.y += m_vDirection.y * m_fSpeedY;

}

void CPlayer04::Jump()
{}
