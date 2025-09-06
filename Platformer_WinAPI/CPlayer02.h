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
	//void		Update_Components();

	void Jumping();

	bool m_bJump;
	float m_fTime;
};

