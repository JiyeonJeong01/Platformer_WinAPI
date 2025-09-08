#include "pch.h"
#include "CBoss04.h"
#include "CAbstractFactory.h"
#include "CBullet04.h"
#include "CBullet_BossAtk01.h"

CBoss04::CBoss04()
	: m_eBossState(BOSS04_STATE::IDLE), m_fBossAtkTimer(0.f), m_bTalk_Idle(false)
{}

CBoss04::~CBoss04()
{
	CBoss04::Release();
}

void CBoss04::Initialize()
{
	m_vPosition  = { WINCX - 150, WINCY - ((WINCY >> 2) + 100) };
	m_vDirection = { 0.f, 0.f };
	m_vSize      = { 120.f, 120.f };

	m_fSpeedX = 10.f;
	m_fSpeedY = 7.f;

	// TODO : 보스 타입을 몬스터와 분리할지
	//m_objID = BOSS ?
	m_objID = MONSTER;

	// Boss Status
	m_fMaxHP = 100.f;
	m_fHP    = m_fMaxHP;

	m_fDamage = 10.f;
}

int CBoss04::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (CObjectManager::Get_Instance()->Get_Player() == nullptr)
		m_eBossState = BOSS04_STATE::IDLE;

	// 보스 공격 구현
	ULONGLONG qwTimer = GetTickCount64();

	if (qwTimer - m_fBossAtkTimer >= 1000)
	{
		switch (m_eBossState)
		{
		case BOSS04_STATE::IDLE:
		{
			m_bTalk_Idle = true;

			m_eBossState = BOSS04_STATE::ATTACK_01;
		}
		break;
		case BOSS04_STATE::ATTACK_01:
		{
			m_bTalk_Idle = false;

			CBoss04::Attack01();

			m_eBossState = BOSS04_STATE::IDLE;
		}
		break;
		case BOSS04_STATE::ATTACK_02:
			break;
		case BOSS04_STATE::NONE:
			break;
		default:
			break;
		}

		m_fBossAtkTimer = static_cast<float>(qwTimer);
	}

	return CMonster::Update();
}

void CBoss04::Late_Update()
{
	__super::Update_Rect();
}

void CBoss04::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	CUIManager::Get_Instance()->Render_BossHP(hDC, this);

	//CUtility::PrintText(hDC, 100, 200,
	//					L"BossState : ", static_cast<int>(m_eBossState));

	if (m_bTalk_Idle)
	{
		CUtility::PrintText(hDC, 100, 250,
							L"안녕? ", static_cast<int>(m_eBossState));
	}
}

void CBoss04::Release()
{}

void CBoss04::On_Collision(CObject* pObj)
{
	switch (pObj->Get_ObjectID())
	{
	case PL_BULLET:
	{
		CBoss04::Take_Damage(pObj->Get_Damage());
	}
	break;
	case PLATFORM:
	{
		//todo 착지 판정
	}
	break;
	default:
		break;
	}
}

void CBoss04::Take_Damage(float _fDamage)
{
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

//! 플레이어 방향으로 가속하는 총알 3발 흩뿌리기
void CBoss04::Attack01()
{
	Vector2 vPlayer_Dir;

	vPlayer_Dir.x = CObjectManager::Get_Instance()
					->Get_Player()->Get_Position().x - m_vPosition.x;
	vPlayer_Dir.y = CObjectManager::Get_Instance()
					->Get_Player()->Get_Position().y - m_vPosition.y;
	vPlayer_Dir = Vector2::Nomalize(vPlayer_Dir);

	Vector2 vPlayer_Dir_OffsetUp   = { vPlayer_Dir.x - 0.1f, vPlayer_Dir.y - 0.1f };
	vPlayer_Dir_OffsetUp           = Vector2::Nomalize(vPlayer_Dir_OffsetUp);
	Vector2 vPlayer_Dir_OffsetDown = { vPlayer_Dir.x + 0.1f, vPlayer_Dir.y + 0.1f };
	vPlayer_Dir_OffsetDown         = Vector2::Nomalize(vPlayer_Dir_OffsetDown);

	CObjectManager::Get_Instance()->Add_Object(
		MON_BULLET, CAbstractFactory<CBullet_BossAtk01>::Create(
			MON_BULLET, m_vPosition, vPlayer_Dir));

	CObjectManager::Get_Instance()->Add_Object(
		MON_BULLET, CAbstractFactory<CBullet_BossAtk01>::Create(
			MON_BULLET, m_vPosition, vPlayer_Dir_OffsetUp));

	CObjectManager::Get_Instance()->Add_Object(
		MON_BULLET, CAbstractFactory<CBullet_BossAtk01>::Create(
			MON_BULLET, m_vPosition, vPlayer_Dir_OffsetDown));
}

void CBoss04::Attack02()
{ }
