#pragma once
#include "CPlayer.h"

class CPlayer04 final : public CPlayer
{
public:
	CPlayer04();
	~CPlayer04() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	int  Get_PlayerJumpCount() { return m_iPlayerJumpCount; }
	int  Get_PlayerMaxJump() { return m_iPlayerMaxJump; }
	bool Get_PlayerLanded() { return m_bPlayerLanded; }

	void Set_PlayerMaxJump(int _iMaxJump) { m_iPlayerMaxJump = _iMaxJump; }

public:
	void On_Collision(CObject* pObj) override;
	void Do_Attack() override;
	void Take_Damage(float _fDamage) override;

private:
	void Update_Components() override;

	void Landed();
	void Jump();
	void Horizontal_Move();
	void Vertical_Move();

private:
	int m_iPlayerJumpCount;			// 플레이어가 점프 입력 카운트. 착지하면 0이 됨
	int m_iPlayerMaxJump;			// 한 번 체공 중 점프 몇 번 가능하게 만들건지

	float m_fGroundY;				// Collision_Line이 전달해 주는, 착지해야 할 y좌표 저장

	bool m_bPlayerLanded;		// 플레이어가 착지 중일 때 true
};
