#pragma once
#include "CBullet.h"

//! º¸½º °ø°Ý3 Àü¿ë ÃÑ¾Ë : ¶³¾îÁö´Â ÃÑ¾Ë

class CBullet_BossAtk03 final : public CBullet
{
public:
	CBullet_BossAtk03();
	~CBullet_BossAtk03() override;

	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void On_Collision(CObject* pObj) override;
	void Do_Attack() override;
	void Take_Damage(float _fDamage) override;
};
