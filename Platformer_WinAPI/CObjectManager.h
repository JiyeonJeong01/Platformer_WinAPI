#pragma once
#include "CObject.h"
class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

public:
	CObject* Get_Player()
	{
		return m_ObjList[PLAYER].front();
	}

public:
	void	Add_Object(OBJID eID, CObject* pObj);
	int	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

private:
	list<CObject*>	m_ObjList[OBJ_END];

#pragma region Singleton
public:
	static CObjectManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CObjectManager;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjectManager* m_pInstance;
#pragma endregion
};
