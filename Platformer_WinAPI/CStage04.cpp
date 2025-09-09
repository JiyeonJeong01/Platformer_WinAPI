#include "pch.h"
#include "CStage04.h"
#include "CAbstractFactory.h"
#include "CBoss04.h"
#include "CObjectManager.h"
#include "CPlatform.h"
#include "CPlayer04.h"

CStage04::CStage04()
{}

CStage04::~CStage04()
{
	CStage04::Release();
}

void CStage04::Initialize()
{
	CObjectManager::Get_Instance()
		->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create(PLAYER));

	CObjectManager::Get_Instance()
		->Add_Object(MONSTER, CAbstractFactory<CBoss04>::Create(MONSTER, 1000.f, 400.f));

	// 1. 바닥 : 플랫폼
	CObjectManager::Get_Instance()
		->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(PLATFORM, WINCX >> 1, WINCY, 3000.f, 300.f));

	// 2. 왼쪽 외벽 : 플랫폼
	CObjectManager::Get_Instance()
		->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(PLATFORM, -500.f, 265.f, 100.f, WINCY));

	// 3. 오른쪽 외벽 : 플랫폼
	CObjectManager::Get_Instance()
		->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(PLATFORM, WINCX + 500.f, 265.f, 100.f, WINCY));

	// 4. 가운데 언덕 : 플랫폼
	CObjectManager::Get_Instance()
		->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(PLATFORM, WINCX >> 1, 495.f, 300.f, 150.f));

	// 5. 언덕 왼쪽 경사 : 선
	Vector2 tPoint[2] =
		{ { (WINCX >> 1) - 250.f, 570.f }, { (WINCX >> 1) - 150.f, 450.f } };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);

	// 6. 언덕 오른쪽 경사 : 선
	Vector2 tPoint2[2] =
		{ { (WINCX >> 1) + 150.f, 450.f }, { (WINCX >> 1) + 250.f, 570.f } };
	CLineManager::Get_Instance()->Create_Line(tPoint2, 2);
}

void CStage04::Update()
{}

void CStage04::LateUpdate()
{}

void CStage04::Render(HDC hDC)
{
	CLineManager::Get_Instance()->Render(hDC);
}

void CStage04::Release()
{}
