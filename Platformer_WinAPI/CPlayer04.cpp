#include "pch.h"
#include "CPlayer04.h"
#include "CAbstractFactory.h"
#include "CBullet04.h"

CPlayer04::CPlayer04()
{ }

CPlayer04::~CPlayer04()
{
	CPlayer04::Release();
}

void CPlayer04::Initialize()
{
	__super::Initialize();
}

int CPlayer04::Update()
{
	//const int iResult = __super::Update();

	if (m_vPosition.y + (m_vSize.y / 2.f) >= WINCY + 100) // 낭떠러지
	//todo && 플레이어 사망 조건
	{
		//todo 스테이지 매니저에서 재시작하도록 함수 호출
	}

	// 낙하속도 상한 설정
	if (m_fSpeedY > 1000.f)
		m_fSpeedY = 1000.f;

	m_fDeltaTime = CObject::DeltaTime();

	// 플레이어 내장 타이머
	m_fAtkTimer += m_fDeltaTime;

	// 플레이어 입력 받아오기
	__super::Handle_KeyInput();

	// 플레이어 위치, 속도 업데이트
	__super::Update_Components();

	if (bLeftMouseClicked)
		CPlayer04::Do_Attack();

	return OBJ_NOEVENT;
}

void CPlayer04::Late_Update()
{
	__super::Late_Update();
}

void CPlayer04::Render(HDC hDC)
{
	__super::Render(hDC);
}

void CPlayer04::Release()
{}

void CPlayer04::On_Collision(CObject* pObj)
{
	__super::On_Collision(pObj);
}

void CPlayer04::Do_Attack()
{
	//__super::Do_Attack();

	// 타이머를 이용한 일정 간격 발사
	if (m_fAtkTimer > m_fAtkCooldown)
	{
		m_fAtkTimer = 0;

		Vector2 dir    = Vector2::Nomalize(m_mouseDir);
		Vector2 barrel = m_vPosition + dir * 50.f;

		CObjectManager::Get_Instance()->
			Add_Object(PL_BULLET,
					   CAbstractFactory<CBullet04>::Create(
						   PL_BULLET, barrel, dir));
	}
}
