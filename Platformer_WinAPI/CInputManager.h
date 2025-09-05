#pragma once

#include "InputKeyInfo.h"

class CInputManager
{
public:
	void Initialize();
	void Update();
	void Release();

public :
	void Check_KeyInput();
	void Check_MouseInput();
	Vector2 Get_CursorPosition() { return m_vCursorPosition;  }

public:
	bool GetKeyDown(int iKey);
	bool GetKey(int iKey);
	bool GetKeyUp(int iKey);

private:
	vector<int> m_vKeys{ VK_SPACE, 'A', 'D', VK_LBUTTON };
	map<int, InputKeyInfo*> m_KeyInfos;

	Vector2 m_vCursorPosition;

#pragma region Singleton
public:
	static CInputManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CInputManager;
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
	static CInputManager* m_pInstance;
#pragma endregion
};
