#include "pch.h"
#include "CBoss02.h"
#include "CPlayer02.h"
#include "math.h"
#include "CAbstractFactory.h"
#include "CBullet.h"

CBoss02::CBoss02(): m_Attack_Interval2(GetTickCount()), bJump(false)
{
	ZeroMemory(&m_BossPosinDir, sizeof(Vector2) * 4);
}

CBoss02::~CBoss02()
{
	Release();
}

void CBoss02::Initialize()
{
	CMonster::Initialize();

	m_vPosition = { 2500, WINCY - ((WINCY >> 2) + 100) };
	m_vDirection = { 0.f, 0.f };
	m_vSize = { 70.f, 70.f };

	m_fSpeedX = 200.f;
	m_fSpeedY = 7.f;


	m_objID = MONSTER;

	// Boss Status
	m_fMaxHP = 100.f;
	m_fHP = m_fMaxHP;

	m_BossPosinDir[0] = { -1,0 };
	m_BossPosinDir[1] = { 1, 0 };
	m_BossPosinDir[2] = { 0, 1 };
	m_BossPosinDir[3] = { 0, -1 };
	m_fDamage = 10.f;

	pTarget = CObjectManager::Get_Instance()->Get_Player();
	__super::Update_Rect();

}



int CBoss02::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;


			m_fDeltaTime = DeltaTime();


		Vector2 pos = pTarget->Get_Position();
		Vector2 size = pTarget->Get_Size();
		float distanceX = pos.x - m_vPosition.x;
		float distanceY = pos.y - m_vPosition.y;

		if (400 >= (abs(distanceX)))
		{
			if (distanceX <= -(m_vSize.y / 2))
			{
				m_vPosition.x -= m_fSpeedX *m_fDeltaTime;

			}
			else if (distanceX >= +(m_vSize.y / 2))
			{
				m_vPosition.x += m_fSpeedX *m_fDeltaTime;

			}

			if (distanceX >= -(m_vSize.y / 2) && (distanceX <= +(m_vSize.y / 2)) && distanceY <= -(m_vSize.y / 2))
			{


				if (bJump != true)
				{
				bJump = true;
				m_fSpeedY = -900.f;
				// 임의로 준 점프 스피드, 점프할때만 필요하므로 이 때 값을 집어넣는다.
				}
			}

		}
	

		{
			// TODO : 점프?? 


			float pY = WINCY + 100.f;
		bool	bLine = CLineManager::Get_Instance()->Collision_Line(m_vPosition, &pY);

				// 수직방향 이동 (점프, 낙하)
				m_fSpeedY += 3000.f * m_fDeltaTime;
				//! Y속도 += 가속도(중력가속도 * 화면 보정값) * dt : 속도의 적분

				m_vPosition.y += m_fSpeedY * m_fDeltaTime;
				//! Y위치 += Y속도 * dt : 위치의 적분

			if (bJump)
			{





				if (m_fSpeedY >= 0.f
					&& m_vPosition.y + (m_vSize.y / 2.f) > pY)
				{
					m_vPosition.y = pY - (m_vSize.y / 2.f);
					m_fSpeedY = 0.f;
					bJump = false;
				}

			}
			else if(bLine)
			{
				m_vPosition.y = pY - (m_vSize.y / 2);
			}

		}


	ULONGLONG current2 = GetTickCount64();
	if (abs(distanceX) <= 500)
	{

	if (current2 - m_Attack_Interval2 >= 2000)
	{
		if (m_pattern == BOSS02_PATTERN::IDLE)
		{
			m_pattern = BOSS02_PATTERN::PATTERN1;
			m_Attack_Interval2 = current2;

		}
		else if (m_pattern == BOSS02_PATTERN::PATTERN1)
		{
			m_pattern = BOSS02_PATTERN::IDLE;
			m_Attack_Interval2 = current2;

		}


	}
	}

	ULONGLONG current = GetTickCount64();

	if (current - m_Attack_Interval >= 150)
	{
		//if (m_pattern == BOSS02_PATTERN::IDLE)
		//{
			Do_Attack();

			m_Attack_Interval = current;
		//}
	}


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss02::Late_Update()
{

}

void CBoss02::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	CUIManager::Get_Instance()->Render_BossHP(hDC, this);
	MoveToEx(hDC, m_vPosition.x, m_vPosition.y,NULL);
	LineTo(hDC, m_vPosition.x -500, m_vPosition.y);
}

void CBoss02::Release()
{
}

void CBoss02::On_Collision(CObject* pObj)
{
	if (pObj->Get_ObjectID() == PL_BULLET)
	{
		Take_Damage(pObj->Get_Damage());
	}
	else if (pObj->Get_ObjectID() == PLAYER)
	{

		if (pObj)
		{
			CPlayer02* tmp = dynamic_cast<CPlayer02*>(pObj);
			tmp->Take_Damage(m_fDamage);
		}
	}
}

void CBoss02::Do_Attack()
{
	


	if (m_pattern == BOSS02_PATTERN::PATTERN1)
	{
		
		
		//for (int j = 0; j < m_PosinNum; j++)
		//{

	
				angle += 10.0;
				angle %= 360;
				Vector2 rotated = RotateVector(m_BossPosinDir[1], angle);

				CObjectManager::Get_Instance()->Add_Object(MON_BULLET, CAbstractFactory<CBullet>::Create(MON_BULLET, m_vPosition, rotated));
			
		//}

	}
	else if (m_pattern == BOSS02_PATTERN::PATTERN2 && pTarget != nullptr)
	{


	}
	else if (m_pattern == BOSS02_PATTERN::PATTERN3 && pTarget != nullptr)
	{

	}


	//if (m_pattern != BOSS02_PATTERN::IDLE)
	//	m_pattern = BOSS02_PATTERN::IDLE;
}

void CBoss02::Take_Damage(float _fDamage)
{
	if (0 < (m_fHP - _fDamage))
		m_fHP -= _fDamage;
	else
	{
		m_fHP = 0.f;
		m_bDead = true;
		CStageManager::Get_Instance()->On_CurrentBossDead(this);
	}
}

Vector2 CBoss02::RotateVector(Vector2& v, float angle)
{
	float radian = angle * (PI / 180.f);

	float cosX = cosf(radian);
	float sinY = sinf(radian);

	Vector2 result;
	result.x = v.x * cosX - v.y * sinY;
	result.y = v.x * sinY - v.y * cosX;
	return result;
}