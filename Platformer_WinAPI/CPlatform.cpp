#include "pch.h"
#include "CPlatform.h"

CPlatform::CPlatform()
{
}

CPlatform::~CPlatform()
{
	CPlatform::Release();
}

void CPlatform::Initialize()
{
}

int CPlatform::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlatform::Late_Update()
{
}

void CPlatform::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlatform::Release()
{
}

void CPlatform::On_Collision(CObject* pObj)
{
	//todo 벽에 피격판정 필요하면 추가

	switch (pObj->Get_ObjectID())
	{
	case PLAYER:
		break;
	case MONSTER:
		break;
	case PL_BULLET:
		break;
	case MON_BULLET:
		break;
	case MOUSE:
		break;
	case SHIELD:
		break;
	case ITEM:
		break;
	default:
		break;
	}
}
