#include "pch.h"
#include "CStage04.h"

#include "CAbstractFactory.h"
#include "CLine.h"
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
	LINEPOINT tPoint[2] =
	{
		{ 50.f, WINCY - 100.f },
		{ WINCX - 50.f, WINCY - 100.f }
	};

	m_LineList.push_back(new CLine(tPoint[0], tPoint[1]));

	CObjectManager::Get_Instance()
		->Add_Object(PLAYER, CAbstractFactory<CPlayer04>::Create());
	//todo 몬스터 만든 후 Create하기

	CLineManager::Get_Instance()->Initialize();
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
