#pragma once

#include "CStage.h"
class CMonster;

class CStage01 : public CStage
{
public:
	CStage01();
	virtual ~CStage01();

public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

public :
	void Request_ChangeStage();
	void Create_Monster();
	void Handle_PlayerDead();
	void Handle_BossDead();

private:
	int iMonsterSpawnLimit;
	int iCurrentMonsterCount;
	float fSpawnTime;

	float fItemDropRate;

	bool bBossDead;

private :
	CPlayer* pPlayer;
	CMonster* pBoss;

	Vector2 vPlayerStartPosition;

	vector<LINE*> m_vEnvironment;
};