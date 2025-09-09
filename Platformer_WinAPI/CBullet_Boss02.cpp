#include "pch.h"
#include "CBullet_Boss02.h"

CBullet_Boss02::CBullet_Boss02()
{
}

CBullet_Boss02::~CBullet_Boss02()
{
}

void CBullet_Boss02::Initialize()
{
	m_vSize = Vector2(20, 20);

	m_fSpeedX = 5.f;
	m_fSpeedY = 5.f;

	m_fDamage = 10.f;

}

int CBullet_Boss02::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet_Boss02::Late_Update()
{
	m_vPosition += m_vDirection * m_fSpeedX;
}

void CBullet_Boss02::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CBullet_Boss02::Release()
{
}

void CBullet_Boss02::On_Collision(CObject* pObj)
{
	CObject::On_Collision(pObj);

	switch (pObj->Get_ObjectID())
	{
	case PLAYER:
	{
		if (m_objID == MON_BULLET)
			m_bDead = true;
	}
	break;
	case MONSTER:
	{
		if (m_objID == PL_BULLET)
			m_bDead = true;
	}
	break;
	case PLATFORM:
			m_bDead = true;
		break;
	case PL_BULLET:				  break;
	case MON_BULLET:		      break;
	case MOUSE:					  break;
	case SHIELD:				  break;
	case ITEM:					  break;

	}
}

void CBullet_Boss02::Do_Attack()
{
}

void CBullet_Boss02::Take_Damage(float _fDamage)
{
}
