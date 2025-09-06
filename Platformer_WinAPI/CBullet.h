#pragma once

#include "CObject.h"

class CBullet :  public CObject
{
public:
	CBullet();
	virtual ~CBullet();

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;

	virtual void Do_Attack() {};				
	virtual void Take_Damage(float _fDamage) {};	// 플레이어가 주는 데미지를 받는 함수
};

