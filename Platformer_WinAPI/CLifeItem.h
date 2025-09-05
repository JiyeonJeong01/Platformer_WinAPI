#pragma once
#include "CItem.h"

class CLifeItem :  public CItem
{
public :
	void Render(HDC _hDC) override;
	void Initialize() override;
	void Apply_Effect(CObject* pObj) override;

private :
	int iHealAmount;
};

