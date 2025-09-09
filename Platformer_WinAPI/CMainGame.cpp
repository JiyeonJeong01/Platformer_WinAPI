#pragma region Header
#include "pch.h"
#include "CMainGame.h"

#include "CObjectManager.h"
#include "CInputManager.h"

#include "CAbstractFactory.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CStageManager.h"
#include "CUIManager.h"
#include "CLineManager.h"

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

	// Initialize managers
	CInputManager::Get_Instance()->Initialize();
	CUIManager::Get_Instance()->Initialize();
	CStageManager::Get_Instance()->Initialize();
	CBmpManager::Get_Instance()->Initialize();

	// Start Stage
	CStageManager::Get_Instance()->ChangeStage(STAGE1);

}

void CMainGame::Update()
{
	CInputManager::Get_Instance()->Update();
	CObjectManager::Get_Instance()->Update();
	CStageManager::Get_Instance()->Update();
	CUIManager::Get_Instance()->Update();

}

void CMainGame::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
	CStageManager::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC	hBackDC = CBmpManager::Get_Instance()->Find_Img(L"Dummy");
	HDC	hBackroundDC = CBmpManager::Get_Instance()->Find_Img(L"Background");

	BitBlt(hBackDC, 0, 0, WINCX, WINCY, hBackroundDC, 0, 0, SRCCOPY);

	if (CStageManager::Get_Instance()->Get_GameClear())
	{
		CUIManager::Get_Instance()->Render_GameClear(m_hDC);
		return;
	}
	CObjectManager::Get_Instance()->Render(hBackDC);
	CStageManager::Get_Instance()->Render(hBackDC);
	CUIManager::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);
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
	CStageManager::Destroy_Instance();
	CUIManager::Destroy_Instance();
	CLineManager::Destroy_Instance();
	CScrollManager::Destroy_Instance();
}

