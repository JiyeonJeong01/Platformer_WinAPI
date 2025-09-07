#include "pch.h"
#include "CPlatform.h"

CPlatform::CPlatform()
{}

CPlatform::~CPlatform()
{
	CPlatform::Release();
}

void CPlatform::Initialize()
{}

int CPlatform::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlatform::Late_Update()
{}

void CPlatform::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlatform::Release()
{}

void CPlatform::On_Collision(CObject* pObj)
{
	//todo 벽이 맞으면 부서지게 만들고 싶은건가? 이걸 수정하시게

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
