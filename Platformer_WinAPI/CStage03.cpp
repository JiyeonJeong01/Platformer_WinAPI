#include "pch.h"
#include "CStage03.h"
#include "CAbstractFactory.h"
#include "CBoss03.h"
#include "CCollisionManager.h"
#include "CObjectManager.h"
#include "CPlatform.h"
#include "CPlayer03.h"
#include "CPlayer04.h"

class CPlayer02;

CStage03::CStage03()
{

}

CStage03::~CStage03()
{

}

void CStage03::Initialize()
{
	// 맵 만들기
	CreateTile();

	// Object 추가
	CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer03>::Create(PLAYER));
	CObjectManager::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CBoss03>::Create(MONSTER, 1200, 620));

}

void CStage03::Update()
{

}

void CStage03::LateUpdate()
{

}

void CStage03::Render(HDC hDC)
{
	CUtility::PrintText(hDC, 50, 200, L"마우스 위치 : ", CInputManager::Get_Instance()->Get_CursorPosition().x, CInputManager::Get_Instance()->Get_CursorPosition().y);

	CLineManager::Get_Instance()->Render(hDC);
}

void CStage03::Release()
{

}

void CStage03::CreateTile()
{
	// 가로
	CObjectManager::Get_Instance()
		->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(PLATFORM, WINCX - 930, 805.f, 2400.f, 30.f));

	// 세로
	CObjectManager::Get_Instance()
		->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(PLATFORM, 0, WINCY - 100, 30.f, 400.f));
}
	