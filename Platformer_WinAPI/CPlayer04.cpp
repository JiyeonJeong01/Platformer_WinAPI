#include "pch.h"
#include "CPlayer04.h"
#include "CLineManager.h"

CPlayer04::CPlayer04()
	: m_qwDTTimer(GetTickCount64()), m_fDeltaTime(0.f),
	  m_iPlayerJump(0), m_iPlayerMaxJump(0),
	  m_fGroundY(0.f), m_bPlayerLanded(false)
{}

CPlayer04::~CPlayer04()
{
	CPlayer04::Release();
}

void CPlayer04::Initialize()
{
	m_vPosition  = { 200, 200 };
	m_vDirection = { 0.f, 0.f };
	m_vSize      = { 40.f, 40.f };

	m_fSpeedX = 500.f;
	m_fSpeedY = 0.f;

	m_fMaxHP  = 100.f;
	m_fHP     = m_fMaxHP;
	m_fDamage = 1.f;
}

int CPlayer04::Update()
{
	// 낭떠러지
	if (m_vPosition.y + (m_vSize.y / 2.f) >= WINCY + 100)
	//todo && 플레이어 사망 조건
	{
		//todo 플레이어가 스테이지 재시작하도록
	}

	// ↓ 콘솔로 원하는 값 보는 디버깅용 코드
	//_tprintf(_T("%f y스피드 : "), m_fSpeedY);

	// 낙하속도 상한 설정
	if (m_fSpeedY > 3000.f)
		m_fSpeedY = 3000.f;

	// DeltaTime 측정
	m_fDeltaTime = DeltaTime();

	// 플레이어 입력 받아오기
	CPlayer::Handle_KeyInput();

	// 플레이어 위치, 속도 업데이트
	CPlayer04::Update_Components();

	// 충돌판정용 RECT 갱신
	CObject::Update_Rect();

	// 플레이어 공격
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

	//CUtility::PrintText(hDC, 50, 200, L"Ground ? : ", m_fGroundY);
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
}

void CPlayer04::Update_Components()
{
	// Collision_Line이 제대로 수행되지 않았을 경우 떨어질 높이를 설정
	m_fGroundY = WINCY + 100.f;

	CLineManager::Get_Instance()
		->Collision_Line(m_vPosition, &m_fGroundY);

	Landed();

	Jump();

	Horizontal_Move();

	Vertical_Move();
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

void CPlayer04::Landed()
{
	if (m_fSpeedY >= 0.f
		&& m_vPosition.y + (m_vSize.y / 2.f) > m_fGroundY)
	{
		m_vPosition.y = m_fGroundY - (m_vSize.y / 2.f);
		m_fSpeedY     = 0.f;
		m_iPlayerJump = 0;
	}
}

void CPlayer04::Jump()
{
	if (bJumpPressed && m_iPlayerJump < 2)
	{
		m_fSpeedY = -900.f;
		// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.

		m_iPlayerJump += 1;
		// 플레이어가 점프를 하는 중일때 점프 하나 증가, 현재 2 이상이 되면 점프 제한
	}
}

void CPlayer04::Horizontal_Move()
{
	// 좌우 방향키에 따른 수평방향 이동
	if (bLeftPressed)
		m_vDirection.x = -1.f;
	else if (bRightPressed)
		m_vDirection.x = 1.f;
	else
		m_vDirection.x = 0.f;

	m_vDirection = m_vDirection.GetNomalized();

	// 수평방향 이동
	m_vPosition.x += m_vDirection.x * m_fSpeedX * m_fDeltaTime;
}

void CPlayer04::Vertical_Move()
{
	// 수직방향 이동 (점프, 낙하)
	m_fSpeedY += 3000.f * m_fDeltaTime;
	//! Y속도 += 가속도(중력가속도 * 화면 보정값) * dt : 속도의 적분

	m_vPosition.y += m_fSpeedY * m_fDeltaTime;
	//! Y위치 += Y속도 * dt : 위치의 적분
}
