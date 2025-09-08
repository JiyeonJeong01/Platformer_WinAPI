#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
	: pTarget(nullptr),
	  m_iMonsterJumpCount(0), m_iMonsterMaxJump(1),
	  m_fGroundY(0), m_bMonsterLanded(false), m_bGravityOn(false)
{}

CMonster::~CMonster()
{
	CMonster::Release();
}

void CMonster::Initialize()
{}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	// 델타타임 사용을 위해 포함할 것
	m_fDeltaTime = CObject::DeltaTime();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	__super::Update_Rect();
}

void CMonster::Render(HDC hDC)
{}

void CMonster::Release()
{}

void CMonster::On_Collision(CObject* pObj)
{}

void CMonster::Landed_Platform(CObject* pObj)
{
	float fX = 0.f, fY = 0.f;

	if (CCollisionManager::Check_Rect(this, pObj, &fX, &fY))
	{
		if (fX > fY)	// 상하 충돌
		{
			if (m_vPosition.y < pObj->Get_Position().y && m_fSpeedY >= 0.f)		//	상 충돌
			{
				m_fSpeedY           = 0.f;
				m_iMonsterJumpCount = 0;
				m_vPosition.y       = pObj->Get_Position().y - (pObj->Get_Size().y / 2.f + m_vSize.y / 2.f);

				m_bMonsterLanded = true;
			}
			else //-------------------------------------------	하 충돌
			{
				//m_fSpeedY = 0.f;
				//m_vPosition.y = pObj->Get_Position().y + (pObj->Get_Size().y / 2.f + m_vSize.y / 2.f);
				//! 천장 필요하면 사용하기
			}
		}

		if (fX < fY)		// 좌우 충돌
		{
			if (m_vPosition.x < pObj->Get_Position().x)		//	좌 충돌
			{
				m_vPosition.x = pObj->Get_Position().x - (pObj->Get_Size().x / 2.f + m_vSize.x / 2.f);
			}
			else //-------------------------------------------	우 충돌
			{
				m_vPosition.x = pObj->Get_Position().x + (pObj->Get_Size().x / 2.f + m_vSize.x / 2.f);
			}
		}
	}
}

void CMonster::Landed_Line()
{
	if (m_fSpeedY >= 0.f
		&& m_vPosition.y + (m_vSize.y / 2.f) >= m_fGroundY)
	{
		m_vPosition.y       = m_fGroundY - (m_vSize.y / 2.f);
		m_fSpeedY           = 0.f;
		m_iMonsterJumpCount = 0;

		m_bMonsterLanded = true;
	}
}

// 몬스터 점프는 m_bGravityOn == true 일 때만 사용 가능
// 주의 : 점프 조건은 직접 줄 것
void CMonster::Jump()
{
	if (m_bGravityOn && (m_iMonsterJumpCount < m_iMonsterMaxJump))
	{
		m_fSpeedY = -900.f;
		// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.

		m_iMonsterJumpCount += 1;
		// 몬스터가 점프를 하는 중일때 점프 하나 증가, 현재 2 이상이 되면 점프 제한

		m_bMonsterLanded = false;
	}
}

void CMonster::Left_Move()
{
	m_vDirection.x = -1.f;
	m_vDirection   = m_vDirection.GetNomalized();
	m_vPosition.x += m_vDirection.x * m_fSpeedX * m_fDeltaTime;
}

void CMonster::Right_Move()
{
	m_vDirection.x = 1.f;
	m_vDirection   = m_vDirection.GetNomalized();
	m_vPosition.x += m_vDirection.x * m_fSpeedX * m_fDeltaTime;
}

void CMonster::Vertical_Move()
{
	if (m_bGravityOn)
		m_fSpeedY += 3000.f * m_fDeltaTime;
	//! Y속도 += 가속도(중력가속도 * 화면 보정값) * dt : 속도의 적분

	m_vPosition.y += m_fSpeedY * m_fDeltaTime;
	//! Y위치 += Y속도 * dt : 위치의 적분
}
