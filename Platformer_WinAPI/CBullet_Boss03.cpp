#include "pch.h"
#include "CBullet_Boss03.h"

CBullet_Boss03::CBullet_Boss03()
{

}

CBullet_Boss03::~CBullet_Boss03()
{
}

void CBullet_Boss03::Initialize()
{
	CBullet::Initialize();

	m_fDamage = 10.f;
}

int CBullet_Boss03::Update()
{
	return CBullet::Update();
}

void CBullet_Boss03::Late_Update()
{
	CBullet::Late_Update();
}

void CBullet_Boss03::Render(HDC hDC)
{
	CBullet::Render(hDC);
}

void CBullet_Boss03::Release()
{
	CBullet::Release();
}

void CBullet_Boss03::On_Collision(CObject* pObj)
{
	CBullet::On_Collision(pObj);
}

void CBullet_Boss03::Take_Damage(float _fDamage)
{
	CBullet::Take_Damage(_fDamage);
}
