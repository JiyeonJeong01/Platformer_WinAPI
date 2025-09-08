#pragma once
#include "CObject.h"

template <typename T>
class CAbstractFactory
{
public:
	static CObject* Create(OBJID _eObjID)
	{
		CObject* pObj = new T;
		pObj->Initialize();

		pObj->Set_ObjectID(_eObjID);

		return pObj;
	}

	static CObject* Create(OBJID _eObjID, float _fX, float _fY)
	{
		CObject* pObj = new T;
		pObj->Initialize();

		pObj->Set_ObjectID(_eObjID);

		pObj->Set_PosX(_fX);
		pObj->Set_PosY(_fY);

		return pObj;
	}

	static CObject* Create(OBJID _eObjID, float _fPosX, float _fPosY, float _fSizeX, float _fSizeY)
	{
		CObject* pObj = new T;
		pObj->Initialize();

		pObj->Set_ObjectID(_eObjID);

		pObj->Set_PosX(_fPosX);
		pObj->Set_PosY(_fPosY);

		pObj->Set_SizeX(_fSizeX);
		pObj->Set_SizeY(_fSizeY);

		return pObj;
	}

	static CObject* Create(OBJID _eObjID, Vector2 _position)
	{
		CObject* pObj = new T;

		pObj->Set_ObjectID(_eObjID);

		pObj->Set_PosX(_position.x);
		pObj->Set_PosY(_position.y);
		pObj->Initialize();

		return pObj;
	}

	static CObject* Create(OBJID _eObjID, Vector2 _position, Vector2 _dir)
	{
		CObject* pObj = new T;

		pObj->Set_ObjectID(_eObjID);

		pObj->Set_PosX(_position.x);
		pObj->Set_PosY(_position.y);

		pObj->Set_DirX(_dir.x);
		pObj->Set_DirY(_dir.y);

		pObj->Initialize();

		return pObj;
	}

	static CObject* Create(OBJID _eObjID, Vector2 _position, CObject* _target)
	{
		CObject* pObj = new T;

		pObj->Set_ObjectID(_eObjID);

		pObj->Set_PosX(_position.x);
		pObj->Set_PosY(_position.y);

		pObj->Set_Target(_target);

		pObj->Initialize();

		return pObj;
	}
};
