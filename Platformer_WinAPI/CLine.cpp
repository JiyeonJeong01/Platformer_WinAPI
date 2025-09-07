#include "pch.h"
#include "CLine.h"

#include "CScrollManager.h"

CLine::CLine()
{
}

CLine::CLine(Vector2& _leftPoint, Vector2& _rIghtPoint)
	: m_tLine(_leftPoint, _rIghtPoint)
{
}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int iScrollX = static_cast<int>(CScrollManager::Get_Instance()->Get_ScrollX());

	MoveToEx(hDC, static_cast<int>(m_tLine.tLeft.x + iScrollX), static_cast<int>(m_tLine.tLeft.y), NULL);
	LineTo(hDC, static_cast<int>(m_tLine.tRight.x + iScrollX), static_cast<int>(m_tLine.tRight.y));
}
