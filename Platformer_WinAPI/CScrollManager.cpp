#include "pch.h"
#include "CScrollManager.h"

CScrollManager* CScrollManager::m_pInstance = nullptr;

CScrollManager::CScrollManager()
	: m_fScrollX(0), m_fScrollY(0)
{

}

CScrollManager::~CScrollManager()
{
}
