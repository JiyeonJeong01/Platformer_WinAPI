#include "pch.h"
#include "CPlayer03.h"

#include "CAbstractFactory.h"
#include "CBullet_Player03.h"
#include "CShield.h"

CPlayer03::CPlayer03()
{
	
}

CPlayer03::~CPlayer03()
{
	Release();
}

void CPlayer03::Initialize()
{
	CPlayer::Initialize();

	m_fMaxHP = 100.f;
	m_fHP = m_fMaxHP;

	m_fDamage = 16.f;
}


int CPlayer03::Update()
{
	int result = CPlayer::Update();

	if (result == OBJ_DEAD)
		return OBJ_DEAD;




	return OBJ_NOEVENT;
}

void CPlayer03::Late_Update()
{
	CPlayer::Late_Update();


}

void CPlayer03::Render(HDC hDC)
{
	CPlayer::Render(hDC);

	CUIManager::Get_Instance()->Render_PlayerHP(hDC, this);

	//if (bRightMouseClicked)
	//{
	//	CObjectManager::Get_Instance()->Add_Object(
	//		OBJID::SHIELD, CAbstractFactory<CShield>::Create(SHIELD, ))
	//}
}

void CPlayer03::Release()
{
	CPlayer::Release();
}

void CPlayer03::Update_Components()
{
	CPlayer::Update_Components();

}

void CPlayer03::Handle_KeyInput()
{
	CPlayer::Handle_KeyInput();


}

void CPlayer03::On_Collision(CObject* pObj)
{
	CPlayer::On_Collision(pObj);

	switch (pObj->Get_ObjectID())
	{
	case PLATFORM: break;
	case PLAYER: break;
	case PL_BULLET: break;
	case MONSTER: break;

	case MON_BULLET:
		{
		Vector2 dir = m_vPosition - pObj->Get_Position();
		dir = Vector2::Nomalize(dir);

		m_vPosition.x += dir.x * 15.f;
		m_vPosition.y += dir.y * 30.f;
		}
		
		break;
	case MOUSE: break;
	case SHIELD: break;
	case ITEM: break;
	case OBJ_END: break;
	}
	
}

void CPlayer03::Do_Attack()
{
	CPlayer::Do_Attack();

	
}

void CPlayer03::Take_Damage(float _fDamage)
{
	CPlayer::Take_Damage(_fDamage);

}

