#include "pch.h"
#include "CInputManager.h"

CInputManager* CInputManager::m_pInstance = nullptr;

void CInputManager::Initialize()
{
	for (vector<int>::iterator it = vKeys.begin(); it != vKeys.end(); it++)
	{
		mKeyInfos.insert({ *it, new InputKeyInfo() });
	}
}

void CInputManager::Update()
{
	CheckKeyInput();
}

void CInputManager::Release()
{
	for_each(mKeyInfos.begin(), mKeyInfos.end(), [](pair<int, InputKeyInfo*> value) { Safe_Delete(value.second); });
}

bool CInputManager::GetKeyDown(int iKey)
{
	return mKeyInfos[iKey]->GetKeyDown();
}

bool CInputManager::GetKey(int iKey)
{
	return mKeyInfos[iKey]->GetKey();
}

bool CInputManager::GetKeyUp(int iKey)
{
	return mKeyInfos[iKey]->GetKeyUp();
}

void CInputManager::CheckKeyInput()
{
	for_each(vKeys.begin(), vKeys.end(), [&](int iKey) {
		if (GetAsyncKeyState(iKey))
		{
			mKeyInfos[iKey]->Set_PrevPressed(mKeyInfos[iKey]->Get_CurrentPressed());
			mKeyInfos[iKey]->Set_CurrentPressed(true);
		}
		else
		{
			mKeyInfos[iKey]->Set_CurrentPressed(false);
		}
		});
}
