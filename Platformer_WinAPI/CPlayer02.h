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

	void Jumping();

	bool m_bJump;
	float m_fTime;
	bool isStart;
	float tmp;
	DWORD sz_Time;
};

