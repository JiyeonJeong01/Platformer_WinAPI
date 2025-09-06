#include "pch.h"
#include "CPlayer02.h"
#include "CInputManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
CPlayer02::CPlayer02()
{
	
}

CPlayer02::~CPlayer02()
{
}

void CPlayer02::Initialize()
{

	CPlayer::Initialize();

	m_vPosition = { WINCX * .5f, WINCY * .5f };
	m_vSize = { 50.f, 50.f };
	m_vDirection = { 0,0 };
	m_fSpeedX = 10.f;
	m_fSpeedY = 10.f;
	m_vPosinPosition = { 1,1 };
}

int CPlayer02::Update()
{
	

	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	Posin_Pos();






	return CPlayer::Update();
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

	if (bJumpPressed)
	{

	}
}
