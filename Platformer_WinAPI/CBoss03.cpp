#include "pch.h"
#include "CBoss03.h"

#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CBullet02_Boss03.h"
#include "CBullet_Boss03.h"
#include "CObjectManager.h"
#include "CUIManager.h"

CBoss03::CBoss03() : m_Attack_Interval(GetTickCount64()), m_Attack1(GetTickCount64())
{

}

CBoss03::~CBoss03()
{

}

void CBoss03::Initialize()
{
	CMonster::Initialize();

	//m_vPosition = { WINCX - 150, WINCY - ((WINCY >> 2) + 100) };
	//m_vDirection = { 0.f, 0.f };
	m_vSize = { 250.f, 300.f };

	m_fSpeedX = 10.f;
	m_fSpeedY = 7.f;

	// TODO : 보스 타입을 몬스터와 분리할지
	//m_objID = BOSS ?
	m_objID = MONSTER;

	// Boss Status
	m_fMaxHP = 100.f;
	m_fHP = m_fMaxHP;

	m_fDamage = 10.f;
}

int CBoss03::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	// Idle -> 2초마다 일단 패턴 변경
	ULONGLONG current = GetTickCount64();

	switch (m_pattern)
	{
	case BOSS_STATE::Idle:
		if (current - m_Attack_Interval >= 2000)
			Do_Attack();
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

	return CMonster::Update();
}

void CBoss03::Late_Update()
{
	CMonster::Late_Update();

}

void CBoss03::Render(HDC hDC)
{
	CMonster::Render(hDC);

	// TODO : 이미지로 변경
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

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

	//int random = 1 + rand() % static_cast<int>(BOSS_STATE::None);
	//m_pattern = static_cast<BOSS_STATE>(random);
	
	//m_pattern = static_cast<BOSS_STATE>(random);
	m_pattern = BOSS_STATE::Attack2;

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
	}

}

void CBoss03::Attack1()
{
	ULONGLONG current = GetTickCount64();

	// 5초뒤에 Idle로 전환
	if (current - m_Attack_Interval >= 5000)
	{
		m_pattern = BOSS_STATE::Idle;
		m_Attack_Interval = current;

		return;
	}

	if (current - m_Attack1 >= 100)
	{
		Vector2 dir;
		dir.x = CObjectManager::Get_Instance()->Get_Player()->Get_Position().x - m_vPosition.x;
		dir.y = CObjectManager::Get_Instance()->Get_Player()->Get_Position().y - m_vPosition.y;
		dir = Vector2::Nomalize(dir);

		CObjectManager::Get_Instance()->Add_Object(
			MON_BULLET, CAbstractFactory<CBullet_Boss03>::Create(MON_BULLET, m_vPosition, dir));

		m_Attack1 = current;
	}
}

void CBoss03::Attack2()
{
	ULONGLONG current = GetTickCount64();

	CUtility::PrintCmd(L"Attack Count : ", m_Attack_Count);

	if (m_Attack_Count > 5)
	{
		m_pattern = BOSS_STATE::Idle;
		m_Attack_Interval = current;

		m_Attack_Count = 0;
	
		return;
	}

	if (current - m_Attack1 >= 1000)
	{
		m_Attack_Count++;

		Vector2 startPos;
		startPos.x = m_vPosition.x;
		startPos.y = m_vPosition.y - 250;

		Vector2 dir;
		dir.x = CObjectManager::Get_Instance()->Get_Player()->Get_Position().x - startPos.x;
		dir.y = CObjectManager::Get_Instance()->Get_Player()->Get_Position().y - startPos.y;
		dir = Vector2::Nomalize(dir);

			CObjectManager::Get_Instance()->Add_Object(
			MON_BULLET, CAbstractFactory<CBullet02_Boss03>::Create(MON_BULLET, startPos, dir));

		m_Attack1 = current;
	}
}

void CBoss03::Attack3()
{
	// 실드 ? 
}
