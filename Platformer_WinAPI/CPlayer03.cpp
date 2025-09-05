#include "pch.h"
#include "CPlayer03.h"

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

	// for test
	//if (bLeftMouseClicked)
	//{
	//	Rectangle(hDC, m_fMousePosX - 10, m_fMousePosY - 10, m_fMousePosX + 10, m_fMousePosY + 10);
	//}
}

void CPlayer03::Release()
{
	CPlayer::Release();
}

void CPlayer03::On_Collision(CObject* pObj)
{
	CPlayer::On_Collision(pObj);
}

void CPlayer03::Do_Attack()
{
	CPlayer::Do_Attack();
}

void CPlayer03::Take_Damage(float _fDamage)
{
	CPlayer::Take_Damage(_fDamage);
}
