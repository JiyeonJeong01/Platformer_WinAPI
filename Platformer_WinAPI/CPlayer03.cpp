#include "pch.h"
#include "CPlayer03.h"

#include "CUIManager.h"

CPlayer03::CPlayer03()
{
	
}

CPlayer03::~CPlayer03()
{
	Release();
}

void CPlayer03::Initialize()
{
	CPlayer::Initialize();

	m_fMaxHP = 100.f;
	m_fHP = m_fMaxHP;
}


int CPlayer03::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return CPlayer::Update();
}

void CPlayer03::Late_Update()
{
	CPlayer::Late_Update();


}

void CPlayer03::Render(HDC hDC)
{
	CPlayer::Render(hDC);

	CUIManager::Get_Instance()->Render_PlayerHP(hDC, this);
}

void CPlayer03::Release()
{
	CPlayer::Release();
}

void CPlayer03::On_Collision(CObject* pObj)
{
	CPlayer::On_Collision(pObj);

	Take_Damage(pObj->Get_Damage());
}

void CPlayer03::Do_Attack()
{
	CPlayer::Do_Attack();


}

void CPlayer03::Take_Damage(float _fDamage)
{
	CPlayer::Take_Damage(_fDamage);

	if (m_fHP - _fDamage > 0.f)
	{
		Set_HP(m_fHP - _fDamage);
	}
	else
	{
		Set_HP(0.f);
		m_bDead = true;
	}
}
