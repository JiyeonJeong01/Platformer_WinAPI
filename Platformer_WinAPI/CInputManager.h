#pragma once

#include "InputKeyInfo.h"

class CInputManager
{
public:
	void Initialize();
	void Update();
	void Release();

public:
	bool GetKeyDown(int iKey);
	bool GetKey(int iKey);
	bool GetKeyUp(int iKey);

	void CheckKeyInput();

private:
	vector<int> vKeys{ VK_SPACE, 'A', 'D' };
	map<int, InputKeyInfo*> mKeyInfos;

// singleton
public :
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
};
