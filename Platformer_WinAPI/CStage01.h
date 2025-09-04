#pragma once
#include "CStage.h"
class CStage01 : public CStage
{
public:
	CStage01();
	virtual ~CStage01();

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;
	void Release() override;

private:
	int	m_iKillCount = 0;
};