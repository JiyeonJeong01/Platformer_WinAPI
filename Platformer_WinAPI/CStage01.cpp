#include "pch.h"
#include "CStage01.h"

#include "CStageManager.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"

#include "CPlayer.h"
#include "CPlayer01.h"
#include "CMonster.h"
#include "CBoss01.h"

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

	pPlayer = static_cast<CPlayer*>(CAbstractFactory<CPlayer01>::Create());
	CObjectManager::Get_Instance()->Add_Object(PLAYER, pPlayer);
	
	pBoss = static_cast<CMonster*>(CAbstractFactory<CBoss01>::Create());
	pBoss->Set_Target(pPlayer);
	CObjectManager::Get_Instance()->Add_Object(MONSTER, pBoss);

	
	pPlayer->Set_PosX(vPlayerStartPosition.x);
	pPlayer->Set_PosY(vPlayerStartPosition.y);

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
	CObjectManager::Get_Instance()->Release_ObjID(PLAYER);
	CObjectManager::Get_Instance()->Release_ObjID(PL_BULLET);
	CObjectManager::Get_Instance()->Release_ObjID(MON_BULLET);
	CObjectManager::Get_Instance()->Release_ObjID(MONSTER);
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
