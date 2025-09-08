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

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스 핸들
		pFilePath,  // 파일의 경로
		IMAGE_BITMAP,  // 어떤 타입을 읽어들일 것인가
		0, 0, // 이미지의 가로, 세로 사이즈
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteDC(m_hMemDC);

	DeleteObject(m_hBitmap);
}
