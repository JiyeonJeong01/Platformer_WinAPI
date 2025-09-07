#include "pch.h"
#include "CPlayer02.h"
#include "CInputManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CLineManager.h"
CPlayer02::CPlayer02() : m_bJump(false),m_fTime(0.f)
{

}

CPlayer02::~CPlayer02()
{
}

void CPlayer02::Initialize()
{

	CPlayer::Initialize();

	m_vPosition = { 50.f, WINCY * 0.8 };
	m_vSize = { 50.f, 50.f };
	m_vDirection = { 0,0 };
	m_fSpeedX = 8.f;
	m_fSpeedY = 15.f;
	m_vPosinPosition = { 1,1 };
}

int CPlayer02::Update()
{
	CPlayer::Update();

	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	Posin_Pos();

	if (bJumpPressed)
		m_bJump = true;
	Jumping();



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



void CPlayer02::Jumping()
{
	float fY = .0f;
	float m_fGravity = 9.8f;
	bool bLine = CLineManager::Get_Instance()->Collision_Line(m_vPosition, &fY);

		if (m_bJump)
		{
			m_vPosition.y -= m_fSpeedY * m_fTime - (9.8f * m_fTime * m_fTime) * 0.5f;
			
			


			m_fTime += 0.2f;
			if ( bLine&& fY<=m_vPosition.y +(m_vSize.y * .5f))
			{
  				m_fTime = 0.f;
				m_vPosition.y = fY-(m_vSize.y * .5f);
				m_bJump = false;
			}

		}
		else if (bLine)
		{
			m_vPosition.y = fY-(m_vSize.y*.5f);

		}
		else
		{
			m_fTime += 0.2f;

			m_vPosition.y -= -((9.8f * m_fTime * m_fTime) * 0.5f);

			if (m_vPosition.y > WINCY)
			{
				m_bDead = true;
				m_fTime = 0;
			}

		}
	
	
}
