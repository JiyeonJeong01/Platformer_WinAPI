#include "pch.h"
#include "CBullet_BossAtk01.h"

CBullet_BossAtk01::CBullet_BossAtk01()
{}

CBullet_BossAtk01::~CBullet_BossAtk01()
{
	CBullet_BossAtk01::Release();
}

void CBullet_BossAtk01::Initialize()
{
	__super::Initialize();

	m_fSpeedX = 0.5f;
	m_fSpeedY = 0.5f;

	m_fDamage = 10.f;
}

int CBullet_BossAtk01::Update()
{
	const int iResult = __super::Update();

	// 가속 기능
	m_fSpeedX += 1.0f;
	m_fSpeedY += 1.0f;

	return iResult;
}

void CBullet_BossAtk01::Late_Update()
{
	__super::Late_Update();
}

void CBullet_BossAtk01::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CBullet_BossAtk01::Release()
{}

void CBullet_BossAtk01::On_Collision(CObject* pObj)
{
	//! 플랫폼 충돌 테스트. CBullet::On_Collision 여기선 안쓰는중

	switch (pObj->Get_ObjectID())
	{
	case PLAYER:
	{
		if (m_objID == MON_BULLET)
			m_bDead = true;
	}
	break;
	case MONSTER:
	{
		if (m_objID == PL_BULLET)
			m_bDead = true;
	}
	break;
	case PLATFORM:
	{
		m_bDead = true;
	}
	break;
	default:
		break;
	}
}

void CBullet_BossAtk01::Do_Attack()
{
	__super::Do_Attack();
}

void CBullet_BossAtk01::Take_Damage(float _fDamage)
{
	__super::Take_Damage(_fDamage);
}
