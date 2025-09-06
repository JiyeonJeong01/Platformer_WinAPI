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
    m_vPosition = { WINCX *0.5f, WINCY *0.5f };
    m_vDirection = { 0.f, 0.f };
    m_vSize = { 40.f, 40.f };

    m_fSpeedX = 10.f;
    m_fSpeedY = 7.f;

    m_fHP = 100.f;

    m_objID = MONSTER;
}

int CMob01::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

    Update_Rect();



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
    if(pObj->Get_ObjectID() == BULLET)
    {
        Take_Damage(pObj->Get_Damage());
    }
    else if (dynamic_cast<CPlayer02*>(pObj))
    {
        // 플레이어에게 데미지 줄거임
        if (pObj)
        {
            pObj->Set_Damage(m_fDamage);
        }
    }

}
void CMob01::Take_Damage(float _fDamage)
{
    if (0 <= (m_fHP - _fDamage))
        m_iHP -= _fDamage;
    else
    {
        m_fHP = 0.f;
        m_bDead = true;
    }
}
// Take_Damage 이런 용어 통일 헷갈릴거 같음 
