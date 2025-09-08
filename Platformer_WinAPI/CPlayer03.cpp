#include "pch.h"
#include "CPlayer03.h"

#include "CAbstractFactory.h"
#include "CBullet_Player03.h"

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

	m_fDamage = 16.f;
}


int CPlayer03::Update()
{
	int result = CPlayer::Update();

	if (result == OBJ_DEAD)
		return OBJ_DEAD;




	return OBJ_NOEVENT;
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

}

void CPlayer03::Do_Attack()
{
	CPlayer::Do_Attack();

	//Vector2 dir = Vector2::Nomalize(m_mouseDir);
	//
	//Vector2 barrel;
	//barrel.x = m_vPosition.x + dir.x * 50.f;
	//barrel.y = m_vPosition.y + dir.y * 50.f;
	//
	//CObjectManager::Get_Instance()->Add_Object(PL_BULLET, CAbstractFactory<CBullet_Player03>::Create(MON_BULLET, barrel, dir));
}

void CPlayer03::Take_Damage(float _fDamage)
{
	CPlayer::Take_Damage(_fDamage);


}