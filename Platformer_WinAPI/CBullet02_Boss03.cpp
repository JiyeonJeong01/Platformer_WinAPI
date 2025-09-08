#include "pch.h"
#include "CBullet02_Boss03.h"

CBullet02_Boss03::CBullet02_Boss03()
{

}

CBullet02_Boss03::~CBullet02_Boss03()
{

}

void CBullet02_Boss03::Initialize()
{
	CBullet::Initialize();

	m_vSize = Vector2(100, 100);

	m_fSpeedX = 15.f;
	m_fSpeedY = 15.f;

	m_fDamage = 10.f;
}

int CBullet02_Boss03::Update()
{
	return CBullet::Update();
}

void CBullet02_Boss03::Late_Update()
{
	//CBullet::Late_Update();

}

void CBullet02_Boss03::Render(HDC hDC)
{
	CBullet::Render(hDC);

}

void CBullet02_Boss03::Release()
{
	CBullet::Release();

}

void CBullet02_Boss03::On_Collision(CObject* pObj)
{
	CBullet::On_Collision(pObj);

}

void CBullet02_Boss03::Take_Damage(float _fDamage)
{
	CBullet::Take_Damage(_fDamage);
	
}
