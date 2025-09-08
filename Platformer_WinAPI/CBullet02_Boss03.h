#pragma once

#include "CBullet.h"

enum class Type { Charge, Fire };

class CBullet02_Boss03 : public CBullet
{
public:
	CBullet02_Boss03();
	virtual ~CBullet02_Boss03();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;
	void Take_Damage(float _fDamage) override;

private:
	Type attackType = Type::Charge;

	float      m_fAngleDeg = 0.f;     // 현재 각도(도)
	float      m_fRadius = 40.f;      // 공전 반지름
	float      m_fAngSpeed = 240.f;   // 각속도(도/초)  (= 한 바퀴 1.5초 정도)
	float      m_fElapsed = 0.f;      // 누적 시간(초)
	bool       m_bFired = false;      // 발사했는지
	Vector2    m_center;              // 제자리 기준점(스폰 시점)
};

