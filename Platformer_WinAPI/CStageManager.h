#pragma once

class CStage;
class CObject;

class CStageManager
{
public:
	CStageManager();
	~CStageManager();

public:
	static CStageManager* GetInstance()
	{
		static CStageManager s_Instance;

		return &s_Instance;
	}

	CObject* Get_Player() { return m_pPlayer; }
	STAGEID	 Get_CurrentStageID() { return m_currentStageID; }
	CStage* Get_CurrentStage() { return m_currentStage; }

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC hdc);
	void Release();

public:
	int  ChangeStage( STAGEID _id);
	void Render_StageClear();


private:
	CStage* m_currentStage;
	STAGEID m_currentStageID;

	CObject* m_pPlayer;


// singleton
public :
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


private :
	static CStageManager* m_pInstance;
};
