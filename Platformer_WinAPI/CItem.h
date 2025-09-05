#pragma once
#include "CObject.h"
class CItem abstract :  public CObject
{
public :
	CItem() {}
	virtual ~CItem() {}

public :
	void Initialize() override;
	int Update() override;
	void Render(HDC _hDC) override;

public :
	void On_Collision(CObject* pObj) override;

public :
	virtual void Apply_Effect(CObject* pObj) {};
};

