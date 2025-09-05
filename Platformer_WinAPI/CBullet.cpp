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
	m_vSize = Vector2(40, 40);

}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{

}

void CBullet::Render(HDC hDC)
{

}

void CBullet::Release()
{

}

void CBullet::On_Collision(CObject* pObj)
{
	CObject::On_Collision(pObj);


}
