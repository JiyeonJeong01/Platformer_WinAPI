#pragma once

#include "CObject.h"

class CShield : public CObject
{
public:
	CShield();
	virtual ~CShield();

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Set_Target(CObject* pObj) { pTarget = pObj; }

private:
	CObject* pTarget;
};

