#include "pch.h"
#include "CBoss02.h"
#include "CPlayer02.h"
#include "math.h"

CBoss02::CBoss02()
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

	m_vPosition = { WINCX - 100, WINCY - ((WINCY >> 2) + 100) };
	m_vDirection = { 0.f, 0.f };
	m_vSize = { 70.f, 70.f };

	m_fSpeedX = 5.f;
	m_fSpeedY = 7.f;


	m_objID = MONSTER;

	// Boss Status
	m_fMaxHP = 100.f;
	m_fHP = m_fMaxHP;

	m_BossPosinDir[0] = { -1,0 };
	m_BossPosinDir[1]={ 1,0 };
	m_BossPosinDir[2]={ 0,1 };
	m_BossPosinDir[3]={ 0,-1 };
	m_fDamage = 10.f;
	__super::Update_Rect();

}



int CBoss02::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;


	{

		// TODO : 점프?? 
		float pY = 0.f;
		CLineManager::Get_Instance()->Collision_Line(m_vPosition, &pY);
		m_vPosition.y = pY - (m_vSize.y / 2);
	}


	Vector2 pos = CObjectManager::Get_Instance()->Get_Player()->Get_Position();
	Vector2 size = CObjectManager::Get_Instance()->Get_Player()->Get_Size();
	float distanceX = pos.x - m_vPosition.x;
	float distanceY = pos.y - m_vPosition.y;

	if (200 >= (abs(distanceX)))
	{
		if (distanceX <= -(m_vSize.y / 2))
		{
			m_vPosition.x -= m_fSpeedX;

		}
		else if (distanceX >= +(m_vSize.y / 2))
		{
			m_vPosition.x += m_fSpeedX;

		}

		if ((distanceX <= -(m_vSize.y / 2))
		{
			// TODO : 점프
		}

	}



	ULONGLONG current = GetTickCount64();

		if (current - m_Attack_Interval >= 1000)
		{
			if (m_pattern == BOSS02_PATTERN::IDLE)
			{
				Do_Attack();

				m_Attack_Interval = current;
			}
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



}

void CBoss02::Take_Damage(float _fDamage)
{
	if (0 < (m_fHP - _fDamage))
		m_fHP -= _fDamage;
	else
	{
		m_fHP = 0.f;
		m_bDead = true;
	}
}
