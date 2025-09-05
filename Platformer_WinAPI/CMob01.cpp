#include "pch.h"
#include "CMob01.h"
#include "CBullet.h"
#include "CPlayer02.h"

CMob01::CMob01()
{
}

CMob01::~CMob01()
{
}

void CMob01::Initialize()
{
    m_vPosition = { WINCX >> 1, WINCY - (WINCY >> 2) };
    m_vDirection = { 0.f, 0.f };
    m_vSize = { 40.f, 40.f };

    m_fSpeedX = 10.f;
    m_fSpeedY = 7.f;


    m_objID = MONSTER;
}

int CMob01::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	return 0;
}

void CMob01::Late_Update()
{

	
}

void CMob01::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMob01::Release()
{

}

void CMob01::On_Collision(CObject* pObj)
{
    if(dynamic_cast<CBullet*>(pObj))
    {
        //Get_Damage가 없음 
        //m_iHP-= pObj->Get
    }
    else if (dynamic_cast<CPlayer02*>(pObj))
    {
        // 플레이어에게 데미지 줄거임
    }

}
// Take_Damage 이런 용어 통일 헷갈릴거 같음 
