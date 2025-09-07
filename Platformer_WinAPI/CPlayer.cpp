#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
	: bLeftPressed(false), bRightPressed(false),
	bJumpPressed(false), bLeftMouseClicked(false),
	m_iPlayerJump(0), m_iPlayerMaxJump(0),
	m_fGroundY(0.f), m_bPlayerLanded(false)
{
	ZeroMemory(&m_vPosinPosition, sizeof(Vector2));
	ZeroMemory(&m_mouseDir, sizeof(Vector2));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_vPosition = { WINCX >> 3, WINCY - (WINCY >> 2) };
	m_vDirection = { 0.f, 0.f };
	m_vSize = { 40.f, 40.f };

	m_fSpeedX = 500.f;
	m_fSpeedY = 0.f;

	m_fMaxHP = 100.f;
	m_fHP = m_fMaxHP;
	m_fDamage = 1.f;

	m_objID = PLAYER;
}

int CPlayer::Update()
{
	if (m_bDead) return OBJ_DEAD;

	m_fDeltaTime = DeltaTime();

	// Process client's inputs
	Handle_KeyInput();

	// Apply inputs to player's state 
	Update_Components();

	if (bLeftMouseClicked)
		Do_Attack();

	float iScrollX = CScrollManager::Get_Instance()->Get_ScrollX();
	float iScrollY = CScrollManager::Get_Instance()->Get_ScrollY();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	Scroll_Offset();

	float iScrollX = CScrollManager::Get_Instance()->Get_ScrollX();
	float iScrollY = CScrollManager::Get_Instance()->Get_ScrollY();

	float mouseWorldX = m_fMousePosX - iScrollX;
	float mouseWorldY = m_fMousePosY - iScrollY;

	m_mouseDir.x = mouseWorldX - m_vPosition.x;
	m_mouseDir.y = mouseWorldY - m_vPosition.y;

	Vector2 dir = Vector2::Nomalize(m_mouseDir);
	m_vPosinPosition.x = m_vPosition.x + (50 * dir.x);
	m_vPosinPosition.y = m_vPosition.y + (50 * dir.y);

	__super::Update_Rect(); 
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int iScrollX = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollX());
	int iScrollY = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollY());

	MoveToEx(hDC, static_cast<int>(m_vPosition.x + iScrollX), static_cast<int>(m_vPosition.y + iScrollY), nullptr);
	LineTo(hDC, static_cast<int>(m_vPosinPosition.x + iScrollX), static_cast<int>(m_vPosinPosition.y + iScrollY));
}

void CPlayer::Release()
{

}

void CPlayer::Handle_KeyInput()
{
	// Apply client's input to variables
	bLeftPressed = CInputManager::Get_Instance()->GetKey('A');
	bRightPressed = CInputManager::Get_Instance()->GetKey('D');
	bJumpPressed = CInputManager::Get_Instance()->GetKeyDown(VK_SPACE);

	bLeftMouseClicked = CInputManager::Get_Instance()->GetKeyDown(VK_LBUTTON);
	m_fMousePosX = CInputManager::Get_Instance()->Get_CursorPosition().x;
	m_fMousePosY = CInputManager::Get_Instance()->Get_CursorPosition().y;
}

void CPlayer::Update_Components()
{
	// Update player's direction
	// (조건) ? true일 경우 : false일 경우
	//m_vDirection.x = (bLeftPressed ? -1.f : ( bRightPressed ? 1.f : 0.f ));
	//m_vDirection.y = bJumpPressed ? -1.f : 0.f;
	//
	//Vector2 normalized = Vector2::Nomalize(m_vDirection);
	//m_vDirection.x = normalized.x;
	//m_vDirection.y = normalized.y;
	//
	//// Update player's position
	//m_vPosition.x += m_vDirection.x * m_fSpeedX;
	//m_vPosition.y += m_vDirection.y * m_fSpeedY;
	//
	//// Update player's renderer rect
	//__super::Update_Rect();

	// Jump Jump
	m_fGroundY = WINCY + 100.f;
	CLineManager::Get_Instance()->Collision_Line(m_vPosition, &m_fGroundY);

	Horizontal_Move();

	Jump();
	Vertical_Move();

	Landed();
}

void CPlayer::Do_Attack()
{
	// TODO : 각자 플레이어에서 세팅하기, Player03 보고 스크롤 세팅까지 하세요
	//Vector2 dir = Vector2::Nomalize(m_mouseDir);
	//Vector2 barrel = m_vPosition + dir * 50.f;
	//
	//CObjectManager::Get_Instance()->Add_Object(PL_BULLET, CAbstractFactory<CBullet>::Create(PL_BULLET, barrel, dir));
}

void CPlayer::Landed()
{
	if (m_fSpeedY >= 0.f
		&& m_vPosition.y + (m_vSize.y / 2.f) > m_fGroundY)
	{
		m_vPosition.y = m_fGroundY - (m_vSize.y / 2.f);
		m_fSpeedY = 0.f;
		m_iPlayerJump = 0;
	}
}

void CPlayer::Jump()
{
	if (bJumpPressed && m_iPlayerJump < 2)
	{
		m_fSpeedY = -900.f;
		// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.

		m_iPlayerJump += 1;
		// 플레이어가 점프를 하는 중일때 점프 하나 증가, 현재 2 이상이 되면 점프 제한
	}
}

void CPlayer::Horizontal_Move()
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

void CPlayer::Vertical_Move()
{
	// 수직방향 이동 (점프, 낙하)
	m_fSpeedY += 3000.f * m_fDeltaTime;
	//! Y속도 += 가속도(중력가속도 * 화면 보정값) * dt : 속도의 적분

	m_vPosition.y += m_fSpeedY * m_fDeltaTime;
	//! Y위치 += Y속도 * dt : 위치의 적분
}

void CPlayer::Scroll_Offset()
{
	int minX = 250;
	int maxX = WINCX - 300;

	int minY = 300;
	int maxY = WINCY - 150;

	float iScrollX = CScrollManager::Get_Instance()->Get_ScrollX();
	float iScrollY = CScrollManager::Get_Instance()->Get_ScrollY();

	float playerScreenX = m_vPosition.x + iScrollX;
	float playerScreenY = m_vPosition.y + iScrollY;

	// X축 스크롤
	if (playerScreenX < minX)
	{
		float offset = (minX - playerScreenX);
		CScrollManager::Get_Instance()->Set_ScrollX(offset);
	}
	else if (playerScreenX > maxX)
	{
		float offset = (playerScreenX - maxX);
		CScrollManager::Get_Instance()->Set_ScrollX(-offset);
	}

	// Y축 스크롤
	if (playerScreenY < minY)
	{
		float offset = (minY - playerScreenY);
		CScrollManager::Get_Instance()->Set_ScrollY(offset);
	}
	else if (playerScreenY > maxY)
	{
		float offset = (playerScreenY - maxY);
		CScrollManager::Get_Instance()->Set_ScrollY(-offset);
	}
}