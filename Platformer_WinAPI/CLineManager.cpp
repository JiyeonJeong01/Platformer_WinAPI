#include "pch.h"
#include "CLineManager.h"

#include "CStage.h"
#include "CStage04.h"
#include "CStageManager.h"

CLineManager* CLineManager::m_pInstance = nullptr;

CLineManager::~CLineManager()
{
	CLineManager::Release();
}

void CLineManager::Initialize()
{
	CStage* pStage = CStageManager::Get_Instance()->Get_CurrentStage();

	if (auto* pStage04 = dynamic_cast<CStage04*>(pStage))
		m_LineList = pStage04->Get_LineList();
}

int CLineManager::Update()
{
	return 0;
}

void CLineManager::Late_Update()
{
	
}

void CLineManager::Render(HDC hDC)
{
	
}

void CLineManager::Release()
{
	
}

bool CLineManager::Collision_Line(float& rX, float& rY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& pLine : m_LineList)
	{
		if (rX >= pLine->Get_Info().tLeft.fPosX
			&& rX < pLine->Get_Info().tRight.fPosX)
			pTargetLine = pLine;
	}

	if (!pTargetLine)
		return false;

	float x1 = pTargetLine->Get_Info().tLeft.fPosX;
	float y1 = pTargetLine->Get_Info().tLeft.fPosY;

	float x2 = pTargetLine->Get_Info().tRight.fPosX;
	float y2 = pTargetLine->Get_Info().tRight.fPosY;

	rY = ((y2 - y1) / (x2 - x1)) * (rX - x1) + y1;
	//! Y = (기울기) * (X - x1) + y1 ((x1, y1) = 직선 위의 한 점)

	return true;
}