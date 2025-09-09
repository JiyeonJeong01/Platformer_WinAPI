#include "pch.h"
#include "CBmpManager.h"

CBmpManager* CBmpManager::m_pInstance = nullptr;

CBmpManager::CBmpManager()
{
}

CBmpManager::~CBmpManager()
{
	Release();
}

void CBmpManager::Initialize()
{
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Background.bmp", L"Dummy");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Background.bmp", L"Background");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Player.bmp", L"Player");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Boss01.bmp", L"Boss01");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Boss02.bmp", L"Boss02");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Boss03.bmp", L"Boss03");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Boss04.bmp", L"Boss04");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Mob01.bmp", L"Mob01");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\Mob02.bmp", L"Mob02");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\ItemLife.bmp", L"ItemLife");
	Insert_Bmp(L"..\\Platformer_WinAPI\\Image\\ItemPower.bmp", L"ItemPower");
}

void CBmpManager::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (m_mapBit.end() == iter)
	{
		CBmp* pBmp = new CBmp;

		pBmp->Load_Bmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}

}

HDC CBmpManager::Find_Img(const TCHAR* pImgKey)
{
	auto		iter = find_if(m_mapBit.begin(), m_mapBit.end(), tagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpManager::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), DeleteMap());
	m_mapBit.clear();
}
