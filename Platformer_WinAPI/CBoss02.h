#pragma once
#include "CMonster.h"

enum class BOSS02_PATTERN {IDLE, PATTERN1, PATTERN2, PATERN3, BP_END  };

class CBoss02 :
    public CMonster
{
public:
	CBoss02();
	~CBoss02() override;

public:
	void Initialize() override;
	int	Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void On_Collision(CObject* pObj) override;

public:
	virtual void Do_Attack();						// Target�� �����ϴ� �Լ�, pTarget�� �����ص־� �Ѵ�
	virtual void Take_Damage(float _fDamage);		// �÷��̾ �ִ� �������� �޴� �Լ�

private:

	BOSS02_PATTERN m_pattern = BOSS02_PATTERN::IDLE;

	float m_Attack_Interval = 0.f;

	Vector2 m_BossPosinDir[3];


};

