#include "pch.h"
#include "CStage03.h"
#include "CAbstractFactory.h"
#include "CBoss03.h"
#include "CCollisionManager.h"
#include "CObjectManager.h"
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
	{
		float   Ystart = WINCY - 100.f;
		Vector2 tPoint[2] =
		{ { 0.f, (Ystart) }, { 300.f, Ystart } };
		CLineManager::Get_Instance()->Create_Line(tPoint, 2);

		Vector2 tPoint2[4] =
		{ { 450.f, Ystart }, { 500.f, Ystart }, { 700.f, Ystart - 200.f }, { 2800.f, Ystart - 200.f } };
		CLineManager::Get_Instance()->Create_Line(tPoint2, 4);

		Vector2 tPoint3[2] =
		{ { 450.f, Ystart - 200.f }, { 600.f, Ystart - 200.f } };
		CLineManager::Get_Instance()->Create_Line(tPoint3, 2);

		Vector2 tPoint4[2] =
		{ { 600.f, 260.f }, { 800.f, 260.f } };
		CLineManager::Get_Instance()->Create_Line(tPoint4, 2);

		Vector2 tPoint5[2] =
		{ { 800.f, 200.f }, { 1000.f, 200.f } };
		CLineManager::Get_Instance()->Create_Line(tPoint5, 2);

		Vector2 tPoint6[2] =
		{ { 1000.f, 130.f }, { 1200.f, 130.f } };
		CLineManager::Get_Instance()->Create_Line(tPoint6, 2);
	}
	

	// Object 추가
	CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer03>::Create(PLAYER));
	CObjectManager::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CBoss03>::Create(MONSTER, 1500, 320));

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
