#include "pch.h"
#include "CBullet04.h"

CBullet04::CBullet04()
{}

CBullet04::~CBullet04()
{
	CBullet04::Release();
}

void CBullet04::Initialize()
{
	__super::Initialize();

	m_fDamage = 2.f;
}

int CBullet04::Update()
{
	const int iResult = __super::Update();

	return iResult;
}

void CBullet04::Late_Update()
{
	__super::Late_Update();
}

void CBullet04::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CBullet04::Release()
{}

void CBullet04::On_Collision(CObject* pObj)
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

void CBullet04::Do_Attack()
{
	__super::Do_Attack();
}

void CBullet04::Take_Damage(float _fDamage)
{
	__super::Take_Damage(_fDamage);
}
