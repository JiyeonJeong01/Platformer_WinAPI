#include "pch.h"
#include "CBoss03.h"

CBoss03::CBoss03()
{

}

CBoss03::~CBoss03()
{

}

void CBoss03::Initialize()
{
	CMonster::Initialize();

	m_vPosition = { WINCX >> 3, WINCY - (WINCY >> 2) };
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

	return CMonster::Update();
}

void CBoss03::Late_Update()
{
	CMonster::Late_Update();

}

void CBoss03::Render(HDC hDC)
{
	CMonster::Render(hDC);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//CUtility::PrintText(hDC, 400, 50, L"보스 Hp : ", m_fHP);
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

	// 공격한 오브젝트의 공격력만큼 데미지 ? 
	Take_Damage(pObj->Get_Damage());
}

void CBoss03::Do_Attack()
{
	CMonster::Do_Attack();

}

void CBoss03::Take_Damage(float _fDamage)
{
	CMonster::Take_Damage(_fDamage);

	if (m_fHP >= 0.f)
	{
		Set_HP(m_fHP - _fDamage);
	}
	else
	{
		Set_HP(0.f);
		m_bDead = true;
	}

}
