#include "pch.h"
#include "CStageManager.h"
#include "CStage.h"
#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"
#include "CStage04.h"

CStageManager* CStageManager::m_pInstance = nullptr;

CStageManager::CStageManager() : m_currentStageID(STAGE_END), m_currentStage(nullptr)
{
}

CStageManager::~CStageManager()
{

}

void CStageManager::Initialize()
{

}

void CStageManager::Update()
{
	if (m_currentStage)
		m_currentStage->Update();
}

void CStageManager::Render(HDC hDC)
{
	if (m_currentStage)
		m_currentStage->Render(hDC);
}

void CStageManager::Late_Update()
{
	if (m_currentStage)
		m_currentStage->LateUpdate();
}

void CStageManager::ChangeStage(STAGEID _id)
{
	if (m_currentStageID == _id)
		return;

	CStage* newStage = nullptr;

	switch (_id)
	{
	case STAGEID::STAGE1:
		newStage = new CStage01();
		m_StageNumber = 1;
		break;

	case STAGEID::STAGE2:
		newStage = new CStage02();
		m_StageNumber = 2;
		break;

	case STAGEID::STAGE3:
		newStage = new CStage03();
		m_StageNumber = 3;
		break;

	case STAGEID::STAGE4:
		newStage = new CStage04();
		m_StageNumber = 4;
		break;

	case STAGEID::STAGE_END:
		break;
	}

	// 기존 스테이지 할당 해제
	Safe_Delete(m_currentStage);

	// 새로운 스타이지 할당
	m_currentStage = newStage;
	m_currentStageID = _id;

	m_currentStage->Initialize();
}

void CStageManager::Release()
{
	Safe_Delete(m_currentStage);
}

