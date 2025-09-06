#include "pch.h"
#include "CBoss03.h"

#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CObjectManager.h"
#include "CUIManager.h"

CBoss03::CBoss03() : m_Attack_Interval(GetTickCount64())
{

}

CBoss03::~CBoss03()
{

}

void CBoss03::Initialize()
{
	CMonster::Initialize();

	m_vPosition = { WINCX - 150, WINCY - ((WINCY >> 2) + 100) };
	m_vDirection = { 0.f, 0.f };
	m_vSize = { 120.f, 120.f };

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

	// 보스 공격 구현
	ULONGLONG current = GetTickCount64();

	if (current - m_Attack_Interval >= 1000)
	{
		if (m_pattern == BOSS_PATTERN::Idle)
		{
			Do_Attack();

			m_Attack_Interval = current;
		}
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
	CUtility::PrintText(hDC, 50, 240, L"공격 타입 : ", attackType);
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

	// Player의 데미지가 아니라, Bullet의 데미지로 계산 중 / Player의 Damage가 필요한가?
	Take_Damage(pObj->Get_Damage());
}

void CBoss03::Do_Attack()
{
	CMonster::Do_Attack();

	// TODO : 공격 패턴 여러개면 랜덤으로
	//int random = 1 + rand() % static_cast<int>(BOSS_PATTERN::None);
	//m_pattern = static_cast<BOSS_PATTERN>(random);

	m_pattern = BOSS_PATTERN::Attack;

	Vector2 dir;
	dir.x = CObjectManager::Get_Instance()->Get_Player()->Get_Position().x - m_vPosition.x;
	dir.y = CObjectManager::Get_Instance()->Get_Player()->Get_Position().y - m_vPosition.y;

	dir = Vector2::Nomalize(dir);

	//CObjectManager::Get_Instance()->Add_Object(MON_BULLET, CAbstractFactory<CBullet>::Create(Vector2(m_vPosition.x - 200, m_vPosition.y), dir));
	CObjectManager::Get_Instance()->Add_Object(MON_BULLET, CAbstractFactory<CBullet>::Create(m_vPosition, dir));

	// 대기 상태로
	if (m_pattern == BOSS_PATTERN::Attack)
		m_pattern = BOSS_PATTERN::Idle;
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
