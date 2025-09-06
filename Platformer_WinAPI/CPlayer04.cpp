#include "pch.h"
#include "CPlayer04.h"
#include "CLineManager.h"

CPlayer04::CPlayer04()
	: m_fPlayerBottom(0.f), m_fJumpSpeed(0.f), m_fDeltaTime(0.f),
	  m_iPlayerJump(0), m_qwDTTimer(GetTickCount64())
{}

CPlayer04::~CPlayer04()
{
	CPlayer04::Release();
}

void CPlayer04::Initialize()
{
	m_vPosition  = { WINCX >> 3, WINCY - (WINCY >> 2) };
	m_vDirection = { 0.f, 0.f };
	m_vSize      = { 40.f, 40.f };

	m_fSpeedX = 500.f;
	//! dt를 곱했으므로, 프레임마다 이동이 아닌 시간당 이동이기 때문에 x스피드가 커야 함

	//m_fSpeedY = 7.f;
	//! 속도 = 가속도 * dt 를 사용할 것이므로 y속도 고정값 사용 X

	m_objID   = PLAYER;
	m_fMaxHP  = 100.f;
	m_fHP     = m_fMaxHP;
	m_fDamage = 1.f;
}

int CPlayer04::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fDeltaTime = DeltaTime();
	//todo DeltaTime 은 추후 Timer 클래스로 따로 만들 예정

	CObject::Update_Rect();

	m_fPlayerBottom = m_vPosition.y + (m_vSize.y / 2.f);

	// Process client's inputs
	CPlayer::Handle_KeyInput();

	// Apply inputs to player's state
	// + 시간에 따른 등가속 물리 구현
	CPlayer04::Update_Components();

	if (bLeftMouseClicked)
		CPlayer::Do_Attack();

	return OBJ_NOEVENT;
}

void CPlayer04::Late_Update()
{
	CPlayer::Late_Update();
}

void CPlayer04::Render(HDC hDC)
{
	CPlayer::Render(hDC);
}

void CPlayer04::Release()
{}

void CPlayer04::Do_Attack()
{
	CPlayer::Do_Attack();
}

void CPlayer04::Take_Damage(float _fDamage)
{
	CPlayer::Take_Damage(_fDamage);
	//! Take_Damage : 현재 구현 안되어 있음
}

void CPlayer04::Update_Components()
{
	// 라인에 착지하기 위한 Collision_Line 호출
	float fGroundY = 0.f;
	CLineManager::Get_Instance()
		->Collision_Line(m_vPosition.x, fGroundY);

	// 좌우 방향키에 따른 수평방향 이동
	if (bLeftPressed)
		m_vDirection.x = -1.f;
	else if (bRightPressed)
		m_vDirection.x = 1.f;
	else
		m_vDirection.x = 0.f;

	m_vDirection.y = 0.f;
	// -> 수직방향으로는 직접 점프, 낙하로 구현하므로 고정값은 안쓰임

	m_vDirection = m_vDirection.GetNomalized();
	// 일단 Normalize 했지만, 사실상 m_vDirection은 0 또는 1이므로 현재 의미는 없음

	// m_iPlayerJump 를 하나씩 증가시켜서, 조건식으로 더블 점프 구현
	if (bJumpPressed && m_iPlayerJump < 2)
	{
		m_fJumpSpeed = -800.f;
		// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.
		m_iPlayerJump += 1;
		// 플레이어가 점프를 하는 중일때 점프 하나 증가
	}

	// 가로로 이동
	m_vPosition.x += m_vDirection.x * m_fSpeedX * m_fDeltaTime;

	// 세로로 이동 (점프, 낙하)
	m_fJumpSpeed += 2000 * m_fDeltaTime;
	//! Y속도 += 가속도(중력가속도 * 화면 보정값) * dt : 속도의 적분

	m_vPosition.y += m_fJumpSpeed * m_fDeltaTime;
	//! Y위치 += Y속도 * dt : 위치의 적분

	// 땅에 발이 닿도록 위치 조정
	//? 이러면 결국 fGroundY라는 위치값으로 착지 판단을 하는 건가?
	if (m_vPosition.y > (fGroundY - (m_vSize.y / 2.f)))
	{
		m_vPosition.y = fGroundY - (m_vSize.y / 2.f);
		m_fJumpSpeed  = 0.f;
		m_iPlayerJump = 0;
	}
}

//! DeltaTime 측정용.
// 먼저 CPlayer04의 생성자에서 m_qwDTTimer가 흐르기 시작하고,
// 그 다음 Update() 안에서 DeltaTime()을 호출 할 때 qwCurrentTime은 흐르기 시작함
// qwTimeDiff 에 둘의 차이를 저장하고 (이게 델타 타임)
// m_qwDTTimer = qwCurrentTime 으로 m_qwDTTimer 재초기화
// qwTimeDiff은 GetTickCount64 인 ms 단위이므로 0.001 을 곱해 초 단위로 변환
// -> fDeltaTime 완성!
float CPlayer04::DeltaTime()
{
	ULONGLONG qwCurrentTime = GetTickCount64();
	ULONGLONG qwTimeDiff    = qwCurrentTime - m_qwDTTimer;
	m_qwDTTimer             = qwCurrentTime;

	float fDeltaTime = static_cast<float>(qwTimeDiff) * 0.001f;

	return fDeltaTime;
}
