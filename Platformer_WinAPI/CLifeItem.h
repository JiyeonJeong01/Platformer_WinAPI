#pragma once
#include "CItem.h"

class CLifeItem :  public CItem
{
public :
	void Apply_Effect(CObject* pObj) override;

private :
	int iHealAmount;
};

