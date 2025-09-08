#include "pch.h"
#include "CBoss04.h"
#include "CAbstractFactory.h"
#include "CBullet04.h"
#include "CBullet_BossAtk01.h"

CBoss04::CBoss04()
	: m_eBossState(BOSS04_STATE::IDLE), m_fBossAtkDelay(0.f), m_bCanAttack(false)
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

	m_fSpeedX = 0.f;
	m_fSpeedY = 0.f;

	// TODO : 보스 타입을 몬스터와 분리할지
	//m_objID = BOSS ?
	m_objID = MONSTER;

	// Boss Status
	m_fMaxHP = 100.f;
	m_fHP    = m_fMaxHP;

	m_fDamage = 10.f;

	m_bGravityOn = true;
}

int CBoss04::Update()
{
	int iResult = CMonster::Update();

	if (CObjectManager::Get_Instance()->Get_Player() == nullptr)
		m_eBossState = BOSS04_STATE::IDLE;

	// 낙하속도 상한 설정
	if (m_bGravityOn && m_fSpeedY > 1000.f)
		m_fSpeedY = 1000.f;

	//todo 점프 조건 만들기
	Jump();

	//todo 왼쪽으로 가는 조건 만들기
	//Left_Move();

	//todo 오른쪽으로 가는 조건 만들기
	//Right_Move();

	Vertical_Move();

	m_fGroundY = WINCY + 100.f;

	CLineManager::Get_Instance()->Collision_Line(m_vPosition, &m_fGroundY);

	Landed_Line();

	// 보스 내장 타이머
	m_fBossAtkDelay += m_fDeltaTime;

	// ↓ 콘솔로 원하는 값 보는 디버깅용 코드
	//_tprintf(_T(" m_fBossAtkTimer : %f \n"), m_fBossAtkTimer);

	if (m_fBossAtkDelay > 2.f)
	{
		switch (m_eBossState)
		{
		case BOSS04_STATE::IDLE:
		{
			//todo 랜덤 대사

			m_eBossState = BOSS04_STATE::ATTACK_01;
		}
		break;
		case BOSS04_STATE::ATTACK_01:
		{
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

		m_fBossAtkDelay = 0.f;
	}

	return iResult;
}

void CBoss04::Late_Update()
{
	__super::Update_Rect();
}

void CBoss04::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	CUIManager::Get_Instance()->Render_BossHP(hDC, this);

	if (m_bTalk_Idle)
	{
		CUtility::PrintText(hDC, 50, 250,
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
		Landed_Platform(pObj);
	}
	break;
	default:
		break;
	}

	__super::Update_Rect();
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
{}
