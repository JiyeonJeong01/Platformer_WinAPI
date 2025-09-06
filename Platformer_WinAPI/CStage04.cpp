#include "pch.h"
#include "CStage04.h"

#include "CLine.h"

CStage04::CStage04()
{}

CStage04::~CStage04()
{
	CStage04::Release();
}

void CStage04::Initialize()
{
	LINEPOINT tPoint[2] =
	{
		{ 50.f, WINCY - 50.f },
		{ WINCX - 50.f, WINCY - 50.f }
	};

	m_LineList.push_back(new CLine(tPoint[0], tPoint[1]));
}

void CStage04::Update()
{}

void CStage04::LateUpdate()
{}

void CStage04::Render(HDC hDC)
{
	for (auto& pLine : m_LineList)
		pLine->Render(hDC);

	//MoveToEx(hDC, 50.f, 550.f, nullptr);
	//LineTo(hDC, 750.f, 550.f);
}

void CStage04::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), DeleteObj());
	m_LineList.clear();
}

bool CStage04::Collision_Line(float& rX, float& rY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& pLine : m_LineList)
	{
		if (rX >= pLine->Get_Info().tLeft.fPosX
			&& rX < pLine->Get_Info().tRight.fPosX)
			pTargetLine = pLine;
	}

	if (!pTargetLine)
		return false;

	float x1 = pTargetLine->Get_Info().tLeft.fPosX;
	float y1 = pTargetLine->Get_Info().tLeft.fPosY;

	float x2 = pTargetLine->Get_Info().tRight.fPosX;
	float y2 = pTargetLine->Get_Info().tRight.fPosY;

	rY = ((y2 - y1) / (x2 - x1)) * (rX - x1) + y1;
	//! Y = (기울기) * (X - x1) + y1 ((x1, y1) = 직선 위의 한 점)

	return true;
}
