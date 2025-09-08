#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
	: pTarget(nullptr), m_iMonsterJumpCount(0), m_iMonsterMaxJump(0), m_fGroundY(0), m_bMonsterLanded(false)
{}

CMonster::~CMonster()
{}

void CMonster::Initialize()
{}

int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{}

void CMonster::Render(HDC hDC)
{}

void CMonster::Release()
{}

void CMonster::On_Collision(CObject* pObj)
{
	CObject::On_Collision(pObj);
}

void CMonster::Landed_Platform(CObject* pObj)
{}

void CMonster::Landed_Line()
{}

void CMonster::Jump()
{}

void CMonster::Horizontal_Move()
{}

void CMonster::Vertical_Move()
{}
