#include "pch.h"
#include "CMob03.h"

#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CStageManager.h"
#include "CUIManager.h"

CMob03::CMob03()
{
}

CMob03::~CMob03()
{
}

void CMob03::Initialize()
{
	m_objID = MONSTER;

	m_vPosition = { 500.f, 400.f };
	m_vSize = { 40.f, 40.f };
	m_vDirection = { 1.f, 0.f };

	m_fSpeedX = 0.4f;

	llElapsedTime = GetTickCount64();
	fIdleElapsedTime = GetTickCount64();

	iStateIndex = 0;
	iTotalState = 3;
	iLastDirection = -1;

	fShotTime = 1.2f;
	fShotTimeLog = 0;

	m_fMaxHP = 30.f;
	m_fHP = m_fMaxHP;

	m_fDamage = 5.f;

	currentState = &CMob03::Move_State;
}

int CMob03::Update()
{
	if (CMonster::Update() == OBJ_DEAD)
	{
		m_bDead = true;
		return OBJ_DEAD;
	}

	Decide_State();

	(this->*currentState)();

	return 0;
}

void CMob03::Late_Update()
{
}

void CMob03::Render(HDC hDC)
{
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		int iScrollX = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollX());
		int iScrollY = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollY());

		CUIManager::Get_Instance()->DrawHP(
			hDC, 
			(m_vPosition.x + iScrollX - m_vSize.x * .5f),
			(m_vPosition.y + iScrollY + m_vSize.y * .5f) + 10, 
			m_vSize.x, 5, m_fHP, m_fMaxHP);

}

void CMob03::Release()
{
}

void CMob03::On_Collision(CObject* pObj)
{
	OBJID objID = pObj->Get_ObjectID();

	if (objID == PL_BULLET)
	{
		Take_Damage(pObj->Get_Damage());
	}
}

void CMob03::Take_Damage(float _fDamage)
{
	m_fHP -= _fDamage;

	if (m_fHP <= 0)
	{
		m_bDead = true;

		CStageManager::Get_Instance()->On_MobDead(this);
	}
}

void CMob03::Do_Attack()
{
	float fTargetX = pTarget->Get_Position().x;
	float fTargetY = pTarget->Get_Position().y;

	float fDistX = m_vPosition.x - fTargetX;
	float fDistY = m_vPosition.y - fTargetY;

	Vector2 bulletDir = Vector2::Nomalize({ -fDistX, -fDistY });

	CObject* pObj = CAbstractFactory<CBullet>::Create(MON_BULLET, m_vPosition, bulletDir);
	pObj->Set_Damage(5.f);
	CObjectManager::Get_Instance()->Add_Object(MON_BULLET, pObj);
}

void CMob03::Decide_State()
{
	if (llElapsedTime + fTransitTime * 1000 < GetTickCount64())
	{
		llElapsedTime = GetTickCount64();

		iStateIndex = (iStateIndex + 1) % (iTotalState);

		switch (iStateIndex)
		{
		case 2:
			fIdleElapsedTime = GetTickCount64();
			currentState = &CMob03::Idle_State;
			break;
		case 0:
			iLastDirection *= -1;
			currentState = &CMob03::Move_State;
			break;
		case 1: default:
			currentState = &CMob03::Attack_State;
			break;
		}
	}
}

void CMob03::Idle_State()
{
	if (fIdleElapsedTime + fTransitTime * 500 < GetTickCount64())
	{
		m_vSize.x -= 0.05f;
		// _tprintf(_T("1: %d - %d\n"), (fIdleElapsedTime + fTransitTime * 500), GetTickCount64());
	}
	else
	{
		m_vSize.x += 0.05f;
		// _tprintf(_T("2: %d - %d\n"), (fIdleElapsedTime + fTransitTime * 500), GetTickCount64());
	}
}

void CMob03::Attack_State()
{
	if (fShotTimeLog + fShotTime * 1000 < GetTickCount64())
	{
		Do_Attack();
		fShotTimeLog = GetTickCount64();
	}
}

void CMob03::Move_State()
{
	m_vDirection.x = iLastDirection;
	m_vDirection = Vector2::Nomalize(m_vDirection);

	m_vPosition += m_vDirection * m_fSpeedX;
}