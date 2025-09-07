#include "pch.h"
#include "CStage03.h"
#include "CAbstractFactory.h"
#include "CBoss03.h"
#include "CCollisionManager.h"
#include "CObjectManager.h"
#include "CPlayer03.h"

class CPlayer02;

CStage03::CStage03()
{

}

CStage03::~CStage03()
{

}

void CStage03::Initialize()
{
	CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer03>::Create(PLAYER));
	CObjectManager::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CBoss03>::Create(MONSTER));

}

void CStage03::Update()
{

}

void CStage03::LateUpdate()
{

}

void CStage03::Render(HDC hDC)
{


}

void CStage03::Release()
{
}
