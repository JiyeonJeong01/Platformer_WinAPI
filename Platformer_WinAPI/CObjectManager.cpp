#include "pch.h"
#include "CObjectManager.h"

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

	// CollisionMgr::Collision_RectEx(m_ObjList[PLAYER], m_ObjList[MONSTER]);
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
