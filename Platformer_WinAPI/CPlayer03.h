#pragma once

#include "CPlayer.h"

class CPlayer03 : public CPlayer
{
public:
	CPlayer03();
	virtual ~CPlayer03();

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

