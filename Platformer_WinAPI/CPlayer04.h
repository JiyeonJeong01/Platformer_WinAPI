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
	void Do_Attack() override;
	void Take_Damage(float _fDamage) override;

private:
	void  Update_Components() override;
	float DeltaTime();

private:
	float m_fPlayerBottom;

	float m_fOffsetY = { };

	float m_fJumpSpeed;

	float m_fDeltaTime;

	float m_fGroundY = 0;

	int  m_iPlayerJump;		// 플레이어가 점프 입력을 누를 때, 타이머 지속 동안 true
	//bool m_PlayerLanded;	// 플레이어 착지 중에 true

	ULONGLONG m_qwDTTimer;	// 델타타임 측정용
};
