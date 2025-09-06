#include "pch.h"
#include "CMonster.h"

CMonster::CMonster() : pTarget(nullptr), m_iHP(0), m_iAttackAmount(0)
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
}

int CMonster::Update()
{
	if (m_bDead) return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC hDC)
{
}

void CMonster::Release()
{
}

void CMonster::On_Collision(CObject* pObj)
{
	CObject::On_Collision(pObj);


}
