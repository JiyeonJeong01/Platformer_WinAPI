#include "pch.h"
#include "CBoss01.h"

#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CStageManager.h"
#include "CUIManager.h"

CBoss01::CBoss01()
{
}

CBoss01::~CBoss01()
{
}

void CBoss01::Initialize()
{
	m_objID = MONSTER;

	m_vPosition = { 1000.f, 400.f };
	m_vSize = { 70.f, 70.f };
	m_vDirection = { 1.f, 0.f };

	m_fSpeedX = 1.f;

	llElapsedTime = GetTickCount64();

	iStateIndex = 0;
	iTotalState = 3;
	iLastDirection = -1;
	fShotTime = 0.5f;

	m_fMaxHP = 80.f;
	m_fHP = m_fMaxHP;

	currentState = &CBoss01::Idle_State;
}

int CBoss01::Update()
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

void CBoss01::Late_Update()
{
}

void CBoss01::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	CUIManager::Get_Instance()->Render_BossHP(hDC, this);


}

void CBoss01::Release()
{
}

void CBoss01::On_Collision(CObject* pObj)
{
	OBJID objID = pObj->Get_ObjectID();

	if (objID == PL_BULLET)
	{
		Take_Damage(pObj->Get_Damage());
	}
}

void CBoss01::Take_Damage(float _fDamage)
{
	m_fHP -= _fDamage;

	if (m_fHP <= 0)
	{
		m_bDead = true;
		CStageManager::Get_Instance()->On_CurrentBossDead(this);
	}

}

void CBoss01::Do_Attack()
{
	float fTargetX = pTarget->Get_Position().x;
	float fTargetY = pTarget->Get_Position().y;

	float fDistX = m_vPosition.x - fTargetX;
	float fDistY = m_vPosition.y - fTargetY;

	Vector2 bulletDir = Vector2::Nomalize({ -fDistX, -fDistY });

	CObject* pObj = CAbstractFactory<CBullet>::Create(MON_BULLET, m_vPosition, bulletDir);
	CObjectManager::Get_Instance()->Add_Object(MON_BULLET, pObj);
}

void CBoss01::Decide_State()
{
	if (llElapsedTime + fTransitTime * 1000 < GetTickCount64())
	{
		llElapsedTime = GetTickCount64();

		iStateIndex = (iStateIndex + 1) % (iTotalState );

		switch (iStateIndex)
		{
		case 0:
			currentState = &CBoss01::Idle_State;
			break;
		case 1:
			iLastDirection *= -1;
			currentState = &CBoss01::Move_State;
			break;
		case 2: default :
			currentState = &CBoss01::Attack_State;
			break;
		}
	}
}

void CBoss01::Idle_State()
{

}

void CBoss01::Attack_State()
{
	Do_Attack();
}

void CBoss01::Move_State()
{
	m_vDirection.x = iLastDirection;
	m_vDirection= Vector2::Nomalize(m_vDirection);

	m_vPosition += m_vDirection * m_fSpeedX;
}
