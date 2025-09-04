#include "pch.h"
#include "CStage.h"

#include "CStageManager.h"

CStage::CStage() : m_lastSpawnMS(GetTickCount())
{
}

CStage::~CStage()
{
}

void CStage::Initialize()
{
	//if (auto* obj = CStageManager::GetInstance()->Get_Player())
	//{

	//}

}

void CStage::Update()
{
	//ULONGLONG current = GetTickCount64();

	//// 2초 지났으면 실행
	//if (current - m_lastSpawnMS >= m_spawnInterval)
	//{
	//	Random_ItemSpawn();
	//	m_lastSpawnMS = current;
	//}

	//for (UINT i = 0; i < OBJ_END; ++i)
	//{
	//	for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
	//	{
	//		int iResult = (*iter)->Update();

	//		if (iResult == OBJ_DEAD)
	//		{
	//			Safe_Delete<CObj*>(*iter);
	//			iter = m_ObjList[i].erase(iter);
	//		}
	//		else
	//		{
	//			++iter;
	//		}
	//	}
	//}
}

void CStage::LateUpdate()
{
	//// 아이템 충돌 처리
	//CCollisionMgr::Collision_Item(CSceneMgr::GetInstance()->Get_Player(), m_ObjList[ITEM]);
	//CCollisionMgr::Collision_Item(CSceneMgr::GetInstance()->Get_Player(), m_ObjList[SHIELD]);
	//CCollisionMgr::Collision_Item(CSceneMgr::GetInstance()->Get_Player(), m_ObjList[POTION]);
	////CCollisionMgr::Collision_Item(CSceneMgr::GetInstance()->Get_Player(), m_ObjList[PET]);
	//CCollisionMgr::Collision_Item(CSceneMgr::GetInstance()->Get_Player(), m_ObjList[ERASER_ITEM]);

	//CCollisionMgr::Collision_Circle(m_ObjList[BULLET], m_ObjList[ERASER_BULLET]);


	////CCollisionMgr::Collision_Circle(m_ObjList[BULLET], m_ObjList[ERASER]);

	//for (UINT i = 0; i < OBJ_END; ++i)
	//{
	//	for (auto& iter : m_ObjList[i])
	//	{
	//		iter->Late_Update();
	//	}
	//}
}

void CStage::Render(HDC hdc)
{
	//for (UINT i = 0; i < OBJ_END; ++i)
	//{
	//	for (auto& iter : m_ObjList[i])
	//	{
	//		iter->Render(hdc);
	//	}
	//}
}

void CStage::Release()
{
	//for (UINT i = 0; i < OBJ_END; ++i)
	//{
	//	for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DeleteObj());
	//	m_ObjList[i].clear();
	//}
}

void CStage::Random_ItemSpawn()
{
	//int random = rand() % 4;

	//float randomX = 30 + static_cast<float>(rand()) / RAND_MAX * (WINCX - 30);

	//switch (random)
	//{
	//case 0:
	//	m_ObjList[ITEM].push_back(AbstractFactory<CItem_AddBullet>::Create(randomX, 10));
	//	break;

	//case 1:
	//	m_ObjList[SHIELD].push_back(AbstractFactory<CItem_Shield>::Create(randomX, 10));
	//	break;

	//case 2:
	//	m_ObjList[POTION].push_back(AbstractFactory<CItem_Potion>::Create(randomX, 10));
	//	break;

	//case 3:
	//	m_ObjList[ERASER_ITEM].push_back(AbstractFactory<CItem_Erase>::Create(randomX, 0));
	//	break;
	//}

}