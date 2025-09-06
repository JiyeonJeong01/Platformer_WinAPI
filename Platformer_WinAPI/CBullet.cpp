#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{

}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_vSize = Vector2(20, 20);

	m_fSpeedX = 5.f;
	m_fSpeedY = 5.f;

	m_fDamage = 10.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	m_vPosition += m_vDirection * m_fSpeedX;
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{

}

void CBullet::On_Collision(CObject* pObj)
{
	CObject::On_Collision(pObj);

	switch (pObj->Get_ObjectID())
	{
	case MONSTER: m_bDead = true; break;
	case PLAYER:  m_bDead = true; break;
	case PL_BULLET:				  break;
	case MON_BULLET:		      break;
	case MOUSE:					  break;
	case SHIELD:				  break;
	case ITEM:					  break;

	}
}
