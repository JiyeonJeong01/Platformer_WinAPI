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

public:
	virtual void Do_Attack() {}; 
	virtual void Take_Damage(float _fDamage) {};

private:
	Vector2		m_vPosinPosition;

	float		m_fMousePosX = 0;
	float		m_fMousePosY = 0;

private :
	bool bLeftPressed;
	bool bRightPressed;
	bool bJumpPressed;
	bool bLeftMouseClicked;
};
// todo : 몬스터 플레이어 hp 추가하기 