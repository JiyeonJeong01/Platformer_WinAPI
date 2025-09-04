#pragma once
#include "CObject.h"

template<typename T>
class CAbstractFactory
{
public :
	static CObject* Create()
	{
		CObject* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObject* Create(float _fX, float _fY)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->Set_PosX(_fX);
		pObj->Set_PosY(_fY);

		return pObj;
	}

};

