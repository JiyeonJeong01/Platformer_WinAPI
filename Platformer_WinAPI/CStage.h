#pragma once
#include "Define.h"

class CObj;
class CPlayer;

class CStage abstract
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hdc) PURE;
	virtual void Release() PURE;

private:
};