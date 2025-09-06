#pragma region Header
#include "pch.h"
#include "CMainGame.h"

#include "CObjectManager.h"
#include "CInputManager.h"

#include "CAbstractFactory.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CStageManager.h"
#pragma endregion

CMainGame::CMainGame() : m_hDC(nullptr), m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	// Initialize window resources
	m_hDC = GetDC(g_hWnd);

	// Dubble buffering
	{
		GetClientRect(g_hWnd, &m_rect);

		m_hDC_back = CreateCompatibleDC(m_hDC);
		m_bmpBack = CreateCompatibleBitmap(m_hDC, m_rect.right, m_rect.bottom);
		HBITMAP prev = (HBITMAP)::SelectObject(m_hDC_back, m_bmpBack);
		DeleteObject(prev);
	}

	// Initialize managers
	CInputManager::Get_Instance()->Initialize();

	// Initialize objects
	// CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create());

	// Start Stage
#pragma region Stage4 test
	CStageManager::Get_Instance()->ChangeStage(STAGE4);
#pragma endregion
}

void CMainGame::Update()
{
	CInputManager::Get_Instance()->Update();
	CObjectManager::Get_Instance()->Update();
	CStageManager::Get_Instance()->Update();

}

void CMainGame::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
	CStageManager::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	// Dubble buffering
	{
		BitBlt(m_hDC, 0, 0, m_rect.right, m_rect.bottom, m_hDC_back, 0, 0, SRCCOPY);
		PatBlt(m_hDC_back, 0, 0, m_rect.right, m_rect.bottom, WHITENESS);
	}

	CObjectManager::Get_Instance()->Render(m_hDC_back);
	CStageManager::Get_Instance()->Render(m_hDC_back);

	// Print Stage
	int stageNumber = CStageManager::Get_Instance()->Get_StageNumber();
	CUtility::PrintText(m_hDC_back, 50, 50, L"Stage : ", stageNumber);

}

void CMainGame::Release()
{
	// Release window resources
	ReleaseDC(g_hWnd, m_hDC);
	ReleaseDC(g_hWnd, m_hDC_back);

	// Release managers
	CInputManager::Get_Instance()->Release();
	CInputManager::Destroy_Instance();

	CObjectManager::Destroy_Instance();

	CStageManager::Get_Instance()->Release();
	CStageManager::Destroy_Instance();
}

