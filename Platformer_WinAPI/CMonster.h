#pragma once
#include "CObject.h"

class CMonster : public CObject
{
public:
	CMonster();
	~CMonster() override;

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public :
	void On_Collision(CObject* pObj) override;

public :
	virtual void Do_Attack() {}						// Target을 공격하는 함수, pTarget을 설정해둬야 한다
	virtual void Take_Damage(float _fDamage) {}		// 몬스터가 주는 데미지를 받는 함수

public :
	void     Set_Target(CObject* pObj) { pTarget = pObj; }
	CObject* Get_Target() { return pTarget; }

	int  Get_PlayerJumpCount() { return m_iMonsterJumpCount; }
	int  Get_PlayerMaxJump() { return m_iMonsterMaxJump; }
	bool Get_PlayerLanded() { return m_bMonsterLanded; }

	void Set_PlayerMaxJump(int _iMaxJump) { m_iMonsterMaxJump = _iMaxJump; }
	void Set_PlayerLanded(bool _bPlayerLanded) { m_bMonsterLanded = _bPlayerLanded; }

protected:	// 자식에서도 자유롭게 사용 가능한 착지 및 좌우 이동 관련 함수
	void Landed_Platform(CObject* pObj);
	void Landed_Line();

	void Horizontal_Move();

protected:	// m_bGravityOn == true 일 때만 사용 가능한 점프 및 중력 관련 함수
	void Jump(float _fJumpPower);
	void Vertical_Move();

protected :
	CObject* pTarget;

	// 점프 및 착지 관련 변수
	int   m_iMonsterJumpCount;		// 몬스터가 점프 입력 카운트. 착지하면 0이 됨
	int   m_iMonsterMaxJump;		// 한 번 체공 중 점프 몇 번 가능하게 만들건지
	float m_fGroundY;				// Collision_Line이 전달해 주는, 착지해야 할 y좌표 저장
	bool  m_bMonsterLanded;			// 몬스터가 착지 중일 때 true
	bool  m_bGravityOn;				// 몬스터에 중력 부여 해줄건지
};
