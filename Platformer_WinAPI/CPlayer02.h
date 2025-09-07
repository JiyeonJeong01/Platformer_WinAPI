#pragma once
#include "CPlayer.h"
class CPlayer02 :
    public CPlayer
{
public:
	CPlayer02();
	~CPlayer02() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	void Posin_Pos();
	void Do_Attack();
	void Take_Damage(float _fDamage);
	void		On_Collision(CObject* pObj);
	//void		Update_Components();

	//void Jumping();

	//bool m_bJump;
	//float m_fTime;
	//bool isStart;
	//float tmp;


	DWORD sz_Time;

private:
	ULONGLONG m_qwDTTimer;			// 델타타임 측정용 타이머 : 현재 플레이어가 생성됨과 동시에 시간이 흐름
	float     m_fDeltaTime;			// 델타타임 저장용 변수

	int m_iPlayerJump;				// 플레이어가 점프 입력 카운트. 착지하면 0이 됨
	int m_iPlayerMaxJump;			// 한 번 체공 중 점프 몇 번 가능하게 만들건지

	float m_fGroundY;				// Collision_Line이 전달하는 fY : 착지해야 할 y좌표

	bool m_bPlayerLanded;			// 플레이어가 착지 중일 때 true
private:

	void Update_Components() override;

	float DeltaTime();

	void Landed();
	void Jump();
	void Horizontal_Move();			// 수평 움직임
	void Vertical_Move();			// 점프, 중력에 의한 낙하 등 수직 움직임
};

