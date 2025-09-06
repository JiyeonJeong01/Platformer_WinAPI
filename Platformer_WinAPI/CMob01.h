#pragma once
#include "CMonster.h"
class CMob01 :
    public CMonster
{
public:
	CMob01();
	~CMob01() override;

public:
	void Initialize() override;
	int	Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	virtual void On_Collision(CObject* pObj);
	virtual void Take_Damage(float _fDamage);	// �÷��̾ �ִ� �������� �޴� �Լ�
	virtual void Do_Attack();

	float m_Attack_Interval = 0.f;


};

