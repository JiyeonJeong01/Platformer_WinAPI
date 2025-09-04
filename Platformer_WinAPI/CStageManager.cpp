#include "pch.h"
#include "CStageManager.h"
#include "CStage.h"

CStageManager::CStageManager() : m_currentStageID(STAGE_END), m_pPlayer(nullptr), m_currentStage(nullptr)
{
}

CStageManager::~CStageManager()
{
	Release();
}

void CStageManager::LateUpdate()
{
}

int CStageManager::ChangeStage(STAGEID _id)
{
	return 0;
}

void CStageManager::Render_StageClear()
{
}
