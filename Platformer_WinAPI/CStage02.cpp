#include "pch.h"
#include "CStage02.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CPlayer02.h"
#include "CMob01.h"

CStage02::CStage02()
{
}

CStage02::~CStage02()
{
}

void CStage02::Initialize()
{
	CStage::Initialize();

	CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer02>::Create());
	CObjectManager::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMob01>::Create(WINCX * 0.5, WINCY * 0.7));
}

void CStage02::Update()
{
	CStage::Update();
}

void CStage02::LateUpdate()
{
	CStage::LateUpdate();
}

void CStage02::Render(HDC hdc)
{
	CStage::Render(hdc);
}

void CStage02::Release()
{
	CStage::Release();
}
