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

	m_fSpeedX = 10.f;
	m_fSpeedY = 10.f;

	m_fDamage = 5.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	m_vPosition += m_vDirection * m_fSpeedX;

	__super::Update_Rect();
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
	{
		m_bDead = true;
	}
	break;
	default:
		break;
	}
}
