#include "pch.h"
#include "CBullet03_Boss03.h"

#include "CBullet.h"

CBullet03_Boss03::CBullet03_Boss03()
{
}

CBullet03_Boss03::~CBullet03_Boss03()
{
}

void CBullet03_Boss03::Initialize()
{
	CBullet::Initialize();

	m_vSize = Vector2(80.f, 80.f);

	m_center = m_vPosition;
	m_fAngleDeg = float(rand() % 360);
	m_fRadius = 10.f;
	m_fAngSpeed = 4600.f;
	m_fElapsed = 0.f;

	m_fDamage = 10.f;
	m_fSpeedX = 0.f;
	m_fSpeedY = 0.f;

	attackType = Type::Charge;
	m_chargeTime = 1.f;
	m_gravity = 3000.f;
}

int CBullet03_Boss03::Update()
{
	int result = CBullet::Update();

	if (result == OBJ_DEAD)
		return OBJ_DEAD;


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet03_Boss03::Late_Update()
{
	//CBullet::Late_Update();

	m_fDeltaTime = DeltaTime();
	m_fElapsed += m_fDeltaTime;

	if (attackType == Type::Charge)
	{
		if (m_fElapsed >= m_chargeTime)
		{
			attackType = Type::Fire;

			CObject* player = CObjectManager::Get_Instance()->Get_Player();
			if (!player)
			{
				m_bDead = true;
				return;
			}

			Vector2 pos = m_vPosition;
			Vector2 player_pos = player->Get_Position();
			float   time = 0.95f;
			Vector2 a(0.f, m_gravity);

			// 포물선 공식
			Vector2 v0 = ((player_pos - pos) - (a * 0.5f * time * time)) * (1.f / time);
			m_fSpeedX = v0.x;
			m_fSpeedY = v0.y;
		}
		else
		{
			float rad = m_fAngleDeg * (PI / 180.f);
			m_vPosition.x = m_center.x + m_fRadius * cosf(rad);
			m_vPosition.y = m_center.y - m_fRadius * sinf(rad);
			m_fAngleDeg += m_fAngSpeed * m_fDeltaTime;
		}
	}
	else // Fire 상태
	{
		m_fSpeedY += m_gravity * m_fDeltaTime;

		m_vPosition.x += m_fSpeedX * m_fDeltaTime;
		m_vPosition.y += m_fSpeedY * m_fDeltaTime;
	}
}

void CBullet03_Boss03::Render(HDC hDC)
{
	CBullet::Render(hDC);


}

void CBullet03_Boss03::Release()
{
	CBullet::Release();
}

void CBullet03_Boss03::On_Collision(CObject* pObj)
{
	CBullet::On_Collision(pObj);

	// 플레이어 또는 플랫폼과 충돌 시 삭제
	switch (pObj->Get_ObjectID())
	{
	case PLAYER:
	case PLATFORM:
	{
		for (int i = 0; i < 8; i++)
		{
			float angle = 360.f / 8 * i;
			float radius = angle * (PI / 180.f);

			Vector2 dir = Vector2(cosf(radius), sinf(radius));

			// 음.. 이거 그냥 터지는 이팩트용 bullet을 하나 더 만들어서 그걸로 속도 조절 하는게 낫겠다. Bullet 상속만 받으면 될듯
			CObjectManager::Get_Instance()->Add_Object(
				MON_BULLET, CAbstractFactory<CBullet>::Create(MON_BULLET, m_vPosition, dir));

			// ++ 줄넘기랑 보스 체력 일정이상 깎이면 뒤에서 밀어서 맵으로 강제로 이동? 뭐 이런 느낌 연출
		}
	}
	m_bDead = true;
	break;
	}
}
