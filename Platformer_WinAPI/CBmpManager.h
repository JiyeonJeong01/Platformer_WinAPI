#pragma once
#include "CBmp.h"

class CBmpManager
{
private:
	CBmpManager();
	~CBmpManager();

public:
	void		Initialize();
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Img(const TCHAR* pImgKey);
	void		Release();

public:
	static CBmpManager* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBmpManager;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	map<const TCHAR*, CBmp*>		m_mapBit;
	static CBmpManager* m_pInstance;

};

