#pragma once
#include "CObject.h"
class CMonster : public CObject
{
public:
	CMonster();
	~CMonster() override;

public:
	void Initialize() override;
	int	Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public :
	virtual void On_Collision(CObject* pObj);

public :
	virtual void Do_Attack() {};					// Target을 공격하는 함수, pTarget을 설정해둬야 한다
	virtual void Take_Damage(float _fDamage) { };	// 플레이어가 주는 데미지를 받는 함수
	
public :
	void Set_Target(CObject* pObj) { pTarget = pObj; }
	CObject* Get_Target() { return pTarget;  }

protected :
	CObject* pTarget; 

};

