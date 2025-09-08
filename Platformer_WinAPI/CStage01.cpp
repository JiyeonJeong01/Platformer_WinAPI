#include "pch.h"
#include "CStage01.h"

#include "CStageManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"

#include "CPlayer.h"
#include "CPlayer01.h"
#include "CMonster.h"
#include "CBoss01.h"
#include "CMob03.h"

#include "CPlatform.h"

CStage01::CStage01()
{
}

CStage01::~CStage01()
{
	Release();
}

void CStage01::Initialize()
{
	bBossDead = false;

	vPlayerStartPosition = { 100.f, 400.f };

	pPlayer = static_cast<CPlayer*>(CAbstractFactory<CPlayer01>::Create(PLAYER));
	CObjectManager::Get_Instance()->Add_Object(PLAYER, pPlayer);

	pBoss = static_cast<CMonster*>(CAbstractFactory<CBoss01>::Create(MONSTER, {1200, 350}));
	pBoss->Set_Target(pPlayer);
	CObjectManager::Get_Instance()->Add_Object(MONSTER, pBoss);


	CMonster* pMob = static_cast<CMonster*>(CAbstractFactory<CMob03>::Create(MONSTER, {700, 400}));
	pMob->Set_Target(pPlayer);
	CObjectManager::Get_Instance()->Add_Object(MONSTER, pMob);

	pMob = static_cast<CMonster*>(CAbstractFactory<CMob03>::Create(MONSTER, { 200, 400 }));
	pMob->Set_Target(pPlayer);
	CObjectManager::Get_Instance()->Add_Object(MONSTER, pMob);

	pPlayer->Set_PosX(vPlayerStartPosition.x);
	pPlayer->Set_PosY(vPlayerStartPosition.y);

	CObjectManager::Get_Instance()->Add_Object(
		PLATFORM,
		CAbstractFactory<CPlatform>::Create(PLATFORM, (WINCX >> 1) - 100.f, 600, 300, 30.f));

	CObjectManager::Get_Instance()->Add_Object(
		PLATFORM,
		CAbstractFactory<CPlatform>::Create(PLATFORM, WINCX, WINCY, WINCX * 3.f, 30.f));

}

void CStage01::Update()
{
	if (bBossDead)
	{
		Request_ChangeStage();
	}
}

void CStage01::LateUpdate()
{
}

void CStage01::Render(HDC hDC)
{
}

void CStage01::Release()
{
}

void CStage01::Request_ChangeStage()
{
	CStageManager::Get_Instance()->ChangeStage(STAGE2);
}

void CStage01::Create_Monster()
{
}

void CStage01::Handle_PlayerDead()
{
	pPlayer->Set_PosX(vPlayerStartPosition.x);
	pPlayer->Set_PosY(vPlayerStartPosition.y);

	pPlayer->Set_HP(pPlayer->Get_MaxHP());
}

void CStage01::Handle_BossDead()
{
}