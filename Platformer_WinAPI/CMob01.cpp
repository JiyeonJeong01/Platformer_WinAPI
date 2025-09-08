#include "pch.h"
#include "CMob01.h"
#include "CBullet.h"
#include "CPlayer02.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "Vector2.h"
#include "CLineManager.h"
#include "CUIManager.h"

CMob01::CMob01()
{
}

CMob01::~CMob01()
{
}

void CMob01::Initialize()
{
    m_vPosition = { WINCX *0.5f-100, WINCY *0.5f-50 };
    m_vDirection = { 0.f, 0.f };
    m_vSize = { 40.f, 40.f };

    m_fSpeedX = 10.f;
    m_fSpeedY = 7.f;

    // Boss Status
    m_fMaxHP = 100.f;
    m_fHP = m_fMaxHP;

    m_fDamage = 10.f;

    m_objID = MONSTER;
}

int CMob01::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

    __super::Update_Rect();
    Vector2 pos = CObjectManager::Get_Instance()->Get_Player()->Get_Position();
    Vector2 size = CObjectManager::Get_Instance()->Get_Player()->Get_Size();

    if (pos.y - (size.y*.5f) <= m_vPosition.y && pos.y + (size.y * .5f) >= m_vPosition.y)
    {
       
            ULONGLONG current = GetTickCount64();
        if (current - m_Attack_Interval >= 1000)
        {
            if (0 <= pos.x - m_vPosition.x )
                Do_Attack({1,0});

            else if (0 >= pos.x - m_vPosition.x)
                Do_Attack({-1,0});

            m_Attack_Interval = current;

        }
    }




    float pY=0.f;


    CLineManager::Get_Instance()->Collision_Line(m_vPosition, &pY);


    m_vPosition.y = pY-(m_vSize.y / 2);


	return 0;
}

void CMob01::Late_Update()
{

	
}

void CMob01::Render(HDC hDC)
{
    Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
    //CUIManager::Get_Instance()->Render_BossHP(hDC, this);
    if (m_fHP < m_fMaxHP)
    {
        int iScrollX = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollX());
        int iScrollY = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollY());

        CUIManager::Get_Instance()->DrawHP(hDC, (m_vPosition.x + iScrollX - m_vSize.x * .5f), (m_vPosition.y + iScrollY + m_vSize.y * .5f) + 10, m_vSize.x, 5, m_fHP, m_fMaxHP);
    }
}

void CMob01::Release()
{

}

void CMob01::On_Collision(CObject* pObj)
{
    if (pObj->Get_ObjectID() == PL_BULLET)
    {
        Take_Damage(pObj->Get_Damage());
    }
    else if (pObj->Get_ObjectID() == PLAYER)
    {
        
        if (pObj)
        {
            CPlayer02*  tmp =  dynamic_cast<CPlayer02*>(pObj);
            tmp->Take_Damage(m_fDamage);
        }
    }

}
void CMob01::Take_Damage(float _fDamage)
{
    if (0 <= (m_fHP - _fDamage))
        m_fHP -= _fDamage;
    else
    {
        m_fHP = 0.f;
        m_bDead = true;
    }
}
void CMob01::Do_Attack()
{
    Vector2 dir = { 1,0 };
    CObjectManager::Get_Instance()->Add_Object(MON_BULLET, CAbstractFactory<CBullet>::Create(MON_BULLET,m_vPosition, dir));
}

void CMob01::Do_Attack(Vector2 dir)
{
    CObjectManager::Get_Instance()->Add_Object(MON_BULLET, CAbstractFactory<CBullet>::Create(MON_BULLET,m_vPosition, dir));

}
