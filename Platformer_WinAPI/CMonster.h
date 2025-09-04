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
	virtual void Do_Attack(); // -> Target
	virtual void Take_Damage(float _fDamage);

public :
	void Set_Target(CObject* pObj) { pTarget = pObj; }
	CObject* Get_Target() { return pTarget;  }

private :
	CObject* pTarget;

	// Monster's stat components 
	int m_iHP;
	int m_iMaxHp;
	
	int m_iAttackAmount;
	

};

