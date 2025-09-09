#include "pch.h"
#include "CBullet_BossAtk03.h"

CBullet_BossAtk03::CBullet_BossAtk03()
{}

CBullet_BossAtk03::~CBullet_BossAtk03()
{
	CBullet_BossAtk03::Release();
}

void CBullet_BossAtk03::Initialize()
{
	__super::Initialize();

	m_fSpeedY = -2000.0f;

	m_fDamage = 5.f;

	const int iPattern = rand() % 6;
	switch (iPattern)
	{
	case 0:
		m_fSpeedX = 200.0f;
		break;
	case 1:
		m_fSpeedX = 400.0f;
		break;
	case 2:
		m_fSpeedX = 600.0f;
		break;
	case 3:
		m_fSpeedX = 800.0f;
		break;
	case 4:
		m_fSpeedX = 1000.0f;
		break;
	case 5:
		m_fSpeedX = 1200.0f;
		break;
	default:
		break;
	}
}

int CBullet_BossAtk03::Update()
{
	const int iResult = __super::Update();

	if (iResult == OBJ_DEAD)
	{
		return iResult;
	}

	// 낙하속도 상한 설정
	if (m_fSpeedY > 600.f)
		m_fSpeedY = 600.f;

	// 델타타임 사용을 위해 포함할 것
	m_fDeltaTime = CObject::DeltaTime();

	// 수평방향 이동
	m_vPosition.x += m_vDirection.x * m_fSpeedX * m_fDeltaTime;

	// 수직방향 이동
	m_fSpeedY += 4000.f * m_fDeltaTime;
	m_vPosition.y += m_fSpeedY * m_fDeltaTime;

	return iResult;
}

void CBullet_BossAtk03::Late_Update()
{
	__super::Update_Rect();
}

void CBullet_BossAtk03::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CBullet_BossAtk03::Release()
{}

void CBullet_BossAtk03::On_Collision(CObject* pObj)
{
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

	__super::Update_Rect();
}

void CBullet_BossAtk03::Do_Attack()
{
	__super::Do_Attack();
}

void CBullet_BossAtk03::Take_Damage(float _fDamage)
{
	__super::Take_Damage(_fDamage);
}
