#pragma once

#include "CStage.h"

class CStage02 : public CStage
{
public:
	CStage02();
	virtual ~CStage02();

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

private:

};