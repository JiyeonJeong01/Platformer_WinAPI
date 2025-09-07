#include "pch.h"
#include "CStage04.h"
#include "CAbstractFactory.h"
#include "CObjectManager.h"
#include "CPlayer04.h"

CStage04::CStage04()
{}

CStage04::~CStage04()
{
	CStage04::Release();
}

void CStage04::Initialize()
{
#pragma region Lagacy : 직접 라인 그리던 시절
	/*
	LINEPOINT tPoint[2] =
	{
		{ 50.f, WINCY - 100.f },
		{ WINCX - 50.f, WINCY - 100.f }
	};

	m_LineList.push_back(new CLine(tPoint[0], tPoint[1]));

	CLineManager::Get_Instance()->Initialize();
	 */
#pragma endregion

#pragma region 은수의 노력을 흡수
	float   Ystart    = WINCY - 100.f;
	Vector2 tPoint[2] =
		{ { 0.f, (Ystart) }, { 300.f, Ystart } };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);

	Vector2 tPoint2[4] =
		{ { 450.f, Ystart }, { 500.f, Ystart }, { 700.f, Ystart - 200.f }, { 1000.f, Ystart - 200.f } };
	CLineManager::Get_Instance()->Create_Line(tPoint2, 4);

	Vector2 tPoint3[2] =
		{ { 450.f, Ystart - 200.f }, { 600.f, Ystart - 200.f } };
	CLineManager::Get_Instance()->Create_Line(tPoint3, 2);
#pragma endregion

	CObjectManager::Get_Instance()
		->Add_Object(PLAYER, CAbstractFactory<CPlayer04>::Create(PLAYER));
	//todo 몬스터 만든 후 Create하기
}

void CStage04::Update()
{}

void CStage04::LateUpdate()
{}

void CStage04::Render(HDC hDC)
{
#pragma region 직접 라인 그리던 시절
	/*
	for (auto& pLine : m_LineList)
		pLine->Render(hDC);
	*/
#pragma endregion

	CLineManager::Get_Instance()->Render(hDC);
}

void CStage04::Release()
{
	//for_each(m_LineList.begin(), m_LineList.end(), DeleteObj());
	//m_LineList.clear();
}

bool CStage04::Collision_Line(float& rX, float& rY)
{
	//if (m_LineList.empty())
	//	return false;

	CLine* pTargetLine = nullptr;
	
	//for (auto& pLine : m_LineList)
	//{
	//	if (rX >= pLine->Get_Info().tLeft.fPosX
	//		&& rX < pLine->Get_Info().tRight.fPosX)
	//		pTargetLine = pLine;
	//}

	if (!pTargetLine)
		return false;

	//float x1 = pTargetLine->Get_Info().tLeft.fPosX;
	//float y1 = pTargetLine->Get_Info().tLeft.fPosY;
	//
	//float x2 = pTargetLine->Get_Info().tRight.fPosX;
	//float y2 = pTargetLine->Get_Info().tRight.fPosY;

	//rY = ((y2 - y1) / (x2 - x1)) * (rX - x1) + y1;
	//! Y = (기울기) * (X - x1) + y1 ((x1, y1) = 직선 위의 한 점)

	return true;
}
