#include "pch.h"
#include "CPlayer02.h"
#include "CInputManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CLineManager.h"
#include "CUIManager.h"
CPlayer02::CPlayer02() : sz_Time(GetTickCount())
{

}

CPlayer02::~CPlayer02()
{
	Release();
}

void CPlayer02::Initialize()
{

	CPlayer::Initialize();

	m_vPosition = { 30.f, WINCY * 0.8 };
	m_vSize = { 50.f, 50.f };
	m_vDirection = { 0.f,0.f };

	m_fSpeedX = 300.f;
	m_fSpeedY = 0.f;

	m_vPosinPosition = { 1,1 };

	m_fHP = 1000;
	m_fMaxHP = m_fHP;

	__super::Update_Rect();
}

int CPlayer02::Update()
{
	CPlayer::Update();

	if (m_bDead)
		return OBJ_DEAD;


	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CPlayer02::Late_Update()
{
	CPlayer::Late_Update();

}

void CPlayer02::Render(HDC hDC)
{
	CPlayer::Render(hDC);

	CUIManager::Get_Instance()->Render_PlayerHP(hDC, this);

}

void CPlayer02::Release()
{
	CPlayer::Release();
}

void CPlayer02::Do_Attack()
{
	//CPlayer::Do_Attack();

	Vector2 dir = Vector2::Nomalize(m_mouseDir);
	Vector2 barrel = m_vPosition + dir * 50.f;

	CObjectManager::Get_Instance()->Add_Object(PL_BULLET, CAbstractFactory<CBullet>::Create(PL_BULLET, barrel, dir));
}

void CPlayer02::Take_Damage(float _fDamage)
{

	if (sz_Time + 1000 < GetTickCount())
	{

			if (0 < (m_fHP - _fDamage))
		m_fHP -= _fDamage;

	else
	{
		m_fHP = 0.f;
		m_bDead = true;
	}

	
		sz_Time = GetTickCount();
	}
}

void CPlayer02::On_Collision(CObject* pObj)
{

	__super::On_Collision(pObj);


	if (pObj->Get_ObjectID() == MON_BULLET)
		Take_Damage(pObj->Get_Damage());

		

}

