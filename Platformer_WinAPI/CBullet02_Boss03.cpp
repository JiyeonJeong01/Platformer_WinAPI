#include "pch.h"
#include "CBullet02_Boss03.h"

CBullet02_Boss03::CBullet02_Boss03()
{

}

CBullet02_Boss03::~CBullet02_Boss03()
{

}

void CBullet02_Boss03::Initialize()
{
	CBullet::Initialize();

    m_vSize = Vector2(float(80 + (rand() % 20)), float(80 + (rand() % 20)));

    m_center = m_vPosition;

    m_fAngleDeg = float(rand() % 360); 
    m_fRadius = 5.f;
    m_fAngSpeed = 1600.f; 
    m_fElapsed = 0.f;

    m_fDamage = 10.f;

    m_fSpeedX = 0.f; 
    m_fSpeedY = 0.f;
}

int CBullet02_Boss03::Update()
{
	int result = CBullet::Update();

	if (result == OBJ_DEAD)
		return OBJ_DEAD;


    __super::Update_Rect(); 

	return OBJ_NOEVENT;
}

void CBullet02_Boss03::Late_Update()
{
	CBullet::Late_Update();

    m_fDeltaTime = DeltaTime();

    if (attackType == Type::Charge)
    {
        float rad = m_fAngleDeg * (PI / 180.f);
        m_vPosition.x = m_center.x + m_fRadius * cosf(rad);
        m_vPosition.y = m_center.y - m_fRadius * sinf(rad);

        m_fAngleDeg += m_fAngSpeed * m_fDeltaTime;
        m_fElapsed += m_fDeltaTime;

        // 2초 뒤 발사
        if (m_fElapsed >= 2.f)
        {
            m_fSpeedX = 30.f;
            m_fSpeedY = 30.f;

            attackType = Type::Fire;
        }
    }

    else
    {
        m_vPosition.x += m_fSpeedX * m_fDeltaTime;
        m_vPosition.y += m_fSpeedY * m_fDeltaTime;
    }
}

void CBullet02_Boss03::Render(HDC hDC)
{
	CBullet::Render(hDC);

}

void CBullet02_Boss03::Release()
{
	CBullet::Release();

}

void CBullet02_Boss03::On_Collision(CObject* pObj)
{
	CBullet::On_Collision(pObj);

}

void CBullet02_Boss03::Take_Damage(float _fDamage)
{
	CBullet::Take_Damage(_fDamage);
	
}
