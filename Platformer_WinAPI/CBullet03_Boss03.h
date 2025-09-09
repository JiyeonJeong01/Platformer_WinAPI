#pragma once

#include "CBullet.h"
#include "CBullet02_Boss03.h"

class CBullet03_Boss03 : public CBullet
{
public:

    CBullet03_Boss03();
	virtual ~CBullet03_Boss03();
public:

    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

	void On_Collision(CObject* pObj) override;

    Type   attackType = Type::Charge;
    float  m_chargeTime = 1.0f;
    float  m_gravity = 2500.f;

private:
   
    Vector2 m_center;
    float   m_fAngleDeg = 0.f;
    float   m_fAngSpeed = 1600.f;
	float   m_fRadius = 5.f;
    float   m_fElapsed = 0.f;
};
