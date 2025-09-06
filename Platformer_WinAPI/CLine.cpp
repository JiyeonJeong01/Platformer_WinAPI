#include "pch.h"
#include "CLine.h"

CLine::CLine()
{
}

CLine::CLine(LINEPOINT& _leftPoint, LINEPOINT& _rIghtPoint)
	: m_tInfo(_leftPoint, _rIghtPoint)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	//int iScrollX = static_cast<int>(CScrollMgr::Get_Instance()->Get_ScrollX());

	 // 1) Save state
	//int  oldROP2 = ::GetROP2(hDC);
	//HRGN hOldRgn = ::CreateRectRgn(0, 0, 0, 0);
	//int  hasClip = ::GetClipRgn(hDC, hOldRgn); // 1이면 클립 존재

	// 2) Force a visible pen (use DC_PEN to avoid leaks)
	//HGDIOBJ hOldPen = ::SelectObject(hDC, ::GetStockObject(DC_PEN));
	//::SetDCPenColor(hDC, RGB(255, 0, 0));       // 확실히 보이는 빨강
	//::SetROP2(hDC, R2_COPYPEN);                 // 안전한 라스터 연산
	//if (hasClip == 1) ::SelectClipRgn(hDC, nullptr); // 일단 클립 해제

	MoveToEx(hDC,
		static_cast<int>(m_tInfo.tLeft.fPosX), // + iScrollX,
		static_cast<int>(m_tInfo.tLeft.fPosY),
		nullptr);
	LineTo(hDC,
		static_cast<int>(m_tInfo.tRight.fPosX), // + iScrollX,
		static_cast<int>(m_tInfo.tRight.fPosY));

	// 4) Restore state
	//if (hasClip == 1) ::SelectClipRgn(hDC, hOldRgn);
	//::SetROP2(hDC, oldROP2);
	//::SelectObject(hDC, hOldPen);
	//::DeleteObject(hOldRgn);
}
