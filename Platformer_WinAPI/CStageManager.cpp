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

void CStageManager::ChangeStage(STAGEID _id)
{
}

void CStageManager::Render_StageClear()
{
}

void CStageManager::Release()
{
}