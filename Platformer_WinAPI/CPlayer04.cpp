#include "pch.h"
#include "CPlayer04.h"

CPlayer04::CPlayer04()
{ }

CPlayer04::~CPlayer04()
{ }

void CPlayer04::Initialize()
{
	CPlayer::Initialize();
}

int CPlayer04::Update()
{
	return CPlayer::Update();
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
{
	CPlayer::Release();
}

void CPlayer04::On_Collision(CObject* pObj)
{
	CPlayer::On_Collision(pObj);
}

void CPlayer04::Do_Attack()
{
	CPlayer::Do_Attack();
}

void CPlayer04::Take_Damage(float _fDamage)
{
	CPlayer::Take_Damage(_fDamage);
}

void CPlayer04::Update_Components()
{
	CPlayer::Update_Components();
}
