#pragma once
#include "CObject.h"

class CPlayer :  public CObject
{
public:
	CPlayer();
	~CPlayer() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	virtual void		Handle_KeyInput();
	virtual void		Update_Components();

public:
	virtual void Do_Attack(); 
	virtual void Take_Damage(float _fDamage) {};

	virtual void Scroll_Offset();

protected:
	Vector2		m_vPosinPosition;

	float		m_fMousePosX = 0;	// 마우스의 x 좌표
	float		m_fMousePosY = 0;	// 마우스의 y 좌표

	Vector2		m_mouseDir;

protected:
	bool		bLeftPressed;
	bool		bRightPressed;
	bool		bJumpPressed;
	bool		bLeftMouseClicked;

};
