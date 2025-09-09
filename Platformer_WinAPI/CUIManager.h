#pragma once

class CObject;

enum class HP_DIR { LeftToRight, RightToLeft };

class CUIManager
{
private:
	CUIManager();
	~CUIManager();

public:
	void Initialize();
	void Update();
	void Render(HDC hDC);
	void Release();

public:
	void Render_Stage(HDC hDC);

	void Render_PlayerHP(HDC hDC, CObject* pObj);
	void Render_BossHP(HDC hDC, CObject* pObj);

	void DrawHP(HDC hDC, float x, float y, float width, float height,
		float Hp, float MaxHp, HP_DIR dir = HP_DIR::LeftToRight);

	void Render_GameClear(HDC hDC);

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



