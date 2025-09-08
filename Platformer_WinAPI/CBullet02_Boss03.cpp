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
	//CBullet::Initialize();

    float random = float(85 + (rand() % 15));
    m_vSize = Vector2(random, random);

    //m_center = Vector2(400, 400);
    m_center = m_vPosition;
    CUtility::PrintCmd(L"총알 위치 : ", m_vPosition);

    m_fAngleDeg = float(rand() % 360); 
    m_fRadius = 40.f;
    m_fAngSpeed = 240.f; 
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

    float time = DeltaTime();

    if (attackType == Type::Charge)
    {
        // 제자리 공전
       float rad = m_fAngleDeg * (PI / 180.f);
        m_vPosition.x = m_center.x + m_fRadius * cosf(rad);
        m_vPosition.y = m_center.y - m_fRadius * sinf(rad); 

        m_fAngleDeg += m_fAngSpeed * time; 
        m_fElapsed += time;

        // 5초 뒤 발사
        if (m_fElapsed >= 5.f)
        {
            m_fSpeedX = 10.f;
            m_fSpeedY = 10.f;
            
            attackType = Type::Fire;
        }
    }

    else
    {
        m_vPosition.x += m_fSpeedX * time;
        m_vPosition.y += m_fSpeedY * time;
    }


    __super::Update_Rect(); 

	return OBJ_NOEVENT;
}

void CBullet02_Boss03::Late_Update()
{
	CBullet::Late_Update();

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
