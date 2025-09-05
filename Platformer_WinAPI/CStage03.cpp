#include "pch.h"
#include "CStage03.h"

#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CPlayer03.h"

CStage03::CStage03()
{

}

CStage03::~CStage03()
{

}

void CStage03::Initialize()
{
	CStage::Initialize();

	CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer03>::Create());
}

void CStage03::Update()
{
	CStage::Update();
}

void CStage03::LateUpdate()
{
	CStage::LateUpdate();
}

void CStage03::Render(HDC hDC)
{
	CStage::Render(hDC);
}

void CStage03::Release()
{
	CStage::Release();
}
