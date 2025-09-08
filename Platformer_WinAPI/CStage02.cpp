#include "pch.h"
#include "CStage02.h"
#include "CAbstractFactory.h"
#include "CPlayer02.h"
#include "CPlayer03.h"
#include "CMob01.h"
#include "CBoss02.h"

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
	Vector2 tPoint2[6] =
	{ {350.f,Ystart},{500.f,Ystart},{700.f,Ystart - 200.f},{1000.f,Ystart - 200.f} ,{ 1000.f ,Ystart },{3000.f ,Ystart} };
	CLineManager::Get_Instance()->Create_Line(tPoint2, 6);


	Vector2 tPoint3[2] =
	{ {400.f,Ystart - 200.f}, {600.f,Ystart - 200.f} };
	CLineManager::Get_Instance()->Create_Line(tPoint3, 2);

	Vector2 tPoint4[2] =
	{ {2000.f,(Ystart)-100}, {2100.f,Ystart-100} };
	CLineManager::Get_Instance()->Create_Line(tPoint4, 2);

	Vector2 tPoint5[2] =
	{ {1700.f,(Ystart)-100}, {1800.f,Ystart - 100} };
	CLineManager::Get_Instance()->Create_Line(tPoint5, 2);

	Vector2 tPoint6[2] =
	{ {1800.f,(Ystart)-200}, {2000.f,Ystart - 200} };
	CLineManager::Get_Instance()->Create_Line(tPoint6, 2);

	CObjectManager::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer02>::Create(PLAYER));
	CObjectManager::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CMob01>::Create(MONSTER));
	CObjectManager::Get_Instance()->Add_Object(MONSTER, CAbstractFactory<CBoss02>::Create(MONSTER));
}

void CStage02::Update()
{
}

void CStage02::LateUpdate()
{
}

void CStage02::Render(HDC hDC)
{
	CLineManager::Get_Instance()->Render(hDC);

}

void CStage02::Release()
{
	CLineManager::Get_Instance()->Release();
}
