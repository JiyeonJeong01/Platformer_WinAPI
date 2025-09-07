#pragma once
#include "CPlayer.h"

//! 현재 깡통임. 그냥 부모 플레이어를 쓰자

class CPlayer04 final : public CPlayer
{
public:
	CPlayer04();
	~CPlayer04() override;

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
	void Update_Components() override;
};
