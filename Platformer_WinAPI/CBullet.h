#pragma once

#include "CObject.h"

class CBullet :  public CObject
{
public:
	CBullet();
	~CBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;
};

