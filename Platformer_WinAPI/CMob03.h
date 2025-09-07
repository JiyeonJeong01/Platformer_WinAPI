#pragma once
#include "CMonster.h"
class CMob03 :  public CMonster
{
public:
	CMob03();
	~CMob03() override;

public:
	void Initialize() override;
	int	Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;
	void Take_Damage(float _fDamage) override;
	void Do_Attack() override;

	void Decide_State();
	void Idle_State();
	void Attack_State();
	void Move_State();

private:
	float fTransitTime = 5.f;
	ULONGLONG llElapsedTime;
	int	iStateIndex;
	int	iTotalState;

	int	iLastDirection;
	float fShotTime;
	ULONGLONG fShotTimeLog;

	ULONGLONG	fIdleElapsedTime;


	void(CMob03::* currentState)();
};
