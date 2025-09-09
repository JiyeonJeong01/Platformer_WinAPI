#include "pch.h"
#include "CBullet_Player03.h"

CBullet_Player03::CBullet_Player03()
{
}

CBullet_Player03::~CBullet_Player03()
{
}

void CBullet_Player03::Initialize()
{
	CBullet::Initialize();

	m_fSpeedX = 10.f;
	m_fSpeedY = 10.f;
}

int CBullet_Player03::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	return CBullet::Update();
}

void CBullet_Player03::Late_Update()
{
	CBullet::Late_Update();
}

void CBullet_Player03::Render(HDC hDC)
{
	CBullet::Render(hDC);
}

void CBullet_Player03::Release()
{
	CBullet::Release();
}

void CBullet_Player03::On_Collision(CObject* pObj)
{
	CBullet::On_Collision(pObj);
}

void CBullet_Player03::Do_Attack()
{
	CBullet::Do_Attack();
}

void CBullet_Player03::Take_Damage(float _fDamage)
{
	CBullet::Take_Damage(_fDamage);
}
