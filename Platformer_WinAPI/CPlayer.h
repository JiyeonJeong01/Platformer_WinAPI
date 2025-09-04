#pragma once
#include "CObject.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer() override;

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void		Handle_KeyInput();
	void		Update_Components();

private :
	bool bLeftPressed;
	bool bRightPressed;
	bool bJumpPressed;
};
