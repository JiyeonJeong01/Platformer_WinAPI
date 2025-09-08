#pragma once
#include "CBullet.h"

class CBullet04 final : public CBullet
{
public:
	CBullet04();
	~CBullet04() override;

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
