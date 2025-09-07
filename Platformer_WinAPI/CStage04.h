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

public:
	list<CLine*>& Get_LineList() { return m_LineList; }

private:
	//list<CLine*> m_LineList;
	//Vector2      m_tLinePoint[CLineManager::SIDE_END];
	list<CLine*> m_LineList;
};
