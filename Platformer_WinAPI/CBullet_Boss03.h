#pragma once

#include "CBullet.h"

class CBullet_Boss03 : public CBullet
{
public:
	CBullet_Boss03();
	virtual ~CBullet_Boss03();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;
	void Take_Damage(float _fDamage) override;
};

