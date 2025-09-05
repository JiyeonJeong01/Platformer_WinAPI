#include "pch.h"
#include "CPlayer.h"

#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CInputManager.h"
#include "CObjectManager.h"

CPlayer::CPlayer()
{
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

    m_fSpeedX = 10.f;
    m_fSpeedY = 7.f;

    bLeftPressed = false;
    bRightPressed = false;
    bJumpPressed = false;

    bLeftMouseClicked = false;

    m_objID = PLAYER;
}

int CPlayer::Update()
{
    if (m_bDead) return OBJ_DEAD;

    // Process client's inputs
    Handle_KeyInput();

    // Apply inputs to player's state 
    Update_Components();

    return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
    m_vPosinPosition.x = LONG(m_vPosition.x + (100 * cosf(m_fAngle)));
    m_vPosinPosition.y = LONG(m_vPosition.y - (100 * sinf(m_fAngle)));
}

void CPlayer::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    // Posin
    MoveToEx(hDC, (int)m_vPosition.x, (int)m_vPosition.y, nullptr);
    LineTo(hDC, m_vPosinPosition.x, m_vPosinPosition.y);

    // for test
    if (bLeftMouseClicked)
    {
        Do_Attack();
        Rectangle(hDC, m_fMousePosX - 10, m_fMousePosY - 10, m_fMousePosX +10, m_fMousePosY + 10);
    }
}

void CPlayer::Release()
{

}

void CPlayer::Handle_KeyInput()
{
    // Apply client's input to variables
    bLeftPressed = CInputManager::Get_Instance()->GetKey('A');
    bRightPressed = CInputManager::Get_Instance()->GetKey('D');
    bJumpPressed = CInputManager::Get_Instance()->GetKey(VK_SPACE);

    bLeftMouseClicked = CInputManager::Get_Instance()->GetKey(VK_LBUTTON);
    m_fMousePosX = CInputManager::Get_Instance()->Get_CursorPosition().x;
    m_fMousePosY = CInputManager::Get_Instance()->Get_CursorPosition().y;
}

void CPlayer::Update_Components()
{
    // Update player's direction
    m_vDirection.x = bLeftPressed ? -1.f : ( bRightPressed ? 1.f : 0.f );
    m_vDirection.y = bJumpPressed ? -1.f : 0.f;

    Vector2 normalized = Vector2::Nomalize(m_vDirection);
    m_vDirection.x = normalized.x;
    m_vDirection.y = normalized.y;

    // Update player's position
    m_vPosition.x += m_vDirection.x * m_fSpeedX;
    m_vPosition.y += m_vDirection.y * m_fSpeedY;

    // Update player's renderer rect
    __super::Update_Rect();
}

void CPlayer::Do_Attack()
{
    Vector2 mouseDir = { };

    mouseDir.x = m_fMousePosX - m_vPosition.x;
    mouseDir.y = m_fMousePosY - m_vPosition.y;

    float distance = sqrtf(mouseDir.x * mouseDir.x + mouseDir.y * mouseDir.y);

    Vector2 dir = Vector2::Nomalize(mouseDir);

    // TODO : Create Bullet and Fire, m_vPosition -> m_vPosinPosition
    CObjectManager::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create(m_vPosition, dir));
    
}
	