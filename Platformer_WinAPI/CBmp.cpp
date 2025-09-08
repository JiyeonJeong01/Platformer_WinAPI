#include "pch.h"
#include "CBmp.h"

CBmp::CBmp()
{
}

CBmp::~CBmp()
{
	Release();
}

void CBmp::Load_Bmp(const TCHAR* pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// ���α׷� �ν��Ͻ� �ڵ�
		pFilePath,  // ������ ���
		IMAGE_BITMAP,  // � Ÿ���� �о���� ���ΰ�
		0, 0, // �̹����� ����, ���� ������
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteDC(m_hMemDC);

	DeleteObject(m_hBitmap);
}
