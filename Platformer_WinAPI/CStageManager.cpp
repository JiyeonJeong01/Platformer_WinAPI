#include "pch.h"
#include "CStageManager.h"
#include "CStage.h"
#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"
#include "CStage04.h"

#include "CItem.h"
#include "CLifeItem.h"
#include "CPowerItem.h"
#include "CAbstractFactory.h"

CStageManager* CStageManager::m_pInstance = nullptr;

CStageManager::CStageManager() : m_currentStageID(STAGE_END), m_currentStage(nullptr)
{
}

CStageManager::~CStageManager()
{
	Release();
}

void CStageManager::Initialize()
{
	fItemDropRate = 0.4f;
	fCurrentDamage = -1.f;
	bGameClear = false;
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
		fItemDropRate = 0.4f;
		m_StageNumber = 1;
		break;

	case STAGEID::STAGE2:
		newStage = new CStage02();
		m_StageNumber = 2;
		fItemDropRate = 0.3f;
		break;

	case STAGEID::STAGE3:
		newStage = new CStage03();
		m_StageNumber = 3;
		fItemDropRate = 0.2f;
		break;

	case STAGEID::STAGE4:
		newStage = new CStage04();
		m_StageNumber = 4;
		fItemDropRate = 0.1f;
		break;

	case STAGEID::STAGE_END:
		break;
	}

	// 기존 스테이지 할당 해제
	Safe_Delete(m_currentStage);
	for (int i = 0; i < OBJ_END; ++i)
	{
		CObjectManager::Get_Instance()->Release_ObjID((OBJID)i);
	}

	// 새로운 스타이지 할당
	m_currentStage = newStage;
	m_currentStageID = _id;

	m_currentStage->Initialize();
}

void CStageManager::On_CurrentBossDead(CObject* pObj)
{
	if (m_currentStageID <= STAGE3)
	{
		ChangeStage(STAGEID(m_currentStageID + 1));
	}
	else if (m_currentStageID == STAGE4)
	{
		bGameClear = true;
	}
}

void CStageManager::On_MobDead(CObject* pObj)
{
	int iTotalCount = 1;

	float fDropRate = (float)(rand() % 11);
	if (/*fDropRate <= fItemDropRate*/true) // 100% drop for test!!!!!
	{
		int iRand = rand() % (iTotalCount);

		switch (iRand)
		{
		case 0:
			CObjectManager::Get_Instance()->Add_Object(ITEM,
				CAbstractFactory<CPowerItem>::Create(ITEM, pObj->Get_Position()));
			break;
		case 1:
			CObjectManager::Get_Instance()->Add_Object(ITEM,
				CAbstractFactory<CLifeItem>::Create(ITEM, pObj->Get_Position()));
			break;
		}
	}
}

void CStageManager::On_PlayerDead(STAGEID sID, CObject* pObj)
{
	fCurrentDamage = pObj->Get_Damage();

	for (int i = 0; i < OBJ_END; ++i)
	{
		CObjectManager::Get_Instance()->Release_ObjID((OBJID)i);
	}
	
	m_currentStage->Initialize();

	CObjectManager::Get_Instance()->Get_Player()->Set_Damage(fCurrentDamage);
}

void CStageManager::Release()
{
	Safe_Delete(m_currentStage);
}
