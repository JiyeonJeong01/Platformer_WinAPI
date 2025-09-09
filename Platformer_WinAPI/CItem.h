#pragma once
#include "CObject.h"
class CItem :  public CObject
{
public :
	CItem() {}
	virtual ~CItem() {}

public :
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Release() override {}

public :
	void On_Collision(CObject* pObj) override;

public :
	virtual void Apply_Effect(CObject* pObj) {}
};

