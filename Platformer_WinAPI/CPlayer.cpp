#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"

CPlayer::CPlayer()
	: bLeftPressed(false), bRightPressed(false), bJumpPressed(false), bLeftMouseClicked(false),
	  m_iPlayerJumpCount(0), m_iPlayerMaxJump(0), m_fGroundY(0.f), m_bPlayerLanded(false),
	  m_fAtkTimer(0), m_fAtkCooldown(0)
{
	ZeroMemory(&m_vPosinPosition, sizeof(Vector2));
	ZeroMemory(&m_mouseDir, sizeof(Vector2));
}

CPlayer::~CPlayer()
{
	CPlayer::Release();
}

void CPlayer::Initialize()
{
	m_vPosition  = { WINCX >> 3, WINCY - (WINCY >> 2) };
	m_vDirection = { 0.f, 0.f };
	m_vSize      = { 40.f, 40.f };

	m_fSpeedX = 500.f;
	m_fSpeedY = 0.f;

	m_fMaxHP         = 100.f;
	m_fHP            = m_fMaxHP;
	m_fDamage        = 1.f;
	m_iPlayerMaxJump = 2;
	m_fAtkCooldown   = 0.2f;
}

int CPlayer::Update()
{
	if (m_vPosition.y + (m_vSize.y / 2.f) >= WINCY + 100) // 낭떠러지
	//todo && 플레이어 사망 조건
	{
		//todo 스테이지 매니저에서 재시작하도록 함수 호출
	}

	// ↓ 콘솔로 원하는 값 보는 디버깅용 코드
	//_tprintf(_T(" m_bPlayerLanded : %d \n"), m_bPlayerLanded);

	// 낙하속도 상한 설정
	if (m_fSpeedY > 1000.f)
		m_fSpeedY = 1000.f;

	m_fDeltaTime = CObject::DeltaTime();

	// 플레이어 내장 타이머
	m_fAtkTimer += m_fDeltaTime;

	// 플레이어 입력 받아오기
	Handle_KeyInput();

	// 플레이어 위치, 속도 업데이트
	Update_Components();

	if (bLeftMouseClicked)
		Do_Attack();

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

	Vector2 dir        = Vector2::Nomalize(m_mouseDir);
	m_vPosinPosition.x = m_vPosition.x + (50 * dir.x);
	m_vPosinPosition.y = m_vPosition.y + (50 * dir.y);

	// ↓ 콘솔로 원하는 값 보는 디버깅용 코드
	_tprintf(_T(" Is Player Landed? : %d \n"), m_bPlayerLanded);

	// 충돌판정용 RECT 갱신
	__super::Update_Rect();
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int iScrollX = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollX());
	int iScrollY = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollY());

	MoveToEx(hDC, static_cast<int>(m_vPosition.x) + iScrollX, static_cast<int>(m_vPosition.y) + iScrollY, nullptr);
	LineTo(hDC, static_cast<int>(m_vPosinPosition.x) + iScrollX, static_cast<int>(m_vPosinPosition.y) + iScrollY);

	CUIManager::Get_Instance()->Render_PlayerHP(hDC, this);
}

void CPlayer::Release()
{}

void CPlayer::Handle_KeyInput()
{
	// Apply client's input to variables
	bLeftPressed  = CInputManager::Get_Instance()->GetKey('A');
	bRightPressed = CInputManager::Get_Instance()->GetKey('D');
	bJumpPressed  = CInputManager::Get_Instance()->GetKeyDown(VK_SPACE);

	bLeftMouseClicked = CInputManager::Get_Instance()->GetKey(VK_LBUTTON);
	m_fMousePosX      = CInputManager::Get_Instance()->Get_CursorPosition().x;
	m_fMousePosY      = CInputManager::Get_Instance()->Get_CursorPosition().y;
}

void CPlayer::Update_Components()
{
	// Collision_Line이 제대로 수행되지 않았을 경우 떨어질 높이를 설정
	m_fGroundY = WINCY + 100.f;

	CLineManager::Get_Instance()->Collision_Line(m_vPosition, &m_fGroundY);

	Jump();

	Horizontal_Move();

	Vertical_Move();

	Landed_Line();
}

void CPlayer::On_Collision(CObject* pObj)
{
	switch (pObj->Get_ObjectID())
	{
	case MONSTER:
	{
		Take_Damage(pObj->Get_Damage());
	}
	break;
	case MON_BULLET:
	{
		Take_Damage(pObj->Get_Damage());
	}
	break;
	case ITEM:
	{
		//todo 아이템도 다양해지면...
		/*
		 * 아이템별로 세부 태그에 따라 작업이 나뉘어야 정석임
		 * 그 작업은 새로운 아이템 분류용 enum을 만들어서,
		 * 이를 아이템용 새로운 멤버변수에 넣어줘야 할듯
		 */
	}
	break;
	case PLATFORM:
	{
		//if (m_fSpeedY >= 0.f)
		//{
		Landed_Platform(pObj);
		//}

		//todo 천장에 닿을 때, 벽에 닿을 때
		//! -> 이를 Collision_RectEx 를 고쳐 사용 가능할지 테스트중

		// 충돌판정용 RECT 갱신
		CObject::Update_Rect();
	}
	break;
	default:
		break;
	}
}

