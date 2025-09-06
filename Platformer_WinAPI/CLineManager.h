#pragma once
#include "CLine.h"

// For testing in Stage04. Can be modified or deleted freely.
// Currently empty
class CLineManager
{
public:
	enum SIDE { LEFT, RIGHT, SIDE_END };

private:
	CLineManager() {}
	~CLineManager();

	CLineManager(const CLineManager& rhs)       = delete;
	CLineManager& operator=(CLineManager& rMgr) = delete;

public:
	void Initialize();
	int  Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	bool Collision_Line(float& rX, float& rY);

public:
	//void Save_Data();
	//bool Load_Data();

private:
	list<CLine*> m_LineList;
	LINEPOINT    m_tLinePoint[SIDE_END];

#pragma region Singleton
public:
	static CLineManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineManager;

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CLineManager* m_pInstance;
#pragma endregion
};
