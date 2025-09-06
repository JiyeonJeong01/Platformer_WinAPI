#include "pch.h"
#include "CLineManager.h"

CLineManager* CLineManager::m_pInstance = nullptr;

CLineManager::~CLineManager()
{
	CLineManager::Release();
}

void CLineManager::Initialize()
{
	
}

int CLineManager::Update()
{
	return 0;
}

void CLineManager::Late_Update()
{
	
}

void CLineManager::Render(HDC hDC)
{
	
}

void CLineManager::Release()
{
	
}

bool CLineManager::Collision_Line(float& rX, float& rY)
{
	return false;
}
