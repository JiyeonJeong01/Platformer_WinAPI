#include "pch.h"
#include "CBoss02.h"
#include "CPlayer02.h"
#include "math.h"
#include "CAbstractFactory.h"
#include "CBullet.h"
#include "CBullet_Boss02.h"

CBoss02::CBoss02() : m_Attack_Interval2(GetTickCount()), m_bJump(false),
m_isDash(false), m_DashSpeed(0.f), m_DashDuration(0.f), m_DashTime(0.f),
m_StepbackTime(0.f), m_Stepback(false), m_StepBackSpeed(0.f)
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
	m_vSize = { 90.f, 90.f };

	m_fSpeedX = 200.f;
	m_fSpeedY = 7.f;


	m_objID = MONSTER;

	// Boss Status
	m_fMaxHP = 100.f;
	m_fHP = m_fMaxHP;

	m_BossPosinDir = { -1,0 };

	m_fDamage = 1.f;

	pTarget = CObjectManager::Get_Instance()->Get_Player();

	m_DashSpeed = 500.f;
	m_DashDuration = 5.f;
	m_DashTime = .5f;
	
	m_Stepback = false;
	m_StepbackTime = .1f;
	m_StepBackSpeed = 30;
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

	Vector2 PlayerDir = Vector2::Nomalize({ distanceX, distanceY });

	if (700 >= (abs(distanceX)))
	{
		if (m_isDash ==true)
		{
			// �������� ��
		}
		else if (distanceX <= -(m_vSize.y / 2))
		{
			m_vPosition.x -= m_fSpeedX * m_fDeltaTime;

		}
		else if (distanceX >= +(m_vSize.y / 2))
		{
			m_vPosition.x += m_fSpeedX * m_fDeltaTime;

		}


		if (distanceX >= -(m_vSize.y / 2) && (distanceX <= +(m_vSize.y / 2)) && distanceY <= -(m_vSize.y / 2))
		{

			if (m_isDash != true && m_bJump != true)
			{
				m_bJump = true;
				m_fSpeedY = -900.f;
				// ���Ƿ� �� ���� ���ǵ�, �����Ҷ��� �ʿ��ϹǷ� �� �� ���� ����ִ´�.
			}
		}


	}
	// �� �ַܼ� ���ϴ� �� ���� ������ �ڵ�

	m_DashDuration -= m_fDeltaTime;

	if (!m_isDash && 300 >= (fabs(distanceX)) && m_DashDuration <= 0.f)
	{
		tmpdir = PlayerDir;
		m_isDash = true;
		m_DashDuration = 5.f;

	}

	Dash(tmpdir);

	{

		float pY = WINCY + 100.f;
		bool bLine = CLineManager::Get_Instance()->Collision_Line(m_vPosition, &pY);

		// �������� �̵� (����, ����)
		m_fSpeedY += 3000.f * m_fDeltaTime;
		//! Y�ӵ� += ���ӵ�(�߷°��ӵ� * ȭ�� ������) * dt : �ӵ��� ����

		m_vPosition.y += m_fSpeedY * m_fDeltaTime;
		//! Y��ġ += Y�ӵ� * dt : ��ġ�� ����

		if (m_fSpeedY >= 0.f
			&& m_vPosition.y + (m_vSize.y / 2.f) > pY)
		{
			m_vPosition.y = pY - (m_vSize.y / 2.f);
			m_fSpeedY = 0.f;
			m_bJump = false;
		}


	}
	_tprintf(_T("%f x : "), m_bJump);



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
	HDC	hMemDC = CBmpManager::Get_Instance()->Find_Img(L"Boss02");

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_vSize.x,
		(int)m_vSize.y,
		hMemDC,
		0,
		0,
		(int)m_vSize.x,
		(int)m_vSize.y,
		RGB(255, 255, 255));



	CUIManager::Get_Instance()->Render_BossHP(hDC, this);
	//MoveToEx(hDC, m_vPosition.x, m_vPosition.y, NULL);
	//LineTo(hDC, m_vPosition.x - 500, m_vPosition.y);
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
	else if (pObj->Get_ObjectID() == PLATFORM)
	{
		Landed_Platform(pObj);
		CObject::Update_Rect();
	}
}

void CBoss02::Do_Attack()
{



	if (m_pattern == BOSS02_PATTERN::PATTERN1)
	{

		angle += 10.0;
		angle %= 360;

		for (int j = 0; j < m_PosinNum; j++)
		{
			angle = (angle + (90 * j)) % 360;
			Vector2 rotated = RotateVector(m_BossPosinDir, angle);
			CObjectManager::Get_Instance()->Add_Object(MON_BULLET, CAbstractFactory<CBullet_Boss02>::Create(MON_BULLET, m_vPosition, rotated));

		}

	}
	else if (m_pattern == BOSS02_PATTERN::PATTERN2 && pTarget != nullptr)
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

void CBoss02::Dash(Vector2 tmpdir)
{
	if (m_isDash == true && m_bJump ==false)
	{
		if (m_Stepback == false)
		{
			m_vPosition.x += m_StepBackSpeed * (-tmpdir.x) * m_fDeltaTime;

			m_StepbackTime -= m_fDeltaTime;


			if (m_StepbackTime <= 0.f)
			{
				m_StepbackTime = .5f;
				m_Stepback = true;
			}


		}
		else
		{
			if (tmpdir.y >= 0)
			{
				tmpdir.y = 0;
			}

			m_vPosition.x += m_DashSpeed * tmpdir.x * m_fDeltaTime;
			m_vPosition.y += 1200 * tmpdir.y * m_fDeltaTime;

			m_DashTime -= m_fDeltaTime;
			if (m_DashTime <= 0.f)
			{
				m_isDash = false;
				m_DashTime = 1.0f;
				m_Stepback = false;
			}

		}
	}
}


void CBoss02::Landed_Platform(CObject* pObj)
{
	float fX = 0.f, fY = 0.f;

	if (CCollisionManager::Check_Rect(this, pObj, &fX, &fY))
	{
		if (fX > fY)	// ���� �浹
		{
			if (m_vPosition.y < pObj->Get_Position().y && m_fSpeedY >= 0.f)		//	�� �浹
			{
				m_fSpeedY = 0.f;
				//m_iPlayerJumpCount = 0;
				m_vPosition.y = pObj->Get_Position().y - (pObj->Get_Size().y / 2.f + m_vSize.y / 2.f);
			}
			else //-------------------------------------------	�� �浹
			{
				//m_fSpeedY = 0.f;
				//m_vPosition.y = pObj->Get_Position().y + (pObj->Get_Size().y / 2.f + m_vSize.y / 2.f);
				//! õ�� �ʿ��ϸ� ����ϱ�
			}
		}

		if (fX < fY)		// �¿� �浹
		{
			if (m_vPosition.x < pObj->Get_Position().x)		//	�� �浹
			{
				m_vPosition.x = pObj->Get_Position().x - (pObj->Get_Size().x / 2.f + m_vSize.x / 2.f);
			}
			else //-------------------------------------------	�� �浹
			{
				m_vPosition.x = pObj->Get_Position().x + (pObj->Get_Size().x / 2.f + m_vSize.x / 2.f);
			}
		}
	}
}