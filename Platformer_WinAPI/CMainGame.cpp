#pragma region Header
#include "pch.h"
#include "CMainGame.h"

#include "CObjectManager.h"
#include "CInputManager.h"

#include "CAbstractFactory.h"

#include "CObject.h"
#include "CPlayer.h"
#pragma endregion

CMainGame::CMainGame() : m_dwTime(GetTickCount()), m_iFPS(0)
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

	// Initialize objects
	CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create());

	
}

void CMainGame::Update()
{
	CInputManager::Get_Instance()->Update();
	CObjectManager::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CObjectManager::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	CObjectManager::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release()
{
	// Release window resources
	ReleaseDC(g_hWnd, m_hDC);

	// Release managers
	CInputManager::Get_Instance()->Destroy_Instance();
	CObjectManager::Get_Instance()->Destroy_Instance();
}

