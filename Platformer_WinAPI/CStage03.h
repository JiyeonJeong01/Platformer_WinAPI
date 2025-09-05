#pragma once

#include "CStage.h"

class CStage03 : public CStage
{
public:
	CStage03();
	virtual ~CStage03();

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

private:

};

