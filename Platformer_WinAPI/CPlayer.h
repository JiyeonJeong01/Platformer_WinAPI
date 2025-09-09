#pragma once
#include "CObject.h"

class CPlayer : public CObject
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

public:
	int  Get_PlayerJumpCount() { return m_iPlayerJumpCount; }
	int  Get_PlayerMaxJump() { return m_iPlayerMaxJump; }
	bool Get_PlayerLanded() { return m_bPlayerLanded; }

	void Set_PlayerMaxJump(int _iMaxJump) { m_iPlayerMaxJump = _iMaxJump; }
	void Set_AttackCooldown(float _fAtkCooldown) { m_fAtkCooldown = _fAtkCooldown; }
	void Set_PlayerLanded(bool _bPlayerLanded) { m_bPlayerLanded = _bPlayerLanded; }

public:
	void On_Collision(CObject* pObj) override;

	virtual void Do_Attack();
	virtual void Take_Damage(float _fDamage);

	virtual void Scroll_Offset();

protected:
	virtual void Handle_KeyInput();
	virtual void Update_Components();

	void Landed_Platform(CObject* pObj);
	void Landed_Line();

	void Jump();

	void Horizontal_Move();
	void Vertical_Move();

protected:
	// 마우스 위치를 바라보는 포신 관련 변수
	Vector2 m_vPosinPosition;
	Vector2 m_mouseDir;
	float   m_fMousePosX = 0;	// 마우스의 x 좌표
	float   m_fMousePosY = 0;	// 마우스의 y 좌표

	// 키 입력 관련 변수
	bool bLeftPressed;
	bool bRightPressed;
	bool bJumpPressed;
	bool bLeftMouseClicked;
	bool bRightMouseClicked;

	// 점프 및 착지 관련 변수
	int   m_iPlayerJumpCount;		// 플레이어가 점프 입력 카운트. 착지하면 0이 됨
	int   m_iPlayerMaxJump;			// 한 번 체공 중 점프 몇 번 가능하게 만들건지
	float m_fGroundY;				// Collision_Line이 전달해 주는, 착지해야 할 y좌표 저장
	bool  m_bPlayerLanded;			// 플레이어가 착지 중일 때 true

	// 공격 딜레이 관련 변수
	float m_fAtkTimer;				// m_fDeltaTime 을 += 로 더해주면 타이머로 사용 가능
	float m_fAtkCooldown;			// 공격간 딜레이 설정, 조절시 공속 바꾸기 가능!

};