void CPlayer::Do_Attack()
{
	// TODO : 각자 플레이어에서 세팅하기, Player03 보고 스크롤 세팅까지 하세요
	// -> 플레이어에 다 합쳐서 그냥 CPlayer 거 가져다가 써도 됨

	// 타이머를 이용한 일정 간격 발사
	if (m_fAtkTimer > m_fAtkCooldown)
	{
		m_fAtkTimer = 0;

		Vector2 dir    = Vector2::Nomalize(m_mouseDir);
		Vector2 barrel = m_vPosition + dir * 50.f;

		CObjectManager::Get_Instance()->
			Add_Object(PL_BULLET,
					   CAbstractFactory<CBullet>::Create(
						   PL_BULLET, barrel, dir));
	}
}

void CPlayer::Take_Damage(float _fDamage)
{
	if (m_fHP - _fDamage > 0.f)
		Set_HP(m_fHP - _fDamage);
	else
	{
		Set_HP(0.f);
		//todo 죽었어! 플레이어 사망 조건 true로 설정
	}
}

void CPlayer::Landed_Platform(CObject* pObj)
{
	float fX = 0.f, fY = 0.f;

	if (CCollisionManager::Check_Rect(this, pObj, &fX, &fY))
	{
		if (fX > fY)	// 상하 충돌
		{
			if (m_vPosition.y < pObj->Get_Position().y && m_fSpeedY >= 0.f)		//	상 충돌
			{
				m_fSpeedY          = 0.f;
				m_iPlayerJumpCount = 0;
				m_vPosition.y      = pObj->Get_Position().y - (pObj->Get_Size().y / 2.f + m_vSize.y / 2.f);
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

/*
void CCollisionManager::Collision_RectEx(list<CObject*> _Dst, list<CObject*> _Src)
{
	float fX(0.f), fY(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				if (fX > fY)	// 상하 충돌
				{
					if (Dst->Get_Position().y < Src->Get_Position().y) // 상 충돌
					{
						Dst->Set_PosY(-fY);
					}
					else  // 하충돌
					{
						Dst->Set_PosY(fY);
					}
				}
				else			// 좌우 충돌
				{
					if (Dst->Get_Position().x < Src->Get_Position().x) // 좌 충돌
					{
						Dst->Set_PosX(-fX);
					}
					else  // 우 충돌
					{
						Dst->Set_PosX(fX);
					}
				}
			}
		}
	}
}

bool CCollisionManager::Check_Rect(CObject* _Dst, CObject* _Src, float* pX, float* pY)
{
	float	fDistanceX = abs(_Dst->Get_Position().x - _Src->Get_Position().x);
	float	fDistanceY = abs(_Dst->Get_Position().y - _Src->Get_Position().y);

	float	fRadiusX = (_Dst->Get_Size().x + _Src->Get_Size().x) * 0.5f;
	float	fRadiusY = (_Dst->Get_Size().y + _Src->Get_Size().y) * 0.5f;

	if ((fRadiusX >= fDistanceX) && (fRadiusY >= fDistanceY))
	{
		*pX = fRadiusX - fDistanceX;
		*pY = fRadiusY - fDistanceY;

		return true;
	}
	return false;
}
 */

void CPlayer::Landed_Line()
{
	if (m_fSpeedY >= 0.f
		&& m_vPosition.y + (m_vSize.y / 2.f) >= m_fGroundY)
	{
		m_vPosition.y      = m_fGroundY - (m_vSize.y / 2.f);
		m_fSpeedY          = 0.f;
		m_iPlayerJumpCount = 0;

		m_bPlayerLanded = true;
	}
}

void CPlayer::Jump()
{
	if (bJumpPressed && m_iPlayerJumpCount < m_iPlayerMaxJump)
	{
		m_fSpeedY = -900.f;
		// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.

		m_iPlayerJumpCount += 1;
		// 플레이어가 점프를 하는 중일때 점프 하나 증가, 현재 2 이상이 되면 점프 제한

		m_bPlayerLanded = false;
	}
}

void CPlayer::Horizontal_Move()
{
	// 좌우 방향키에 따른 m_vDirection.x 변경
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
	int minX = 50;
	int maxX = WINCX - 300;

	int minY = 300;
	int maxY = WINCY - 150;

	float iScrollX = CScrollManager::Get_Instance()->Get_ScrollX();
	float iScrollY = CScrollManager::Get_Instance()->Get_ScrollY();

	float playerScreenX = m_vPosition.x + iScrollX;
	float playerScreenY = m_vPosition.y + iScrollY;

	//! X축 스크롤
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

	//! Y축 스크롤
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
