#pragma once
#include "CItem.h"
class CPowerItem : public CItem
{
public:
	void Render(HDC _hDC) override;
	void Initialize() override;
	void Apply_Effect(CObject* pObj) override;

private:
	float fPowerUpPercentage;
};

