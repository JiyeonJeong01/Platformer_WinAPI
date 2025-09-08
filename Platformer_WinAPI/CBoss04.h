#pragma once
#include "CMonster.h"

class CBoss04 final : public CMonster
{
private:
	enum class BOSS04_STATE
	{
		IDLE = 0,
		ATTACK_01,
		ATTACK_02,
		NONE
	};

public:
	CBoss04();
	~CBoss04() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;
	void Take_Damage(float _fDamage) override;

private:
	//todo 필요할 경우 여기에 보스어택 매니저 구현

	void Attack01();
	void Attack02();

private:
	BOSS04_STATE m_eBossState;

	float m_fBossAtkTimer;

	bool m_bTalk_Idle;
};
