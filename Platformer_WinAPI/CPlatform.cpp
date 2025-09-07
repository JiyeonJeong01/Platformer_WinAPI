#include "pch.h"
#include "CPlatform.h"

CPlatform::CPlatform()
{}

CPlatform::~CPlatform()
{
	CPlatform::Release();
}

void CPlatform::Initialize()
{}

int CPlatform::Update()
{
	return 0;
}

void CPlatform::Late_Update()
{}

void CPlatform::Render(HDC hDC)
{}

void CPlatform::Release()
{}

void CPlatform::On_Collision(CObject* pObj)
{ }
