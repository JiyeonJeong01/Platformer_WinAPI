#include "pch.h"
#include "CPlayer02.h"
#include "CInputManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CLineManager.h"
#include "CUIManager.h"
CPlayer02::CPlayer02()
	: m_qwDTTimer(GetTickCount64()), m_fDeltaTime(0.f), m_iPlayerJump(0), m_iPlayerMaxJump(0)
	, m_fGroundY(0.f), m_bPlayerLanded(false)
{

}

CPlayer02::~CPlayer02()
{
	Release();
}

void CPlayer02::Initialize()
{

	CPlayer::Initialize();

	m_vPosition = { 50.f, WINCY * 0.8 };
	m_vSize = { 50.f, 50.f };
	m_vDirection = { 0.f,0.f };

	m_fSpeedX = 300.f;
	m_fSpeedY = 0.f;

	m_vPosinPosition = { 1,1 };

	m_fHP = 100;
	m_fMaxHP = m_fHP;

	__super::Update_Rect();
}

int CPlayer02::Update()
{
	CPlayer::Update();

	if (m_bDead)
		return OBJ_DEAD;

	Posin_Pos();

	_tprintf(_T("%f y스피드 : "), m_vPosition.y);

	{
		if (m_vPosition.y + (m_vSize.y * .5f) >= WINCY + 100)
		{
			m_bDead = true;
		}

		if (m_fSpeedY > 3000.f)
			m_fSpeedY == 3000.f;

		m_fDeltaTime = DeltaTime();

	CPlayer::Handle_KeyInput();
		Update_Components();

	}




	__super::Update_Rect();


	return OBJ_NOEVENT;
}

void CPlayer02::Late_Update()
{
	CPlayer::Late_Update();

}

void CPlayer02::Render(HDC hDC)
{
	CPlayer::Render(hDC);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	// Posin
	MoveToEx(hDC, (int)m_vPosition.x, (int)m_vPosition.y, nullptr);
	LineTo(hDC, m_vPosinPosition.x, m_vPosinPosition.y);

	CUIManager::Get_Instance()->Render_PlayerHP(hDC, this);


}

void CPlayer02::Release()
{
	CPlayer::Release();
}

void CPlayer02::Posin_Pos()
{
	Vector2 barrel = CInputManager::Get_Instance()->Get_CursorPosition();
	m_mouseDir.x = m_fMousePosX - m_vPosition.x;
	m_mouseDir.y = m_fMousePosY - m_vPosition.y;

	Vector2 dir = Vector2::Nomalize(m_mouseDir);

	m_vPosinPosition = m_vPosition + dir * 50.f;
}

void CPlayer02::Do_Attack()
{
	
	CPlayer::Do_Attack();
}

void CPlayer02::Take_Damage(float _fDamage)
{
	if (m_fHP <= 0)
		m_bDead = true;

	// �����ð�
	if (sz_Time + 1000 < GetTickCount())
	{

		if (0 <= (m_fHP - _fDamage))
			m_fHP -= _fDamage;
		else
		{
			m_fHP = 0.f;
			m_bDead = true;
		}
		sz_Time = GetTickCount();
	}
}

void CPlayer02::On_Collision(CObject* pObj)
{
	if(pObj->Get_ObjectID()==MON_BULLET)
		Take_Damage(pObj->Get_Damage());

}

void CPlayer02::Update_Components()
{
	// Collision_Line이 제대로 수행되지 않았을 경우 떨어질 높이를 설정
	m_fGroundY = WINCY + 100.f;

	bool line = CLineManager::Get_Instance()
		->Collision_Line(m_vPosition, &m_fGroundY);

	Jump();

	Horizontal_Move();

	Vertical_Move();
	Landed();
}

float CPlayer02::DeltaTime()
{


	ULONGLONG qwCurrentTime = GetTickCount64();
	ULONGLONG qwTimeDiff = qwCurrentTime - m_qwDTTimer; // 지금시간 - 생성자 호출시간 = 델타
	m_qwDTTimer = qwCurrentTime; // 초기화 ,생성자 호출시간 을 지금시간으로

	float fDeltaTime = static_cast<float>(qwTimeDiff) * 0.001f; // 델타타임(루프 1번)을 1초기준으로 변환

	return fDeltaTime;
}

void CPlayer02::Landed()
{
	if (m_fSpeedY >= 0.f
		&& m_vPosition.y + (m_vSize.y / 2.f) >= m_fGroundY)
	{
		m_vPosition.y = m_fGroundY - (m_vSize.y / 2.f);
		m_fSpeedY = 0.f;
		m_iPlayerJump = 0;
	}
}

void CPlayer02::Jump()
{
	if (bJumpPressed && m_iPlayerJump < 2)
	{
		m_fSpeedY = -900.f;
		// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.

		m_iPlayerJump += 1;
		// 플레이어가 점프를 하는 중일때 점프 하나 증가, 현재 2 이상이 되면 점프 제한
	}
}

void CPlayer02::Horizontal_Move()
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

void CPlayer02::Vertical_Move()
{
	// 수직방향 이동 (점프, 낙하)
	m_fSpeedY += 3000.f * m_fDeltaTime;
	//! Y속도 += 가속도(중력가속도 * 화면 보정값) * dt : 속도의 적분

	m_vPosition.y += m_fSpeedY * m_fDeltaTime;
	//! Y위치 += Y속도 * dt : 위치의 적분
}



//void CPlayer02::Jumping()
//{
//	float fY = .0f;
//	float m_fGravity = 9.8f;
//	bool isHight = false;
//
//	bool bLine = CLineManager::Get_Instance()->Collision_Line(m_vPosition, &fY);
//
//	if (m_bJump)
//	{
//
//		if (isStart)
//		{
//			tmp = m_vPosition.y;
//			isStart = false;
//			m_fTime = 0.f;
//		}
//
//		m_vPosition.y -= (m_fSpeedY * m_fTime - (9.8f * m_fTime * m_fTime) * 0.5f);
//
//		float h = ((m_fSpeedY * m_fSpeedY) / (2 * 9.8)) + tmp + (m_vSize.y * .5f);
//
//		m_fTime += 0.2f;
//
//		if (m_fSpeedY - m_fGravity * m_fTime <= 0)
//			isHight = true;
//
//		if (bLine && m_vPosition.y >= fY - (m_vSize.y * 0.5f) && isHight)
//		{
//			m_fTime = 0.f;
//			m_vPosition.y = fY - (m_vSize.y * .5f);
//			m_bJump = false;
//			isHight = false;
//
//		}
//
//	}
//	else if (bLine)
//	{
//		m_vPosition.y = fY - (m_vSize.y * .5f);
//
//	}
//	else
//	{
//		m_fTime += 0.2f;
//
//		m_vPosition.y -= -((9.8f * m_fTime * m_fTime) * 0.5f);
//
//		if (m_vPosition.y > WINCY)
//		{
//			m_bDead = true;
//			m_fTime = 0;
//		}
//
//	}
//
//
//}
