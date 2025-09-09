#include "pch.h"
#include "CBoss04.h"
#include "CAbstractFactory.h"
#include "CBullet04.h"
#include "CBullet_BossAtk01.h"
#include "CBullet_BossAtk03.h"

CBoss04::CBoss04()
	: m_eBossState(BOSS04_STATE::IDLE),
	  m_fBossStateTimer(0.f), m_fBossAtkTimer(0.f),
	  m_bCanAttack(false)
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

	m_objID = MONSTER;

	m_fSpeedX = 400.f;	// 수평이동 속도

	m_fMaxHP  = 100.f;
	m_fHP     = m_fMaxHP;
	m_fDamage = 10.f;

	m_bGravityOn = true;	// 부모에 있는 점프 및 중력 코드 사용하겠다

	srand(static_cast<unsigned>(time(nullptr)));
}

int CBoss04::Update()
{
	int iResult = CMonster::Update();

	if (iResult == OBJ_DEAD)
		return iResult;

	// ↓ 콘솔로 원하는 값 보는 디버깅용 코드
	//_tprintf(_T(" m_vDirection.x : %f \n"), m_vDirection.x);

	// 낙하속도 상한 설정
	if (m_bGravityOn && m_fSpeedY > 1000.f)
		m_fSpeedY = 1000.f;

	// Vertical_Move : 점프 및 중력에 의한 수직 속도 및 이동 제어
	Vertical_Move();

	// 라인 충돌 및 그 위에 착지 기능을 사용하긴 하므로 상시 실행
	m_fGroundY = WINCY + 100.f;
	CLineManager::Get_Instance()->Collision_Line(m_vPosition, &m_fGroundY);
	Landed_Line();

	// 타이머
	m_fBossStateTimer += m_fDeltaTime;			// 상태 간 딜레이
	m_fBossAtkTimer += m_fDeltaTime;			// 상태 내 공격 간 딜레이

	// 상태 간 전환
	switch (m_eBossState)
	{
	case BOSS04_STATE::IDLE:
	{
		if (m_fBossStateTimer > 3.0f)		// IDLE 지속시간 끝났을 때
		{
			const int iPattern = rand() % 4;	// 0 ~ 3 범위
			switch (iPattern)
			{
			case 0:
				m_eBossState = BOSS04_STATE::ATTACK_01;
				break;
			case 1:
				m_eBossState = BOSS04_STATE::ATTACK_02;
				break;
			case 2:
				m_eBossState = BOSS04_STATE::ATTACK_03;
				break;
			case 3:
				m_eBossState = BOSS04_STATE::ATTACK_02;
				break;
			}

			m_bCanAttack      = true;		// 한 상태 동안 한 번만 공격이 나오는 패턴에서는 상태 실행 후 false로 바꾸기
			m_fBossStateTimer = 0.f;		// 다음 상태용 타이머 리셋
		}
	}
	break;
	case BOSS04_STATE::ATTACK_01:
	case BOSS04_STATE::ATTACK_02:
	case BOSS04_STATE::ATTACK_03:
	{
		if (m_fBossStateTimer > 3.0f)
		{
			m_eBossState      = BOSS04_STATE::IDLE;
			m_fBossStateTimer = 0.f;
		}
	}
	break;
	default:
		break;
	}

	// 상태 간 행동
	switch (m_eBossState)
	{
	case BOSS04_STATE::ATTACK_01:
	{
		if (m_fBossAtkTimer > 0.7f)	// 발사 간격 조절
		{
			CBoss04::Attack01();
			m_fBossAtkTimer = 0.f;
		}
	}
	break;
	case BOSS04_STATE::ATTACK_02:
	{
		CBoss04::Attack02();		// 이동하는 패턴이기에 항상 실행
	}
	break;
	case BOSS04_STATE::ATTACK_03:
	{
		if (m_fBossAtkTimer > 0.1f)
		{
			CBoss04::Attack03();
			m_fBossAtkTimer = 0.f;
		}
	}
	break;
	default:
		break;
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

	// 상태 간 대사
	switch (m_eBossState)
	{
	case BOSS04_STATE::IDLE:
	{
		//const int iDialogue = rand() % 3;
		//switch (iDialogue)
		//{
		//case 0:
		//	break;
		//default: 
		//	break;
		//}

		CUtility::PrintText(hDC, 1100, 150, L"어리석군... ");
	}

	break;
	case BOSS04_STATE::ATTACK_01:
		CUtility::PrintText(hDC, 1100, 150, L"ATTACK_01");
		break;
	case BOSS04_STATE::ATTACK_02:
		CUtility::PrintText(hDC, 1100, 150, L"ATTACK_02");
		break;
	case BOSS04_STATE::ATTACK_03:
		CUtility::PrintText(hDC, 1100, 150, L"ATTACK_03");
		break;
	default:
		break;
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
{
	Vector2 vPlayer_Dir;

	vPlayer_Dir.x = CObjectManager::Get_Instance()
					->Get_Player()->Get_Position().x - m_vPosition.x;

	m_vDirection = vPlayer_Dir;

	if (m_fBossAtkTimer < 0.3f)		// 점프
		__super::Jump(1500);

	if (m_fBossAtkTimer < 0.6f)		// 수평 이동
		__super::Horizontal_Move();

	if (m_fBossAtkTimer > 1.5f)		// Attack02 실행 간격
		m_fBossAtkTimer = 0.f;
}

void CBoss04::Attack03()
{
	Vector2 vPlayer_Dir;

	vPlayer_Dir.x = CObjectManager::Get_Instance()
					->Get_Player()->Get_Position().x - m_vPosition.x;

	vPlayer_Dir.y = 1.0f;

	vPlayer_Dir = Vector2::Nomalize(vPlayer_Dir);

	CObjectManager::Get_Instance()->Add_Object(
		MON_BULLET, CAbstractFactory<CBullet_BossAtk03>::Create(
			MON_BULLET, m_vPosition, vPlayer_Dir));
}
