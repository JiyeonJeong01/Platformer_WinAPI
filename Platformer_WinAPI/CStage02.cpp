#include "pch.h"
#include "CStage02.h"
#include "CObjectManager.h"
#include "CAbstractFactory.h"
#include "CPlayer02.h"
#include "CMob01.h"
#include "CLineManager.h"

CStage02::CStage02()
{
}

CStage02::~CStage02()
{
	Release();
}

void CStage02::Initialize()
{

	float Ystart = WINCY * 0.8;
	Vector2 tPoint[2] =
	{ {0.f,(Ystart)}, {150.f,Ystart} };
	CLineManager::Get_Instance()->Create_Line(tPoint, 2);	
	Vector2 tPoint2[4] =
	{ {350.f,Ystart},{500.f,Ystart},{700.f,Ystart-200.f},{1000.f,Ystart - 200.f} };
	CLineManager::Get_Instance()->Create_Line(tPoint2, 4);

	Vector2 tPoint3[2] =
	{ {400.f,Ystart - 200.f}, {600.f,Ystart - 200.f} };
	CLineManager::Get_Instance()->Create_Line(tPoint3, 2);


	CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer02>::Create());
	CObjectManager::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMob01>::Create(WINCX * 0.5, WINCY * 0.7));
}

void CStage02::Update()
{
}

void CStage02::LateUpdate()
{
}

void CStage02::Render(HDC hdc)
{
	CLineManager::Get_Instance()->Render(hdc);

}

void CStage02::Release()
{
	CLineManager::Get_Instance()->Release();
}
