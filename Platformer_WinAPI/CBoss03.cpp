#include "pch.h"
#include "CBoss03.h"

#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CBullet02_Boss03.h"
#include "CBullet03_Boss03.h"
#include "CBullet_Boss03.h"
#include "CObjectManager.h"
#include "CUIManager.h"

CBoss03::CBoss03()
{

}

CBoss03::~CBoss03()
{

}

void CBoss03::Initialize()
{
	CMonster::Initialize();
	
	m_vSize = { 90.f, 90.f };

	m_fSpeedX = 10.f;
	m_fSpeedY = 7.f;

	m_objID = MONSTER;

	// Boss Status
	m_fMaxHP = 100.f;
	m_fHP = m_fMaxHP;

	m_fDamage = 10.f;

	m_PatternTimers[BOSS_STATE::Idle] = 0.f;
	m_PatternTimers[BOSS_STATE::Attack1] = 0.f;
	m_PatternTimers[BOSS_STATE::Attack2] = 0.f;
	m_PatternTimers[BOSS_STATE::Attack3] = 0.f;

}

int CBoss03::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;

	float delta = DeltaTime();          
	m_fDeltaTime = delta;

	m_PatternTimers[m_pattern] += delta;

	switch (m_pattern)
	{
	case BOSS_STATE::Idle:
		if (m_PatternTimers[BOSS_STATE::Idle] > 2.0f)
		{
			Do_Attack();
		}
		break;
	case BOSS_STATE::Attack1:
		Attack1();
		break;
	case BOSS_STATE::Attack2:
		Attack2();
		break;
	case BOSS_STATE::Attack3:
		Attack3();
		break;
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}


void CBoss03::Late_Update()
{
	CMonster::Late_Update();

}

void CBoss03::Render(HDC hDC)
{
	CMonster::Render(hDC);

	HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Boss03");

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_vSize.x,
		(int)m_vSize.y,
		hMemDC,
		0,
		0,
		(int)m_vSize.x,
		(int)m_vSize.y,
		RGB(255, 255, 255));


	CUIManager::Get_Instance()->Render_BossHP(hDC, this);

	int attackType = static_cast<int>(m_pattern);
	CUtility::PrintText(hDC, 1080, 120, L"공격 타입 : ", attackType);

}

void CBoss03::Release()
{
	CMonster::Release();

}

void CBoss03::On_Collision(CObject* pObj)
{
	CMonster::On_Collision(pObj);

	if (pObj == nullptr)
		return;

	Take_Damage(pObj->Get_Damage());
}

void CBoss03::Do_Attack()
{
	CMonster::Do_Attack();

	if (CObjectManager::Get_Instance()->Get_Player() == nullptr)
		return;

	// 랜덤으로 했다가 그냥 하나씩 증가로 변경
	m_nextIndex = (m_nextIndex + 1) % 4;
	m_pattern = static_cast<BOSS_STATE>(m_nextIndex);


	for (auto& time : m_PatternTimers) 
	{
		time.second = 0.f;
	}
}

void CBoss03::Take_Damage(float _fDamage)
{
	CMonster::Take_Damage(_fDamage);

	if (m_fHP - _fDamage > 0.f)
	{
		Set_HP(m_fHP - _fDamage);
	}
	else
	{
		Set_HP(0.f);
		m_bDead = true;
		CStageManager::Get_Instance()->On_CurrentBossDead(this);
	}

}

void CBoss03::Attack1()
{
	if (m_PatternTimers[BOSS_STATE::Attack1] >= 5.0f)
	{
		m_pattern = BOSS_STATE::Idle;
		m_PatternTimers[BOSS_STATE::Idle] = 0.f;
		return;
	}

	m_Attack1_Timer += m_fDeltaTime;

	if (m_Attack1_Timer >= 0.1f)
	{
		Vector2 dir;
		dir.x = CObjectManager::Get_Instance()->Get_Player()->Get_Position().x - m_vPosition.x;
		dir.y = CObjectManager::Get_Instance()->Get_Player()->Get_Position().y - m_vPosition.y;
		dir = Vector2::Nomalize(dir);

		CObjectManager::Get_Instance()->Add_Object(
			MON_BULLET, CAbstractFactory<CBullet_Boss03>::Create(MON_BULLET, m_vPosition, dir));

		m_Attack1_Timer = 0.f;
	}

}

void CBoss03::Attack2()
{
	if (m_PatternTimers[BOSS_STATE::Attack2] >= 5.0f)
	{
		m_pattern = BOSS_STATE::Idle;
		m_PatternTimers[BOSS_STATE::Idle] = 0.f;
		return;
	}

	m_Attack2_Timer += m_fDeltaTime;

	if (m_Attack2_Timer >= 0.5f)
	{
		Vector2 startPos;
		startPos.x = m_vPosition.x;
		startPos.y = m_vPosition.y - 250;

		Vector2 dir;
		dir.x = CObjectManager::Get_Instance()->Get_Player()->Get_Position().x - startPos.x;
		dir.y = CObjectManager::Get_Instance()->Get_Player()->Get_Position().y - startPos.y;
		dir = Vector2::Nomalize(dir);

		CObjectManager::Get_Instance()->Add_Object(
		MON_BULLET, CAbstractFactory<CBullet02_Boss03>::Create(MON_BULLET, startPos, dir));

		m_Attack2_Timer = 0.0f;
	}
}

void CBoss03::Attack3()
{
	if (m_PatternTimers[BOSS_STATE::Attack3] >= 6.0f) {
		m_pattern = BOSS_STATE::Idle;
		m_PatternTimers[BOSS_STATE::Idle] = 0.f;
		return;
	}

	m_Attack3_Timer += m_fDeltaTime;

	if (m_Attack3_Timer >= 1.5f)
	{	
		CObjectManager::Get_Instance()->Add_Object(
			MON_BULLET, CAbstractFactory<CBullet03_Boss03>::Create(MON_BULLET, m_vPosition, true));

		m_Attack3_Timer = 0.f;
	}

	
}
