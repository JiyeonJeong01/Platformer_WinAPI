#pragma once
#include "CPlayer.h"

class CPlayer04 final : public CPlayer
{
private:
	// 상태 머신용 enum class 구성
	enum class PLAYER_MOVESTATE
	{
		IDLE = 0,
		RUN,
		JUMP,
		FALL,
		LANDED
	};

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
	void Do_Attack() override;
	void Take_Damage(float _fDamage) override;

private:
	void Update_Components() override;

	float DeltaTime();

	void Move();
	void Gravity();
	void Landed();

	void Decide_MoveState();
	void Apply_MoveState();

private:
	float     m_fDeltaTime;			// 델타타임 저장용 변수
	float     m_fJumpSpeed;			// 점프 속도. - 면 상승 중, + 면 하강 중
	float     m_fGroundY;			// Collision_Line이 전달하는 fY : 착지해야 할 y좌표
	bool      m_bPlayerLanded;		// 플레이어가 착지 중일 때 true
	int       m_iPlayerJump;		// 플레이어가 점프 입력 카운트. 착지하면 0이 됨
	ULONGLONG m_qwDTTimer;			// 델타타임 측정용 타이머 : 현재 플레이어가 생성됨과 동시에 시간이 흐름

	PLAYER_MOVESTATE m_eMoveState;		// 플레이어 이동 상태 머신
};
