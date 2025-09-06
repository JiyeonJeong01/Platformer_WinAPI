#pragma once

#include "CMonster.h"

enum class BOSS_PATTERN { Idle = 1, Attack, None, };

class CBoss03 : public CMonster
{
public:
	CBoss03();
	virtual ~CBoss03();

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;
	void Do_Attack() override;
	void Take_Damage(float _fDamage) override;

private:
	BOSS_PATTERN m_pattern = BOSS_PATTERN::Idle;

	float m_Attack_Interval = 0.f;
};

