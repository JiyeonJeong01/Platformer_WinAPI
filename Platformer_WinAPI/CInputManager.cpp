#include "pch.h"
#include "CInputManager.h"

CInputManager* CInputManager::m_pInstance = nullptr;

void CInputManager::Initialize()
{
	for (vector<int>::iterator it = m_vKeys.begin(); it != m_vKeys.end(); it++)
	{
		m_KeyInfos.insert({ *it, new InputKeyInfo() });
	}
}

void CInputManager::Update()
{
	Check_KeyInput();
	Check_MouseInput();
}

void CInputManager::Release()
{
	for_each(m_KeyInfos.begin(), m_KeyInfos.end(), [](pair<int, InputKeyInfo*> value) { Safe_Delete(value.second); });
}

bool CInputManager::GetKeyDown(int iKey)
{
	return m_KeyInfos[iKey]->GetKeyDown();
}

bool CInputManager::GetKey(int iKey)
{
	return m_KeyInfos[iKey]->GetKey();
}

bool CInputManager::GetKeyUp(int iKey)
{
	return m_KeyInfos[iKey]->GetKeyUp();
}

void CInputManager::Check_KeyInput()
{
	for_each(m_vKeys.begin(), m_vKeys.end(), [&](int iKey) {
		if (GetAsyncKeyState(iKey))
		{
			m_KeyInfos[iKey]->Set_PrevPressed(m_KeyInfos[iKey]->Get_CurrentPressed());
			m_KeyInfos[iKey]->Set_CurrentPressed(true);
		}
		else
		{
			m_KeyInfos[iKey]->Set_CurrentPressed(false);
		}
		});
}

void CInputManager::Check_MouseInput()
{
	POINT tPoint;
	GetCursorPos(&tPoint);
	ScreenToClient(g_hWnd, &tPoint);

	m_vCursorPosition.x = tPoint.x;
	m_vCursorPosition.y = tPoint.y;
}