#include "pch.h"
#include "CObjectManager.h"
#include "CCollisionManager.h"

CObjectManager* CObjectManager::m_pInstance = nullptr;

CObjectManager::CObjectManager() { }

CObjectManager::~CObjectManager()
{
	Release();
}

void CObjectManager::Add_Object(OBJID eID, CObject* pObj)
{
	if (eID >= OBJ_END || pObj == nullptr)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjectManager::Update()
{
	for (UINT i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD)
			{
				Safe_Delete<CObject*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	return 0;
}

void CObjectManager::Late_Update()
{
	for (UINT i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();
		}
	}

	CCollisionManager::Collision_Rect(m_ObjList[PLAYER], m_ObjList[ITEM]);
	CCollisionManager::Collision_Circle(m_ObjList[PL_BULLET], m_ObjList[MONSTER]);
	CCollisionManager::Collision_Circle(m_ObjList[MON_BULLET], m_ObjList[PLAYER]);
  CCollisionManager::Collision_Circle(m_ObjList[MONSTER], m_ObjList[PLAYER]);

#pragma region stage04 : 플레이어 - 플랫폼간 상호작용으로 플랫폼 위 서있기 가능
	CCollisionManager::Collision_Rect(m_ObjList[PLAYER], m_ObjList[PLATFORM]);
#pragma endregion

#pragma region Stage04 : 총알 - 플랫폼간 상호작용 테스트
	CCollisionManager::Collision_Rect(m_ObjList[PL_BULLET], m_ObjList[PLATFORM]);
	CCollisionManager::Collision_Rect(m_ObjList[MON_BULLET], m_ObjList[PLATFORM]);
#pragma endregion

	// 안은수 
	CCollisionManager::Collision_Rect(m_ObjList[MONSTER], m_ObjList[PLATFORM]);

}

void CObjectManager::Render(HDC hDC)
{
	for (UINT i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Render(hDC);
		}
	}
}

void CObjectManager::Release()
{
	for (UINT i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DeleteObj());
		m_ObjList[i].clear();
	}
}

void CObjectManager::Release_ObjID(OBJID eID)
{
	for_each(m_ObjList[eID].begin(), m_ObjList[eID].end(), DeleteObj());
	m_ObjList[eID].clear();
}

list<CObject*>* CObjectManager::Get_ObjList(OBJID eID)
{
	return &m_ObjList[eID];
}
