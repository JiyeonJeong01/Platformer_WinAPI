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
	ULONGLONG m_qwDTTimer;			// ��ŸŸ�� ������ Ÿ�̸� : ���� �÷��̾ �����ʰ� ���ÿ� �ð��� �帧
	float     m_fDeltaTime;			// ��ŸŸ�� ����� ����

	int m_iPlayerJump;				// �÷��̾ ���� �Է� ī��Ʈ. �����ϸ� 0�� ��
	int m_iPlayerMaxJump;			// �� �� ü�� �� ���� �� �� �����ϰ� �������

	float m_fGroundY;				// Collision_Line�� �����ϴ� fY : �����ؾ� �� y��ǥ

	bool m_bPlayerLanded;			// �÷��̾ ���� ���� �� true
private:

	void Update_Components() override;

	float DeltaTime();

	void Landed();
	void Jump();
	void Horizontal_Move();			// ���� ������
	void Vertical_Move();			// ����, �߷¿� ���� ���� �� ���� ������
};

