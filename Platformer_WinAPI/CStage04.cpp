#include "pch.h"
#include "CStage04.h"
#include "CAbstractFactory.h"
#include "CBoss03.h"
#include "CObjectManager.h"
#include "CPlatform.h"
#include "CPlayer04.h"

CStage04::CStage04()
{
}

CStage04::~CStage04()
{
	CStage04::Release();
}

void CStage04::Initialize()
{
	CObjectManager::Get_Instance()
		->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create(PLAYER));

	CObjectManager::Get_Instance()
		->Add_Object(MONSTER, CAbstractFactory<CBoss03>::Create(MONSTER, 1000.f, 200.f));

	// 첫 번째 바닥 : 사선
	Vector2 tPoint[2] =
	{ { 0.f, WINCY - 200.f }, { 300.f, WINCY - 100.f } };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);

	// 두 번째 바닥 : 플랫폼
	CObjectManager::Get_Instance()
		->Add_Object(PLATFORM, CAbstractFactory<CPlatform>::Create(PLATFORM, WINCX >> 1, WINCY - 95.f, 680.f, 10.f));

	// 세 번째 바닥 : 사선
	Vector2 tPoint2[2] =
	{ { WINCX - 300.f, WINCY - 100.f }, { static_cast<float>(WINCX), WINCY - 200.f } };
	CLineManager::Get_Instance()->Create_Line(tPoint2, 2);
}

void CStage04::Update()
{
}

void CStage04::LateUpdate()
{
}

void CStage04::Render(HDC hDC)
{
	CLineManager::Get_Instance()->Render(hDC);
}

void CStage04::Release()
{
}
