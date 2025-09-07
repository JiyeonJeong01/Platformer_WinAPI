#pragma once

class CStage;
class CObject;

class CStageManager
{
private:
	CStageManager();
	~CStageManager();

public:
	STAGEID	 Get_CurrentStageID() const { return m_currentStageID; }
	CStage*  Get_CurrentStage()   const { return m_currentStage; }
	int		 Get_StageNumber()    const { return m_StageNumber; }

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	void ChangeStage(STAGEID _id);
	void On_CurrentBossDead(CObject* pObj);


private:
	CStage* m_currentStage;
	STAGEID m_currentStageID;

	int		m_StageNumber = 0;
	bool		bGameClear;

#pragma region Singleton
public:
	static CStageManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CStageManager;

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
	static CStageManager* m_pInstance;
#pragma endregion
};
