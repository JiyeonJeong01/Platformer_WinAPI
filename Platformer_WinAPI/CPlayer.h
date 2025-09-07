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
	virtual void Take_Damage(float _fDamage) {}

	virtual void Scroll_Offset();

#pragma region 석호 버전 점프 구현
	virtual void Landed();
	virtual void Jump();
	virtual void Horizontal_Move();			// 수평 움직임
	virtual void Vertical_Move();			// 점프, 중력에 의한 낙하 등 수직 움직임
private:
	int		  m_iPlayerJump;			// 플레이어가 점프 입력 카운트. 착지하면 0이 됨
	int		  m_iPlayerMaxJump;			// 한 번 체공 중 점프 몇 번 가능하게 만들건지

	float	  m_fGroundY;				// Collision_Line이 전달하는 fY : 착지해야 할 y좌표

	bool	  m_bPlayerLanded;			// 플레이어가 착지 중일 때 true

#pragma endregion

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
