#pragma once

class CUIManager
{
private:
	CUIManager();
	~CUIManager();

public:
	static CUIManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CUIManager;

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
	static CUIManager* m_pInstance;

};

