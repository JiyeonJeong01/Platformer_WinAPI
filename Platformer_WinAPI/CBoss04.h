#pragma once
#include "CMonster.h"

class CBoss04 final : public CMonster
{
private:
	enum class BOSS04_STATE
	{
		IDLE = 0,
		ATTACK_01,			// 플레이어 방향으로 가속하는 총알 3발 흩뿌리기
		ATTACK_02,			// 플레이어 방향으로 한 번 점프
		ATTACK_03,			// 중력이 있는 총알을 플레이어 위로 떨어지도록 난사하기
		NONE
	};

	/*
	 내가 사용 가능한 잡몹을 하나 만들고, 보스 패턴으로 소환해서, 슬라임처럼 지속적으로 내쪽으로 뛰어오게 만들기
	 */

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
	void Attack03();

private:
	BOSS04_STATE m_eBossState;

	float m_fBossStateTimer;		// 보스 상태 전환 타이머
	float m_fBossAtkTimer;			// 보스 공격 타이머

	bool m_bCanAttack;				// 한 상태 동안 한 번만 공격이 나오는 패턴에서는 false로 바꾸기
};
