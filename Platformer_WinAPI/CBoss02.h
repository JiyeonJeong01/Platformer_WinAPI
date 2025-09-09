#pragma once
#include "CMonster.h"

enum class BOSS02_PATTERN { IDLE, PATTERN1, PATTERN2, MOVE, BP_END };

const static int m_PosinNum = 4;

class CBoss02 :
    public CMonster
{
public:
	CBoss02();
	~CBoss02() override;

public:
	void Initialize() override;
	int	Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;

public:
	virtual void Do_Attack();						// Target을 공격하는 함수, pTarget을 설정해둬야 한다
	virtual void Take_Damage(float _fDamage);		// 플레이어가 주는 데미지를 받는 함수

	Vector2 RotateVector(Vector2& v, float angle);

private:


	BOSS02_PATTERN m_pattern = BOSS02_PATTERN::IDLE;

	float m_Attack_Interval = 0.f;
	DWORD m_Attack_Interval2;

	Vector2 m_BossPosinDir;

	int angle;

	bool m_bJump;

private:

	void Dash(Vector2 tmpdir);

	void Landed_Platform(CObject* pObj);

	bool m_isDash;
	float m_DashSpeed;
	float m_DashTime;
	float m_DashDuration;
	Vector2 tmpdir = {};

	bool m_Stepback;
	float m_StepBackSpeed;
	float m_StepbackTime;
};


