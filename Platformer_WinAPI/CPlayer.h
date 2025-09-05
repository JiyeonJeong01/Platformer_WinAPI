#pragma once
#include "CObject.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer() override;

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void		Handle_KeyInput();
	void		Update_Components();

public:
	virtual void Do_Attack() {}; 
	virtual void Take_Damage(float _fDamage) {};

private:
	Vector2		m_vPosinPosition;

	float		m_fMousePosX = 0;	// 마우스의 x 좌표
	float		m_fMousePosY = 0;	// 마우스의  y좌표

private :
	bool bLeftPressed;					// 'A'키 눌렸는지 여부
	bool bRightPressed;				// 'D'키 눌렸는지 여부
	bool bJumpPressed;				// 스페이스 키 눌렸는지 여부
	bool bLeftMouseClicked;		// 마우스 좌클릭 여부
};
// todo : 몬스터 플레이어 hp 추가하기 