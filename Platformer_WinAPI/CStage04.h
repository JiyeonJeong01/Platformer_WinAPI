#pragma once
#include "CLineManager.h"
#include "CStage.h"

class CLine;

class CStage04 final : public CStage
{
public:
	CStage04();
	~CStage04() override;

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
};
