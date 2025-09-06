#pragma once
#include "CPlayer.h"
class CPlayer01 : public CPlayer
{
public:
	CPlayer01() {};					// base -> derived
	~CPlayer01() override {};	// derived -> base

public:
	void Initialize() override;
	int  Update() override;

public :
	void Do_Attack() override;
	void Take_Damage(float _fDamage) override;




};

