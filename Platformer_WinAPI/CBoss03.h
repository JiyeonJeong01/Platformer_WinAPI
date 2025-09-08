#pragma once

#include "CMonster.h"
#include <unordered_map>

enum class BOSS_STATE { Idle = 0, Attack1, Attack2, Attack3, None, };

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
	void Attack1();
	void Attack2();
	void Attack3();

private:
	BOSS_STATE m_pattern = BOSS_STATE::Idle;

	Vector2		m_PlayerDir = { };

	float m_Attack1_Time = 0.0f;
	float m_Attack2_Time = 0.0f;

	int	  m_Attack2_Count = 0;

	unordered_map<BOSS_STATE, float> m_PatternTimers;
};

