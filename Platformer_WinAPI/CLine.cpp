#include "pch.h"
#include "CLine.h"

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
	MoveToEx(hDC, (int)m_tLine.tLeft.x , (int)m_tLine.tLeft.y, NULL);
	LineTo(hDC, m_tLine.tRight.x, m_tLine.tRight.y);
}
