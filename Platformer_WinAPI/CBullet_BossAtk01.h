#pragma once
#include "CBullet.h"

//! 보스 공격1 전용 총알 : 가속하는 총알

class CBullet_BossAtk01 final : public CBullet
{
public:
	CBullet_BossAtk01();
	~CBullet_BossAtk01() override;

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
};
